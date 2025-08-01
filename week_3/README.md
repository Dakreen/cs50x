# CS50x – Week 3: Tideman

## Goal

Implement a ranked-pairs voting system (the **Tideman method**) that determines the winner of an election using voters' ranked preferences.

## Description

In this program, voters rank candidates in order of preference. The program:

1. Collects all votes and updates a **preference matrix**
2. Identifies all **winning pairs** of candidates
3. Sorts the pairs by **strength of victory**
4. Locks the pairs into a **directed graph**, ensuring no **cycles**
5. Determines the winner as the **source of the graph** (the candidate with no arrows pointing at them)

## Concepts Used

- **2D arrays** to store preferences and graph edges
- **Structs** to represent candidate pairs
- **Sorting algorithms** (custom **merge sort**)
- **Graph theory** (cycle detection using **recursion**)
- **Command-line arguments**
- **Input validation**

## Files

- `tideman.c` — main program source code

## How to Compile and Run

```bash
make tideman
./tideman [candidate1] [candidate2] ... [candidateN]
```

Then follow the prompts to enter voter preferences.

## Notes

This program uses `get_int()` and `get_string()` from the `cs50.`h library.
To run it outside of CS50.dev, you may need to:

Install the CS50 library, or

Replace input functions with standard C equivalents `(scanf, fgets, etc.)`

## Personal Note

This was by far the hardest problem I've encountered in CS50 so far.
Implementing the recursive cycle detection logic and the merge sort algorithm took me a lot of time and debugging.

> The graph logic, especially avoiding cycles when locking in candidate pairs, really tested my understanding of how recursive functions work.
>
> I learned a lot about sorting algorithms, graph theory, and how to think recursively — even though it was frustrating at times.
>
> As always, I used the VS Code debugger to visualize values and recursive calls — it was a lifesaver for understanding why certain pairs created cycles.
