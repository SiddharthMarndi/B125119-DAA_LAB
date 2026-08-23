#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
ALGORITHM: k-Sum in O(n^(k-1) * log n) Time via Sorting & Binary Search

1. Input Representation:
   - Represent set S as a dynamic array of n distinct integers.
   - Read n, the set elements, k (the subset size), and T (the target sum).
2. Sorting Step:
   - Sort the array S in ascending order using QuickSort / Mergesort -> O(n log n).
3. Recursive / Nested Selection (k - 1 elements):
   - Fix (k - 1) distinct elements from S using (k - 1) nested loops or recursion.
   - Let the indices of the chosen (k - 1) elements be i_1 < i_2 < ... < i_{k-1}.
   - The number of distinct ways to choose (k - 1) elements is O(n^(k-1)).
   - Compute the partial sum: current_sum = S[i_1] + S[i_2] + ... + S[i_{k-1}].
   - The required k-th element is: target_k = T - current_sum.
4. Binary Search for the k-th Element:
   - Perform Binary Search in the sorted subarray S[i_{k-1} + 1 ... n - 1] for target_k.
   - Searching strictly to the right (index > i_{k-1}) ensures that all k elements
     are distinct and avoids duplicate combinations.
   - Binary Search takes O(log n) time per combination.
5. Termination:
   - If target_k is found, return true along with the k chosen numbers.
   - If all O(n^(k-1)) combinations are exhausted without a match, return false.

Complexity Analysis:
- Sorting: O(n log n)
- Combination Search: O(n^(k-1)) combinations * O(log n) search = O(n^(k-1) * log n)
- Total Time Complexity: O(n^(k-1) * log n)
- Space Complexity: O(k) auxiliary stack/buffer space for recursion and combination storage.

*/

int compare(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int binary_search(const int arr[], int low, int high, long long target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

bool find_k_sum_helper(const int S[], int n, int k, long long remaining_target,
                       int start_idx, int depth, int chosen_indices[]) {
    if (depth == k - 1) {
        int found_idx = binary_search(S, start_idx, n - 1, remaining_target);
        if (found_idx != -1) {
            chosen_indices[depth] = found_idx;
            return true;
        }
        return false;
    }

    for (int i = start_idx; i <= n - (k - depth); i++) {
        chosen_indices[depth] = i;
        if (find_k_sum_helper(S, n, k, remaining_target - S[i], i + 1, depth + 1, chosen_indices)) {
            return true;
        }
    }

    return false;
}

bool has_k_sum(int S[], int n, int k, long long T, int result_elements[]) {
    if (k > n || k <= 0) return false;

    qsort(S, n, sizeof(int), compare);

    if (k == 1) {
        int idx = binary_search(S, 0, n - 1, T);
        if (idx != -1) {
            result_elements[0] = S[idx];
            return true;
        }
        return false;
    }

    int *chosen_indices = (int *)malloc(k * sizeof(int));
    bool found = find_k_sum_helper(S, n, k, T, 0, 0, chosen_indices);

    if (found) {
        for (int i = 0; i < k; i++) {
            result_elements[i] = S[chosen_indices[i]];
        }
    }

    free(chosen_indices);
    return found;
}

int main() {
    int n, k;
    long long T;

    printf("Enter number of elements in set S (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid set size.\n");
        return 1;
    }

    int *S = (int *)malloc(n * sizeof(int));
    if (!S) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers for set S: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &S[i]) != 1) {
            printf("Invalid input for set element.\n");
            free(S);
            return 1;
        }
    }

    printf("Enter subset size (k): ");
    if (scanf("%d", &k) != 1 || k <= 0 || k > n) {
        printf("Invalid subset size k (must be between 1 and n).\n");
        free(S);
        return 1;
    }

    printf("Enter target sum (T): ");
    if (scanf("%lld", &T) != 1) {
        printf("Invalid target sum.\n");
        free(S);
        return 1;
    }

    int *result = (int *)malloc(k * sizeof(int));
    bool exists = has_k_sum(S, n, k, T, result);

    if (exists) {
        printf("\nResult: FOUND -> %d elements sum to %lld:\n", k, T);
        for (int i = 0; i < k; i++) {
            printf("%d%s", result[i], (i == k - 1) ? "" : " + ");
        }
        printf(" = %lld\n", T);
    } else {
        printf("\nResult: NO subset of %d elements sums to %lld.\n", k, T);
    }

    free(result);
    free(S);
    return 0;
}