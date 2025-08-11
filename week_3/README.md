# Tideman Voting Algorithm

**Author:** Dakreen  
**Date:** July 2025  
**Course:** CS50x – Problem Set 3

---

## Overview
This program implements the **Tideman (Ranked Pairs)** voting algorithm, a ranked-choice voting method that determines the winner without creating contradictions in voter preferences.  
It ensures that the most preferred candidate wins while avoiding cycles in the directed preference graph.

---

## Problem Solved
Traditional plurality voting can lead to winners who are not the most broadly supported candidate.  
Tideman’s method:
- Records voters’ ranked preferences.
- Compares every pair of candidates.
- Orders these pairs by the **strength of victory**.
- Locks them into a directed graph, skipping any that would create cycles.
- Declares the candidate with no incoming edges as the winner.

---

## How It Works
1. **Initialize** preference and locked matrices.
2. **Collect votes**:
   - Validate each vote with `vote()`.
   - Record preferences with `record_preferences()`.
3. **Add pairs**:
   - Store all winning/losing candidate pairs using `add_pairs()`.
4. **Sort pairs**:
   - Sort in descending order of victory strength using `merge_sort()`.
5. **Lock pairs**:
   - Add edges to the graph with `lock_pairs()`, avoiding cycles via `check_cycle()`.
6. **Print winner**:
   - Candidate with no incoming edges is declared winner via `print_winner()`.

---

## Key Functions
- `vote()` → Validates and records candidate ranks for a voter.
- `record_preferences()` → Updates global preferences matrix.
- `add_pairs()` → Identifies all winning pairs from preferences.
- `sort_pairs()` → Sorts pairs by strength of victory.
- `lock_pairs()` → Locks in pairs without forming cycles.
- `check_cycle()` → Recursive cycle detection.
- `print_winner()` → Finds the graph’s source (winner).

---

## Why This Project Is Interesting
- Involves **graph theory** concepts such as directed acyclic graphs (DAGs) and cycle detection.
- Uses **sorting algorithms** (merge sort) for performance.
- Applies recursion to prevent graph cycles.
- Demonstrates ability to translate a real-world voting method into C code.

---

## References
- Tideman, N. (1987). *Independence of clones as a criterion for voting rules*.  
- [CS50x Problem Set 3 Specification](https://cs50.harvard.edu/x/)  

---

## Note
This project was developed as part of **CS50x** while learning C.  
It uses the **CS50 Library** (`cs50.h`) for input handling (`get_int()`, `get_string()`).  
In production code:
- You would replace CS50 input functions with standard C equivalents.
- You could optimize sorting or use adjacency lists for graph representation.
