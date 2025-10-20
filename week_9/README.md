# CS50 Finance

## Overview
This project implements a **simulated stock trading platform** where users can:

- Register and log in securely  
- Look up real-time stock quotes  
- Buy and sell shares  
- View their holdings, cash balance, and transaction history  

It’s part of **CS50x 2025 – Problem Set 9: Finance**.

The goal of this project is to practice **web programming, SQL database management, API integration, and Flask session handling** through a realistic financial simulation.

---

## How It Works

### Step-by-step Functionality
1. **Registration & Login**
   - Users create an account with a unique username and password.
   - Passwords are hashed using `werkzeug.security` for security.
   - Sessions are managed with `Flask-Session`.

2. **Stock Quotes**
   - Users can look up stock information in real time.
   - The app uses `lookup()` (in `helpers.py`) to query the CS50 Finance API.

3. **Buying & Selling Stocks**
   - Users can buy shares if they have enough virtual cash.
   - When a stock is bought or sold, the transaction is recorded in the database.
   - Holdings are automatically updated.

4. **Portfolio Dashboard**
   - Displays all owned stocks with:
     - Symbol and company name
     - Number of shares
     - Current price (via `lookup`)
     - Total value per holding
   - Also shows available cash and grand total balance.

5. **Transaction History**
   - Displays the 15 most recent buy and sell operations.
   - Color-coded for clarity (`green` for buy, `red` for sell`).

---

## Database Design

### `users`
| Column   | Type    | Description |
|-----------|----------|-------------|
| id        | INTEGER | Primary key |
| username  | TEXT    | Unique username |
| hash      | TEXT    | Hashed password |
| cash      | NUMERIC | Virtual cash balance (default: 10000) |

### `holdings`
| Column   | Type    | Description |
|-----------|----------|-------------|
| id        | INTEGER | Primary key |
| user_id   | INTEGER | References `users.id` |
| symbol    | TEXT    | Stock ticker symbol |
| shares    | INTEGER | Number of shares owned |
| UNIQUE(user_id, symbol) | — | Ensures a user can’t have duplicates |

### `transactions`
| Column     | Type    | Description |
|-------------|----------|-------------|
| id          | INTEGER | Primary key |
| user_id     | INTEGER | References `users.id` |
| type        | TEXT    | “buy” or “sell” |
| symbol      | TEXT    | Stock symbol |
| shares      | INTEGER | Number of shares |
| unit_price  | NUMBER  | Price per share |
| timestamp   | DATETIME| Auto-set at transaction time |

---

## Project Structure

```
finance/
├── app.py                # Main Flask app and routes
├── helpers.py            # Helper functions (lookup, apology, usd, etc.)
├── finance.db            # SQLite database
├── requirements.txt      # Python dependencies
│
├── templates/            # HTML templates (Bootstrap + Jinja2)
│   ├── layout.html
│   ├── apology.html
│   ├── login.html
│   ├── register.html
│   ├── quote.html
│   ├── quoted.html
│   ├── buy.html
│   ├── sell.html
│   ├── index.html
│   └── history.html
│
├── static/               # Static assets
│   ├── favicon.ico
│   ├── styles.css
│   └── I_heart_validator.png
│
└── flask_session/        # Folder for session data
```

---

## Installation & Usage

### Clone the repository
```bash
git clone <your_repo_link>
cd finance
```

### Install dependencies
```bash
pip install -r requirements.txt
```

### Run Flask
```bash
flask run
```

### Open your browser
```
http://127.0.0.1:5000
```

---

## Dependencies
```
cs50
Flask
Flask-Session
pytz
requests
```

---

## Notes & Insights
- Implementing **register** and **login** first made testing easier.
- The hardest logic involved updating both `transactions` and `holdings` correctly after each trade.
- Used **Bootstrap 5** for responsive design and consistent theming.
- Added an **apology** system for user-friendly error messages.

---

## Author
**Name:** Jerome Henry   
**Date:** October 2025   
