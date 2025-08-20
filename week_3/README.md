# Tideman Voting Algorithm (CS50 Problem Set 3)

## Overview
This program implements the **Tideman (Ranked Pairs) voting method**, a ranked-choice voting algorithm.  
It determines the winner of an election by considering voter preferences and building a graph of candidate victories **without creating cycles**.

Steps:
1. Record preferences between all pairs of candidates.  
2. Create pairs of candidates (winner → loser).  
3. Sort pairs by **strength of victory**.  
4. Lock pairs into a directed graph (skip any that would form a cycle).  
5. The candidate with **no edges pointing at them** is declared the winner.  

---

## How It Works

1. **Input**
   - Candidate names are provided as command-line arguments.
   - Number of voters is requested with `get_int()`.
   - Each voter provides ranked preferences for all candidates.

2. **Data Structures**
   - `preferences[i][j]`: number of voters who prefer candidate `i` over `j`.
   - `locked[i][j]`: `true` if candidate `i` is locked in over `j`.
   - `pairs[]`: list of winner–loser pairs.

3. **Functions**
   - `vote()` → records a voter’s individual ranking.  
   - `record_preferences()` → updates global preferences matrix.  
   - `add_pairs()` → builds winner–loser pairs.  
   - `sort_pairs()` → sorts pairs by strength of victory (using merge sort).  
   - `lock_pairs()` → locks pairs into the graph, skipping cycles.  
   - `print_winner()` → finds the graph’s “source” node (the winner).  

4. **Cycle Detection**
   - Implemented recursively in `check_cycle()`.  
   - Ensures no cycles are formed in the locked graph.  

---

## File Structure
- **tideman.c** → full implementation
- Functions:  
  - `vote`, `record_preferences`, `add_pairs`, `sort_pairs`, `lock_pairs`, `print_winner`  
  - `merge_sort`, `merge` → sorting helper functions  
  - `check_cycle` → cycle detection  

---

## Example Run

```bash
$ ./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Bob
Rank 3: Alice

Charlie
```

---

## Notes
- Handles up to 9 candidates (configurable with MAX).
- Implements **merge sort** (O(n log n)) instead of bubble sort for efficiency.
- Uses **recursion** in check_cycle to prevent infinite loops.
- Designed for **clarity and modularity**, with **heavy inline documentation**.

---

## Author
- **Name:** Jerome Henry
- **Date:** August 2025

---

## Recruiter Note
This project demonstrates my ability to:
   - Implement a non-trivial **graph algorithm** (cycle detection).
   - Apply **sorting algorithms** (merge sort).
   - Use **multi-dimensional arrays** and **structures** in C.
   - Break down complex problems into **modular functions**.

It shows strong skills in algorithm design, data structures, and problem-solving — directly transferable to system, network, and cybersecurity work.