import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, check_transactions_input


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    # Disable caching to always show updated data
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Retrieve user info and holdings
    user = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])[0]
    holdings = db.execute("SELECT symbol, shares FROM holdings WHERE user_id = ?", session["user_id"])

    # Build portfolio data with current prices
    value = []
    for stock in holdings:
        value.append({
            "symbol": stock["symbol"],
            "shares": stock["shares"],
            "price": lookup(stock["symbol"])["price"],
        })

    # Compute total per stock
    for key in value:
        key["total"] = key["shares"] * key["price"]

    # Compute portfolio summary
    sum_value = sum(item["total"] for item in value)
    balance = user["cash"] + sum_value

    # Render dashboard
    return render_template(
        "index.html", name=user["username"], cash=usd(user["cash"]), value=value,
        sum_value=usd(sum_value), balance=usd(balance),
        holdings=holdings, usd=usd, lookup=lookup
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Validate and extract inputs
        result = check_transactions_input()
        if len(result) != 3:
            return result
        symbol, quotes, shares = result

        # Retrieve user's current cash
        cash_list = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash_list[0]["cash"]

        # Check if user has enough cash
        if float(cash) < shares * quotes["price"]:
            return apology("not enough cash")

        # Record purchase in transactions table
        db.execute("""
            INSERT INTO transactions(user_id, type, symbol, shares, unit_price)
            VALUES(?, ?, ?, ?, ?)
            """, session["user_id"], "buy", symbol, shares, quotes["price"]
        )

        # Deduct cash after purchase
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - (shares * quotes["price"]), session["user_id"])

        # Check if user already owns the stock
        count_symbol = db.execute("SELECT COUNT(*) FROM holdings WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        if count_symbol[0]["COUNT(*)"] == 0:
            # Insert new holding
            db.execute(
                "INSERT INTO holdings(user_id, symbol, shares) VALUES(?, ?, ?)",
                session["user_id"], symbol, shares
            )
        else:
            # Update existing holding
            db.execute(
                "UPDATE holdings SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                shares, session["user_id"], symbol
            )

        # Redirect to portfolio
        return redirect("/")
    else:
        # Render buy form, optionally prefilled if coming from /index
        if request.args.get("symbol") is None:
            return render_template("buy.html")
        else:
            symbol = request.args.get("symbol")
            return render_template("buy.html", symbol=symbol)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Retrieve last 15 transactions for the user
    transactions = db.execute(
        "SELECT type, symbol, shares, unit_price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC LIMIT 15",
        session["user_id"]
    )
    # Render transaction history
    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # Handle form submission
    if request.method == "POST":
        # Validate username
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Validate password
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Check if username exists and password matches
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Log the user in (store session id)
        session["user_id"] = rows[0]["id"]

        # Redirect to homepage
        return redirect("/")

    # Render login form
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Clear session and redirect to login page
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Validate stock symbol input
        symbol = request.form.get("symbol")
        if not symbol or symbol.strip() == "":
            return apology("symbole incorrect")

        # Fetch stock data
        quotes = lookup(symbol)
        if quotes is None:
            return apology("stock not found")

        # Format price in USD
        quotes["price"] = usd(quotes["price"])

        # Render result page
        return render_template("quoted.html", quotes=quotes)
    else:
        # Render quote search form
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Get user inputs
        name = request.form.get("username")
        if not name or name.strip() == "":
            return apology("Username required", 403)

        password = request.form.get("password")
        if not password or password.strip() == "":
            return apology("Password required", 403)

        password_confirm = request.form.get("password_confirm")
        if not password_confirm or password_confirm.strip() == "":
            return apology("Confirm your password", 403)

        # Check password match
        if password == password_confirm:
            password = generate_password_hash(password)
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", name, password)
            return redirect("/login")
        else:
            return apology("Confirmation password does not match", 403)
    else:
        # Render registration form
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Validate and extract inputs
        result = check_transactions_input()
        if len(result) != 3:
            return result
        symbol, quotes, shares = result

        # Check owned shares
        holdings = db.execute("SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]
        if shares > holdings["shares"]:
            return apology("Not enough shares for selling")

        # Record sale in transactions
        db.execute(
            "INSERT INTO transactions(user_id, type, symbol, shares, unit_price) VALUES(?, ?, ?, ?, ?)",
            session["user_id"], "sell", symbol, shares, quotes["price"]
        )

        # Update or remove holding
        db.execute("UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?",
                   holdings["shares"] - shares, session["user_id"], symbol)
        holdings = db.execute("SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]
        if holdings["shares"] == 0:
            db.execute("DELETE FROM holdings WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)

        # Add cash back to user
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", quotes["price"] * shares, session["user_id"])

        # Redirect to portfolio
        return redirect("/")
    else:
        # Display sell form with user's owned stocks
        stock = db.execute("SELECT symbol, shares FROM holdings WHERE user_id = ?", session["user_id"])
        if request.args.get("symbol") is None:
            return render_template("sell.html", stock=stock)
        else:
            symbol = request.args.get("symbol")
            return render_template("sell.html", stock=stock, symbol=symbol)
