# Credit Card Validator

**Author:** Dakreen  
**Date:** June 2025  
**Course:** CS50x – Problem Set 1

---

## Overview
This program validates credit card numbers using the **Luhn algorithm** and determines the card type (**AMEX**, **MASTERCARD**, or **VISA**) based on the number’s length and starting digits.

---

## Problem Solved
Credit card numbers follow specific patterns that can be validated before sending them to a payment processor.  
By checking both the checksum and the card’s prefix rules, we can:
- Detect invalid numbers early.
- Identify the issuing network.

---

## How It Works
1. Prompt the user for a credit card number.  
2. Count the number of digits.  
3. Extract the first one or two digits for card type identification.  
4. Apply **Luhn’s algorithm** to verify the checksum.  
5. Match card type based on:
   - **AMEX**: 15 digits, starts with 34 or 37  
   - **MASTERCARD**: 16 digits, starts with 51–55  
   - **VISA**: 13 or 16 digits, starts with 4  
6. Print the card type or `"INVALID"`.

---

## Key Functions
- `numberLength()` → Counts the number of digits in the card number.  
- `checksum()` → Applies Luhn’s algorithm to verify validity.

---

## Note
This project was developed as part of **CS50x** while learning the C programming language.  
It uses the **CS50 Library** (`cs50.h`) for simplified input handling via `get_long()`.  
This library is designed for educational purposes and is **not required** in production — in real-world C programs, you would use `scanf()` or similar standard library functions for input.  

---

## 📚 References
- [Luhn Algorithm – Wikipedia](https://en.wikipedia.org/wiki/Luhn_algorithm)  
- [CS50x Problem Set 1 Specification](https://cs50.harvard.edu/x/)
