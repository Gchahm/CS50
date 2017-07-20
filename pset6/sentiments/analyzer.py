import nltk
from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.pw=set()
        self.nw=set()
        
        filep = open(positives, "r")
        for line in filep:
            if line.startswith(";")==0:
                self.pw.add(line.rstrip())
        filep.close()
        
        filen = open(negatives,"r")
        for line in filen:
            if line.startswith(";")==0:
                self.nw.add(line.strip())
        filen.close()
        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        for token in tokens:
            if token.lower() in self.pw:
                score+=1
            if token.lower() in self.nw:
                score-=1
        return score