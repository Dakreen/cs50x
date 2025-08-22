📝 Notes: Recursion in check_cycle (Tideman)


---

1. Function Recap

From your Tideman code:

bool check_cycle(int winner, int loser)
{
    if (loser == winner) // base case: cycle found
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) // edge from loser → i
        {
            if (check_cycle(winner, i)) // recursive call
            {
                return true;
            }
        }
    }
    return false; // no cycle found
}


---

2. What It Does

Prevents locking a pair if it would create a cycle in the directed graph.

Uses recursion to walk through the graph:

Start at the loser of a pair.

Follow any outgoing edges (locked[loser][i]).

If you eventually get back to the winner, a cycle exists.




---

3. Base Case

if (loser == winner) return true;

If while walking the graph you reach the starting candidate (winner), you’ve made a loop.

Stops recursion immediately.



---

4. Recursive Case

if (locked[loser][i]) {
    if (check_cycle(winner, i)) {
        return true;
    }
}

If loser is locked to candidate i, recurse from i.

Each recursive call checks one level deeper in the graph.

This continues until:

Cycle found → returns true all the way up.

No edges left → returns false.




---

5. Example Walkthrough

Suppose we’re about to lock A → B.

Call: check_cycle(A, B)

Not equal → explore edges from B.

Suppose B → C is locked → call check_cycle(A, C)

Not equal → explore edges from C.

Suppose C → A is locked → call check_cycle(A, A)

Base case: loser == winner → return true.





Unwinding:

check_cycle(A, A) → true
check_cycle(A, C) → true
check_cycle(A, B) → true

So locking A → B would create a cycle, and must be skipped.


---

6. Stack Behavior

Each recursive call adds a frame:

check_cycle(A,B)
 └─ check_cycle(A,C)
     └─ check_cycle(A,A) → true

When base case is hit:

Stack unwinds, returning true step by step.



---

7. Key Takeaways

Downcalls: follow edges deeper into the graph.

Base case: cycle detected (loser == winner).

Upcalls: propagate true back if a cycle was found.

If recursion finishes with no cycle, returns false.



---

✅ In short:

check_cycle is a recursive depth-first search for a path back to the original winner.

Recursion makes the graph traversal simple: “check this node, then recurse on its neighbors.”

The function prevents creating cycles in the Tideman graph.

---

📝 Diagram: Recursion in check_cycle (Tideman)


---

1. Graph Example

We already have two locked edges:

A → B
B → C

Now we’re considering locking:

C → A


---

2. Function Call

We test:

check_cycle(A, C)

winner = A

loser = C



---

3. Step-by-Step Recursion

Call 1: check_cycle(A, C)

loser != winner → keep going.

Look at edges from C.

Suppose C → A exists (the new edge).

Recurse: check_cycle(A, A).



---

Call 2: check_cycle(A, A)

Base case: loser == winner.

Cycle detected → return true.



---

4. Stack Trace

check_cycle(A,C)
 └─ check_cycle(A,A) → true

Unwinds:

check_cycle(A,A) returns true.

check_cycle(A,C) returns true.


So adding C → A would create a cycle.


---

5. Visual Diagram

A → B → C
   ↑       |
   |_______|

Start at loser (C).

Follow edge C → A.

Arrived back at winner (A).

✅ Cycle detected.



---

6. Key Takeaway

check_cycle works like a depth-first search (DFS).

Downcalls = follow graph edges deeper.

Base case = reached the starting node → cycle.

Upcalls = return true all the way up.



---

✅ In short:
When locking edges, check_cycle prevents cycles by recursively checking if you can “walk” back to the original winner.



