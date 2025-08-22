📝 Notes: Bubble Sort vs Merge Sort


---

1. Bubble Sort (Iterative)

🔹 Idea

Repeatedly compare adjacent elements.

Swap them if they are in the wrong order.

Largest element “bubbles” to the end after each pass.

Keep looping until no swaps needed.


🔹 Example

Array: [5, 3, 8, 2]
Pass 1: [3, 5, 2, 8]
Pass 2: [3, 2, 5, 8]
Pass 3: [2, 3, 5, 8] ✅ sorted

🔹 Pseudocode

repeat n-1 times:
    for i from 0 to n-2:
        if arr[i] > arr[i+1]:
            swap arr[i], arr[i+1]

🔹 Complexity

Best case: O(n) (already sorted with optimization).

Worst case: O(n²).

Space: O(1) (in-place).

Simple but inefficient for large arrays.



---

2. Merge Sort (Recursive)

🔹 Idea

Divide-and-conquer:

1. Split array into halves.


2. Recursively sort each half.


3. Merge the two sorted halves.




🔹 Example

Array: [5, 3, 8, 2]
Split → [5, 3] and [8, 2]
Sort → [3, 5] and [2, 8]
Merge → [2, 3, 5, 8]

🔹 Pseudocode

if n < 2:
    return
mid = n/2
merge_sort(left half)
merge_sort(right half)
merge the two halves into sorted array

🔹 Complexity

Best case: O(n log n).

Worst case: O(n log n).

Space: O(n) (needs temporary arrays).

Efficient and scalable.



---

3. Comparison Table

Feature	Bubble Sort	Merge Sort

Method	Iterative (loop + swap)	Recursive (divide and conquer)
Best case	O(n)	O(n log n)
Worst case	O(n²)	O(n log n)
Space	O(1) (in-place)	O(n) (extra arrays)
Simplicity	Very simple	More complex
Use case	Small arrays, teaching	Large arrays, real-world use



---

4. Visual

Bubble Sort (n=4):

[5 3 8 2]
→ [3 5 2 8]
→ [3 2 5 8]
→ [2 3 5 8]

Merge Sort (n=4):

[5 3 8 2]
→ [5 3] [8 2]
→ [3 5] [2 8]
→ [2 3 5 8]


---

✅ In short:

Bubble Sort → easy but slow (O(n²)).

Merge Sort → fast and reliable (O(n log n)), used in real-world sorting.

CS50 teaches both: Bubble for intuition, Merge for power.

