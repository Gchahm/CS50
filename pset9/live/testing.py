#!/usr/bin/env python3

import cs50
from html.parser import HTMLParser
from urllib import request as req
from bs4 import BeautifulSoup

# create a subclass and override the handler methods
class MyHTMLParser(HTMLParser):
    def handle_starttag(self, tag, attrs):
        if(tag=="head"):
            print ("Encountered a start tag:", tag)

    def handle_endtag(self, tag):
        if(tag=="head"):
            print ("Encountered a end tag:", tag)
    

def main():
    googleMaps = "https://www.google.ie/maps/place/Itajai+sc"
    html = req.urlopen(googleMaps)
    parser = MyHTMLParser()
    
    bytes = html.read().decode("windows-1252")

    
if __name__ == "__main__":
    main()
    

