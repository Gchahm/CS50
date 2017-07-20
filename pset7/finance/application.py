from flask import Flask, flash, redirect, render_template, request, session, url_for
from sqlalchemy import func
from sqlalchemy.dialects.sqlite import REAL
from flask_session import Session
from flask_sqlalchemy import SQLAlchemy
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
import datetime
from helpers import *
import datetime, time

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"

app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
app.config['SQLALCHEMY_DATABASE_URI'] = "sqlite:///finance.db"
app.config["SQLALCHEMY_ECHO"] = True

Session(app)
# configure CS50 Library to use SQL Alchemy
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = "users"
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.Text)
    hash = db.Column(db.Text)
    cash = db.Column(db.Float)
    
    def __init__(self, username, hash):
        self.username = username
        self.hash = hash
        self.cash=10000.00

    def __repr__(self):
        return "<User %r>" % self.username
    
    def checkHash(self,hash):
        return pwd_context.verify(hash,self.hash)
        
class Transaction(db.Model):
    __tablename__ = "transactions"
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer)
    symbol = db.Column(db.Text)
    value = db.Column(db.REAL)
    quantity = db.Column(db.Integer)
    datetime = db.Column(db.DateTime)

 
 
    
    def __init__(self, user_id, symbol,value,quantity):
        self.user_id = user_id
        self.symbol = symbol
        self.value = value
        self.quantity=quantity
        self.datetime=datetime.datetime.now()
        
    def __repr__(self):
        return '<User %r>' % self.username
    
    

@app.route("/")
@login_required
def index():
    
    stocks = db.session.query(Transaction.symbol,Transaction.symbol.label("name"),func.sum(Transaction.quantity).label("quantity"),Transaction.value).group_by(Transaction.symbol).filter(Transaction.user_id.in_([session["user_id"]]))
    symbols = {}
    for stock in stocks:
        current = lookup(stock.symbol)
        symbols[stock.symbol]=current
    
    return render_template("index.html",stocks=stocks,cash=round(session["cash"],2),symbols=symbols)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
           return apology("must provide a symbol")
        elif not request.form.get("quantity") or request.form.get("quantity",type=int)<=0:
            return apology("must have a valid quantity")
        results = lookup(request.form.get("symbol"))
        quantity=request.form.get("quantity",type=int)
        if not results:
            return apology("Couldn't process the request")
        
        if session["cash"] < (results["price"]*quantity):
            return apology("You're trying to bite","more than you can chew")
        
        bought = Transaction(session["user_id"],results["symbol"],results["price"],quantity)
        db.session.add(bought)

        user = User.query.get(session["user_id"])
        user.cash = session["cash"]-(results["price"]*quantity)

        
        db.session.commit()
        
        session["cash"]=user.cash
        session["message"]="bought"
        
        return redirect(url_for("index"))
                        
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    
    stocks = Transaction.query.filter_by(user_id=session["user_id"]).order_by(Transaction.datetime).all()
    types = {}
    for stock in stocks:
        if stock.quantity>0:
            types[stock.symbol+"type"]="BUY"
        else:
            types[stock.symbol+"type"]="SELL"


    return render_template("history.html",stocks=stocks,types=types)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        user = User.query.filter_by(username=request.form.get("username")).first()

        # ensure username exists and password is correct

        #if not user or not pwd_context.verify(request.form.get("password"),hash):
        if not user or not user.checkHash(request.form.get("password")): 
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = user.id
        session["cash"] = user.cash
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if not request.form.get("quote"):
           return apology("must profile a symbol")
        results = lookup(request.form.get("quote"))
        if not results:
            return apology("Couldn't process the request")
        return render_template("quoted.html",results=results)
                        
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    
    session.clear()
    
    if request.method == "POST":
        
        if not request.form.get("username"):
            return apology("must provide username")
        
        user_check = User.query.filter_by(username=request.form.get("username")).first()
        if not user_check is None:
            return apology("Username is invalid")
    
        if not request.form.get("password") or not request.form.get("passverify"):
            return apology("Password/validation is invalid")
        elif not (request.form.get("password")==request.form.get("passverify")):
            return apology("Password/validation does not match")
        
        hash=pwd_context.encrypt(request.form.get("password"))
        user = User(request.form.get("username"),hash)
        db.session.add(user)
        db.session.commit()
        if not user.id:
            return("sorry there was an error with the database")
        
        session["user_id"] = user.id
        session["cash"] = user.cash
        return redirect(url_for("index"))
    
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method=="POST":
        if not request.form.get("symbol"):
            return apology("must type in a symbol")
        if not request.form.get("quantity"):
            return apology("must type in a quantity")
        current = lookup(request.form.get("symbol"))
        if not current:
            return apology("Couldn't find this symbol")
        quantity=request.form.get("quantity",type=int)
        
        stock_check = Transaction.query.filter_by(user_id=session["user_id"],symbol=current["symbol"]).all()
        owned=0
        for stock in stock_check:
            owned+=stock.quantity
        if quantity>owned :
            return apology("you're trying to sell","more than what you have")
        quantity=-quantity
        sold = Transaction(session["user_id"],current["symbol"],current["price"],quantity)
        db.session.add(sold)

        user = User.query.get(session["user_id"])
        user.cash = session["cash"]+(current["price"]*quantity)
        
        db.session.commit()
        
        session["cash"]=user.cash
        session["message"]="sold"
        
        return redirect(url_for("index"))

    return render_template("sell.html")

@app.route("/", methods=[ "POST"])
@login_required
def indextransaction():
    if not request.form.get("id"):
        return apology("must tick a option")
    symbol=request.form.get("id")
    if not request.form.get(symbol,type=int):
        return apology("must type a quantity")
    quantity=request.form.get(symbol,type=int)

    if quantity<1:
        return apology("must have a valid quantity")
    results=lookup(symbol)

    if session["cash"] < (results["price"]*quantity):
        return apology("You're trying to bite","more than you can chew")

    bought = Transaction(session["user_id"],results["symbol"],results["price"],quantity)
    db.session.add(bought)

    user = User.query.get(session["user_id"])
    user.cash = session["cash"]-(results["price"]*quantity)
    session["cash"]=user.cash
    
    db.session.commit()

    return redirect(url_for("index"))