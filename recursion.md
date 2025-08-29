# Notes: Recursion in C — With & Without Return Values


---

## 1. What is Recursion?

Recursion = when a function calls itself to solve a smaller version of the same problem.
Every recursive function needs:

1. Base case → when to stop.


2. Recursive case → the self-call on smaller input.




---

## 2. Recursion without Return Value

Function does something (like printing).

Doesn’t need to return a result.

Work happens “on the way down” or “on the way back up.”


Example: countdown
```c
void countdown(int n) {
    if (n <= 0) {         // base case
        printf("Go!\n");
        return;
    }
    printf("%d\n", n);    // work before recursive call
    countdown(n - 1);     // recursive call
}
```
Execution (countdown(3)):
```
3
2
1
Go!
```
Each call just prints.

No value is sent back to the caller.



---

## 3. Recursion with Return Value

Each call returns a value to its caller.

The final answer is built step by step as recursion unwinds.


Example: factorial
```c
int factorial(int n) {
    if (n == 0) {           // base case
        return 1;
    }
    return n * factorial(n - 1); // recursive case with return
}
```
Execution (factorial(3)):
```
factorial(3) → 3 * factorial(2)
factorial(2) → 2 * factorial(1)
factorial(1) → 1 * factorial(0)
factorial(0) → 1 (base case)
```
Unwinding:
```
factorial(1) = 1 * 1 = 1
factorial(2) = 2 * 1 = 2
factorial(3) = 3 * 2 = 6
```
Final return value = 6


---

## 4. Comparison Table
```
Feature         | Without Return Value           |	With Return Value
+---------------------------------------------------------------------------------+
Purpose         | Perform actions (side effects) |	Compute and return a result
Example         | Printing, traversing a tree    |	Factorial Fibonacci, search
Flow            | No values passed back          |	Values passed back up the stack
Unwinding phase | Does nothing special           |	Builds the final answer
Example         | void countdown(int n)          |	int factorial(int n)
```


---

## 5. Stack Behavior

In both cases, each call has its own stack frame.

Without return → frames disappear after printing.

With return → frames disappear after sending back a value.



---

## In short:

Recursion without return = good for tasks with side effects (printing, visiting nodes).

Recursion with return = good for tasks that produce a final answer (math functions, search results).


---

# Notes: Recursion and the Call Stack


---

## 1. The Call Stack in C

The stack is a memory region where each function call gets a stack frame.

A stack frame contains:

Local variables

Parameters

Return address (where to go back after finishing)


When a function is called → a new frame is pushed on the stack.

When it returns → the frame is popped from the stack.



---

## 2. Example: Recursion without Return
```c
void countdown(int n) {
    if (n <= 0) {
        printf("Go!\n");
        return;
    }
    printf("%d\n", n);
    countdown(n - 1);
}
```
Call countdown(3)

Stack grows like this:
```
Top → countdown(3)
        countdown(2)
            countdown(1)
                countdown(0) → prints "Go!" and returns
```
Unwinding:

countdown(0) returns, its frame pops.

Then countdown(1) returns, pops.

Then countdown(2) returns, pops.

Finally countdown(3) returns, pops.


Stack is empty at the end.
Each frame just printed output, no values returned.


---

## 3. Example: Recursion with Return
```c
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
```
Call factorial(3)

Stack grows:
```
Top → factorial(3) waiting for factorial(2)
        factorial(2) waiting for factorial(1)
            factorial(1) waiting for factorial(0)
                factorial(0) → returns 1
```
Unwinding (return values travel back up):
```
factorial(0) returns 1
factorial(1) = 1 * 1 = 1
factorial(2) = 2 * 1 = 2
factorial(3) = 3 * 2 = 6
```
Stack empty again, final result = 6.


---

## 4. Visual Analogy

Think of recursion like stacking plates:

Each new call = put another plate on top.

Base case = stop adding plates.

Return = remove plates one by one, possibly computing as you go.



---

## 5. Risks

Too many plates = stack overflow
(e.g., infinite recursion or very deep recursion).

Always ensure a base case so the stack unwinds.



---

## In short:

Recursion works because the stack remembers where each function left off.

Without return → stack unwinds with no values, just actions.

With return → stack unwinds while passing values back up.

---

📝 Note: Recursion Demo in C

The Code

#include <stdio.h>

void rec(int n)
{
    if (n == 0)                // Base case
    {
        printf("Base case\n");
        return;
    }

    printf("Down %i\n", n);    // Action before recursion (going down)
    rec(n - 1);                // Recursive call with smaller n
    printf("Up%i\n", n);       // Action after recursion (going up)
}

int main()
{
    rec(5);
    return 0;
}


---

📌 What it Does

Base case: stop when n == 0.

Going down: print Down n before the recursive call.

Going up: print Up n after the recursive call.



---

⏱️ Step-by-step output

Down 5
Down 4
Down 3
Down 2
Down 1
Base case
Up1
Up2
Up3
Up4
Up5

First the program goes down from 5 → 1, opening calls on the stack.

At 0, it hits the base case and stops.

Then it goes up 1 → 5, unwinding the stack and finishing each paused call.



---

🧠 Key Idea

Recursion always has two phases:

1. Descent (going down) → building or preparing, until base case.


2. Ascent (going up) → resolving, filling results, closing calls.




This is exactly how create_family works in CS50’s Inheritance:

Going down: reserve space for parents until base generation.

Going up: actually assign parents/alleles and return the child.



---

✅ Use this simple “Down / Base case / Up” pattern whenever recursion feels abstract — it shows clearly where work happens.



