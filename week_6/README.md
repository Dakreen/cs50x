# DNA (CS50 Problem Set 6)

## Overview
This project is part of **CS50x Problem Set 6**.  
It implements a DNA profile identifier that compares **short tandem repeats (STRs)** in a DNA sequence against a database of individuals.

This repository only contains my own implementation of `dna.py`.  
Other files (sample databases, sequences, testing framework) were provided by CS50 staff.

---

## How It Works

### Core Logic
1. Load a DNA database (CSV) containing names and STR counts.  
2. Load a DNA sequence (text file).  
3. For each STR, compute the **longest consecutive run** inside the sequence.  
4. Compare the computed counts against each profile in the database.  
5. Print the matching person’s name, or `No match` if none found.

### Data Structures / Algorithms
- **Dictionaries** to store STRs and their counts.  
- **String scanning algorithm** (`longest_match`) using a sliding window to find consecutive repeats.  
- **CSV parsing** with Python’s built-in `csv.DictReader`.  

### Functions Implemented
- `main()` → orchestrates program execution.  
- `command_line_check()` → ensures correct usage.  
- `database_loader(db)` → loads CSV database into memory.  
- `sequence_loader(seq)` → reads DNA sequence from file.  
- `get_match(str_list, str_seq)` → builds dictionary of STR counts from sequence.  
- `check_db(match, db)` → compares computed STR counts to each profile.  

Note: The helper function `longest_match(sequence, subsequence)` was provided by CS50 staff.  
I integrated this into my solution, while implementing all the surrounding logic.
 

### Design Choices
- Used `csv.DictReader` for easy access to STR names and values.  
- Represented STR counts as a dictionary `{STR: count}` for clarity.  
- Algorithm checks every position in the DNA string; efficient enough for CS50’s input sizes.  

---

## File Structure
- **dna.py** → my implementation.   

---

## Notes
- Learned to manipulate text data and structured CSV files in Python.  
- Practiced implementing a **string pattern matching algorithm**.  
- Reinforced the use of **dictionaries** for comparisons.  

---

## Author
- **Name:** Jerome Henry  
- **Date:** September 2025  
