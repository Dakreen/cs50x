import requests

from flask import redirect, render_template, session, request
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    # Escape special characters to safely display message via meme generator

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    # Render apology.html with formatted message and code
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """
    # Wrapper function to restrict routes to logged-in users only
    @wraps(f)
    def decorated_function(*args, **kwargs):
        # Redirect to login page if user not authenticated
        if session.get("user_id") is None:
            return redirect("/login")
        # Otherwise execute the wrapped route
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    # Request stock data from CS50 Finance API
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        # Return relevant stock info as dictionary
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    # Format numeric value into currency string (e.g., $1,234.56)
    return f"${value:,.2f}"


def check_transactions_input():
    """Check symbol, shares input for transactions"""
    # Get symbol from form and validate
    symbol = request.form.get("symbol")
    if not symbol or symbol.strip() == "":
        return apology("symbol incorrect")
    symbol = symbol.upper()

    # Validate if symbol exists via lookup
    quotes = lookup(symbol)
    if quotes is None:
        return apology("stock not found")

    # Get and validate shares count
    shares = request.form.get("shares")
    if shares.strip() == "":
        return apology("number of shares incorrect")

    try:
        shares = int(shares)
    except ValueError:
        return apology("number of shares incorrect")

    if shares <= 0:
        return apology("share must be higher than 0")

    # Return validated tuple for use in /buy or /sell
    return symbol, quotes, shares
