# CS50x – Week 1: Credit

## Goal

Implement a program in C that **validates credit card numbers** using [Luhn’s algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm) and determines the **type of card** (AMEX, MASTERCARD, or VISA).

## Description

The program prompts the user to enter a credit card number. It then:

1. Checks the number of digits (must be 13, 15, or 16).
2. Uses **Luhn’s algorithm** to validate the checksum.
3. Determines the card type based on its **starting digits**:
   - AMEX: 15 digits, starts with `34` or `37`
   - MASTERCARD: 16 digits, starts with `51` through `55`
   - VISA: 13 or 16 digits, starts with `4`

If the number is invalid or does not match a known format, the program prints `INVALID`.

## How It Works

- The `numberLength()` function counts the digits of the card.
- The `checksum()` function applies Luhn’s algorithm:
  - Doubles every second digit from the right.
  - Adds the digits of those products.
  - Sums them with the digits in the odd positions.
  - Valid if the total ends in 0.
- The first one or two digits are extracted to identify the card type.

## Files

- `credit.c`: Main source code

## Requirements

- Language: C
- Libraries: `cs50.h`, `stdio.h`
- Environment: [CS50.dev](https://cs50.dev) or local setup with the CS50 library installed

## Note

> This program uses the `cs50.h` library for `get_long()`.  
> If you plan to compile it outside CS50.dev, you may need to:
> - Install the CS50 library manually  
> - Or replace `get_long()` with `scanf()` for portability

## ✍️ Personal Note

> I found this problem interesting — it required some logical thinking and careful handling of digits and conditions.  
> Luhn’s algorithm was simple once broken down, and implementing the checksum helped me practice loops and modular arithmetic.  
> 
> I also used the **debugging tool in VS Code for the first time** to inspect variables step by step. It was a great way to understand how values changed during execution and really helped me catch logic errors.







