# Credit (CS50 Problem Set 1)

## Overview
This program implements a credit card validator using **Luhn’s Algorithm**.  
It takes a credit card number as input and determines whether the number is valid and, if so, what type of card it is:

- **AMEX** (15 digits, starts with 34 or 37)  
- **MASTERCARD** (16 digits, starts with 51–55)  
- **VISA** (13 or 16 digits, starts with 4)  
- Otherwise: **INVALID**

---

## How It Works

1. **Prompt for Input**  
   - The user enters a credit card number (`long`).

2. **Length Check**  
   - Only numbers with 13, 15, or 16 digits are considered.

3. **Prefix Check**  
   - The first one or two digits are extracted to identify the card issuer.

4. **Luhn’s Algorithm** (via `checksum()`):  
   - Starting from the **second-to-last digit**, double every other digit.  
   - If doubling produces a two-digit number, add both digits separately.  
   - Add this sum to the sum of digits that were **not doubled**.  
   - If the total modulo 10 equals 0 → the number is valid.

5. **Decision**  
   - If the number passes both **prefix check** and **Luhn’s check**, print the card type.  
   - Otherwise, print `INVALID`.

---

## File Structure
- **credit.c** → main program
- Functions:
  - `main()` → handles input, card type checks, and calls validation.
  - `checksum(long number)` → implements Luhn’s Algorithm.
  - `numberLength(long number)` → helper to count digits.

---

## Example Runs

```bash
$ ./credit
Number: 378282246310005
AMEX
$ ./credit
Number: 5555555555554444
MASTERCARD
$ ./credit
Number: 4111111111111111
VISA
$ ./credit
Number: 1234567890
INVALID
```

---

## Notes
- Uses `get_long` from CS50 Library for input.
- Written in C, tested with `check50` and `style50`.
- Demonstrates **control flow**, **loops**, **functions**, and **modulo arithmetic**.

---

## Author
- **Name:** Jerome Henry  
- **Date:** July 2025  

---

## Recruiter Note
This project demonstrates my ability to:  
- Implement and explain a **classic validation algorithm** (Luhn’s).  
- Work with **input validation** and error handling.  
- Apply **modular design** using helper functions.  
- Write **clear, well-documented C code** that passes automated tests.  

It reflects both algorithmic thinking and clean coding style — skills I apply when solving larger system, network, and cybersecurity problems.
