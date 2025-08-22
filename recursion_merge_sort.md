📝 Notes: Recursion with merge_sort and merge (C)


---

1. Your Functions Recap

From your Tideman code:

void merge_sort(pair array[], int size) {
    if (size == 1) {
        return; // base case
    }

    int mid = size / 2;
    int end = size - mid;

    pair left[mid];
    pair right[end];

    for (int i = 0; i < mid; i++) {
        left[i] = array[i];
    }
    for (int i = 0; i < end; i++) {
        right[i] = array[i + mid];
    }

    merge_sort(left, mid);   // recursive downcall
    merge_sort(right, end);  // recursive downcall

    merge(size, mid, array, left, right); // combine results
}

void merge(int size, int mid, pair array[], pair left[], pair right[]) {
    int i = 0, j = 0, k = 0;
    while (i < size) {
        if (k == size - mid) {
            array[i++] = left[j++];
        }
        else if (j == mid) {
            array[i++] = right[k++];
        }
        else if (preferences[left[j].winner][left[j].loser] >
                 preferences[right[k].winner][right[k].loser]) {
            array[i++] = left[j++];
        }
        else {
            array[i++] = right[k++];
        }
    }
}


---

2. Base Case and Recursive Case

Base case:
If the array has only 1 element → already sorted → return.

Recursive case:
Split into two halves → sort each half recursively → merge them.



---

3. Downcalls (Recursion)

Example: Sorting array of 8 pairs

merge_sort(8) → split into 4 + 4
    merge_sort(4) → split into 2 + 2
        merge_sort(2) → split into 1 + 1
            merge_sort(1) → base case (return)
            merge_sort(1) → base case (return)
        merge() → combine 2 elements
        merge_sort(2) → split into 1 + 1
            merge_sort(1) → return
            merge_sort(1) → return
        merge() → combine 2 elements
    merge() → combine 4 elements
    (same for right half)
merge() → combine 8 elements

Each downcall = deeper split.

Each upcall = merge results.



---

4. Upcalls (Returning)

When recursion hits size == 1, it returns immediately.

Then the merge() function runs as the stack unwinds.

Sorting happens on the way back up (upcalls).



---

5. Stack Visualization

Call merge_sort(4) on [8, 5, 2, 7]

Downcalls:

merge_sort([8,5,2,7], size=4)
 ├─ merge_sort([8,5], size=2)
 │   ├─ merge_sort([8], size=1) → return
 │   ├─ merge_sort([5], size=1) → return
 │   └─ merge([8], [5]) → [5,8]
 ├─ merge_sort([2,7], size=2)
 │   ├─ merge_sort([2], size=1) → return
 │   ├─ merge_sort([7], size=1) → return
 │   └─ merge([2], [7]) → [2,7]
 └─ merge([5,8], [2,7]) → [2,5,7,8]

Upcalls:

Merge [8] + [5]

Merge [2] + [7]

Merge [5,8] + [2,7]
✅ Sorted array.



---

6. Key Takeaways

Downcalls split the array into smaller and smaller chunks (divide).

Base case = single element, already sorted.

Upcalls merge the smaller sorted arrays into larger ones (conquer).

Sorting is built during the unwinding phase of recursion.



---

✅ In short:
Your merge_sort is a classic divide-and-conquer recursive algorithm:

Downcalls = keep splitting.

Upcalls = merge results.

Final sorted array emerges at the top level after all upcalls.

