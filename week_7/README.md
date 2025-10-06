# Fiftyville (CS50 SQL – Week 7)

## Overview
This project is part of **CS50x Week 7**.  
Using SQL, I investigated the *Mystery of Fiftyville* to identify:
- the **thief**  
- the **accomplice**  
- the **city** to which the thief escaped  

This repository contains my own `log.sql` (all queries I executed) and `answers.txt`.  
The database file `fiftyville.db` was provided by CS50 staff.

---

## How It Works

### Core Logic
1. Read the **crime scene report** to extract key facts (date, place, time).  
2. Review **witness interviews** to derive actionable leads:  
   - check **bakery security logs** (cars exiting near 10:15),  
   - check **Leggett Street ATM withdrawals** the same morning,  
   - check **short phone calls** (< 60s) made that day,  
   - find the **earliest flight** on the next day.  
3. Cross-reference people who match *all* clues:  
   - withdrew at the ATM,  
   - were seen exiting the bakery parking lot,  
   - appear on the earliest flight’s passenger list,  
   - placed a short call that day.  
4. Identify the **caller** (thief) and the **callee** (accomplice).  
5. Query the flight’s **destination city**.

### Data / Tables Used
- `crime_scene_reports` – incident details  
- `interviews` – witness statements  
- `bakery_security_logs` – license plates entering/exiting  
- `atm_transactions` + `bank_accounts` – link accounts to people  
- `phone_calls` – caller/receiver/duration  
- `flights`, `airports`, `passengers` – travel records  
- `people` – names, phones, passports, plates  

### Query Design Highlights
- **Progressive narrowing**: each step reduces candidates with `JOIN`s and `IN` subqueries.  
- **Time windows**: filter bakery exits around 10:15 (theft time).  
- **First flight**: `ORDER BY hour LIMIT 1` to pick the earliest on July 29.  
- **Caller vs receiver**: thief is the **caller** in a <60s call; accomplice is the **receiver**.  

---

## Result
- Thief: Bruce
- Accomplice: Robin
- City: New York City

---

## File Structure
- **answers.txt** – final answers in the required format  
- **fiftyville.db** – SQLite database provided by CS50  
- **log.sql** – complete, ordered list of all queries used to solve the case  
- **README.md** – this explanation  

---

## Notes
- Practiced **relational reasoning** with multiple joins and subqueries.  
- Reinforced careful filtering (dates, times, durations) and **step-by-step narrowing**.  
- Wrote a clean investigation log that is reproducible via `.read log.sql`.  

---

## Author
- **Name:** Jerome Henry  
- **Date:** October 2025  
