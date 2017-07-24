import os
import re
from flask import Flask, jsonify, json, render_template, request, url_for,redirect
from flask_jsglue import JSGlue
from urllib import request as req

from helpers import lookup
# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")    
def search():
    if not request.args.get("location"):
        raise RuntimeError("missing location")
    if not request.args.get("country"):
        raise RuntimeError("missing country")
    location = request.args.get("location")
    country = request.args.get("country")
    
    googleMaps = "https://www.google.ie/maps/place/"+location+"+"+country+"&callback=?"
    
    html = req.urlopen(googleMaps)
    
    bytes = html.read(10).decode("windows-1252")
    
    d = json.dumps(bytes)
    return d