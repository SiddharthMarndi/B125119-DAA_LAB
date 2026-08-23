#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*

ALGORITHM: Pair Sum from Two Sets in O(n log n) Time

1. Input Representation:
   - Represent sets S1 and S2 as dynamic integer arrays of size n.
   - Read n, elements of S1, elements of S2, and the target sum x from user input.
2. Sorting Step:
   - Sort set S1 in ascending order using QuickSort / Mergesort / C qsort() -> O(n log n).
   - Sort set S2 in ascending order using QuickSort / Mergesort / C qsort() -> O(n log n).
3. Two-Pointer Search:
   - Initialize pointer `i = 0` (pointing to the smallest element of S1).
   - Initialize pointer `j = n - 1` (pointing to the largest element of S2).
   - Loop while (i < n and j >= 0):
       a. Compute current_sum = S1[i] + S2[j].
       b. If current_sum == x:
            Pair found! Return (S1[i], S2[j]).
       c. Else if current_sum < x:
            The sum is too small. Increase it by moving `i` rightward (i++).
       d. Else (current_sum > x):
            The sum is too large. Decrease it by moving `j` leftward (j--).
4. If pointers go out of bounds without a match, no such pair exists.

Complexity Analysis:
- Time Complexity:
    - Sorting S1 and S2: 2 * O(n log n) = O(n log n)
    - Two-pointer scan: O(n + n) = O(n)
    - Total Time: O(n log n)
- Auxiliary Space Complexity: O(1) beyond the input arrays (in-place sort/scan).

Alternative Valid Approach:
- Sort only S2 in O(n log n).
- For each a in S1, binary search for (x - a) in S2 -> n * O(log n) = O(n log n).

*/

int compare(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

bool find_pair_sum(int S1[], int S2[], int n, int x, int *out_a, int *out_b) {
    qsort(S1, n, sizeof(int), compare);
    qsort(S2, n, sizeof(int), compare);

    int i = 0;
    int j = n - 1;

    while (i < n && j >= 0) {
        int current_sum = S1[i] + S2[j];

        if (current_sum == x) {
            *out_a = S1[i];
            *out_b = S2[j];
            return true;
        } else if (current_sum < x) {
            i++; 
        } else {
            j--; 
        }
    }

    return false;
}

void print_array(const int arr[], int n) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" }\n");
}

int main() {
    int n;
    printf("Enter the size of the sets (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid set size.\n");
        return 1;
    }

    int *S1 = (int *)malloc(n * sizeof(int));
    int *S2 = (int *)malloc(n * sizeof(int));
    if (!S1 || !S2) {
        printf("Memory allocation failed.\n");
        free(S1);
        free(S2);
        return 1;
    }

    printf("Enter %d elements for Set S1: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &S1[i]) != 1) {
            printf("Invalid input for S1.\n");
            free(S1);
            free(S2);
            return 1;
        }
    }

    printf("Enter %d elements for Set S2: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &S2[i]) != 1) {
            printf("Invalid input for S2.\n");
            free(S1);
            free(S2);
            return 1;
        }
    }

    int x;
    printf("Enter target sum (x): ");
    if (scanf("%d", &x) != 1) {
        printf("Invalid target sum.\n");
        free(S1);
        free(S2);
        return 1;
    }

    int elem_s1, elem_s2;
    bool exists = find_pair_sum(S1, S2, n, x, &elem_s1, &elem_s2);

    printf("\nSorted S1: ");
    print_array(S1, n);
    printf("Sorted S2: ");
    print_array(S2, n);

    if (exists) {
        printf("\nResult: Pair FOUND -> %d (from S1) + %d (from S2) = %d\n", elem_s1, elem_s2, x);
    } else {
        printf("\nResult: NO pair exists such that an element from S1 and an element from S2 sum to %d.\n", x);
    }

    free(S1);
    free(S2);
    return 0;
}