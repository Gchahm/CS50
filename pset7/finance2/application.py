from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
import datetime
from helpers import *

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
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    stocks = db.execute("SELECT user_id,symbol,symbol,value,sum(quantity) as quantity FROM transactions WHERE user_id=:user_id group by symbol",user_id=session["user_id"])
    for stock in stocks:
        current = lookup(stock["symbol"])
        stock["value"]=current["price"]
        stock["user_id"]=current["name"]
    usercash = db.execute("SELECT cash FROM users where id=:id",id=session["user_id"])
    cash = round(usercash[0]["cash"],2)
    return render_template("index.html",stocks=stocks,cash=cash,message=json.loads(message))

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
        rows = db.execute("SELECT cash FROM users where id =:id",id=session["user_id"])    
        if len(rows)!=1:
            return apology("something awful happend","good luck next time")
        if rows[0]["cash"] < (results["price"]*quantity):
            return apology("You're trying to bite","more than you can chew")
        
        buy = db.execute("INSERT INTO transactions(user_id,symbol,value,quantity) VALUES(:id, :symbol, :value, :quantity)",id=session["user_id"],symbol=results["symbol"],value=results["price"],quantity=quantity)
        if not buy:
            return("sorry there was an error with the database")
            
        cash=rows[0]["cash"]-(results["price"]*quantity)
        db.execute("UPDATE users SET cash=:cash WHERE id=:id",cash=cash,id=session["user_id"])
        
        return redirect(url_for("index"))
                        
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    stocks = db.execute("SELECT * FROM transactions WHERE user_id=:user_id order by date desc,time desc",user_id=session["user_id"])
    dformat = '%Y-%m-%d'
    new_dformat = '%d/%m/%y'
    tformat = '%H:%M:%S'
    new_tformat = '%H:%M:%S'
    for stock in stocks:
        if stock["quantity"]>0:
            stock["user_id"]="BUY"
        else:
            stock["user_id"]="SELL"
            stock["quantity"]=-stock["quantity"]
        stock["date"]=datetime.datetime.strptime(stock["date"], dformat).strftime(new_dformat)
        stock["time"]=datetime.datetime.strptime(stock["time"],tformat).strftime(new_tformat)
        
    return render_template("history.html",stocks=stocks)

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
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
        
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) == 1:
            return apology("Username is invalid")
    
        if not request.form.get("password") or not request.form.get("passverify"):
            return apology("Password/validation is invalid")
        elif not (request.form.get("password")==request.form.get("passverify")):
            return apology("Password/validation does not match")
        
        hash=pwd_context.encrypt(request.form.get("password"))
        result=db.execute("insert into users(username,hash) values(:username, :hash)",username=request.form.get("username"),hash=hash)
        if not result:
            return("sorry there was an error with the database")
        
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

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
        rows = db.execute("select sum(quantity) as quantity,cash from transactions join users on user_id=users.id where user_id =:user_id and symbol=:symbol",user_id=session["user_id"],symbol=current["symbol"])
        if len(rows)!=1:
            return apology("do you really","have that symbol?")
        owned = int(rows[0]["quantity"])
        if quantity>owned :
            return apology("you're trying to sell","more than what you have")
        
        sell = db.execute("INSERT INTO transactions(user_id,symbol,value,quantity) VALUES(:id, :symbol, :value, :quantity)",id=session["user_id"],symbol=current["symbol"],value=current["price"],quantity=-quantity)
        if not sell:
            return("sorry there was an error with the database")
            
        cash=rows[0]["cash"]+(current["price"]*quantity)
        db.execute("UPDATE users SET cash=:cash WHERE id=:id",cash=cash,id=session["user_id"])
        return redirect(url_for("index"))

    return render_template("sell.html")

@app.route("/", methods=[ "POST"])
@login_required
def indextransaction():
    if not request.form.get("id"):
        return apology("must tick a option")
    if not request.form.get("quantity"):
        return apology("must type a quantity")
    symbol=request.form.get("id")
    quantity=request.form.get("quantity",type=int)
    if quantity<1:
        return apology("must have a valid quantity")
    results=lookup(symbol)
    rows = db.execute("SELECT cash FROM users where id =:id",id=session["user_id"])    
    if len(rows)!=1:
        return apology("something awful happend","good luck next time")
    if rows[0]["cash"] < (results["price"]*quantity):
        return apology("You're trying to bite","more than you can chew")
    
    buy = db.execute("INSERT INTO transactions(user_id,symbol,value,quantity) VALUES(:id, :symbol, :value, :quantity)",id=session["user_id"],symbol=results["symbol"],value=results["price"],quantity=quantity)
    if not buy:
        return("sorry there was an error with the database")
        
    cash=rows[0]["cash"]-(results["price"]*quantity)
    db.execute("UPDATE users SET cash=:cash WHERE id=:id",cash=cash,id=session["user_id"])
    
    return redirect(url_for("index"))