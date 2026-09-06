#include <stdio.h>
#include <stdlib.h>

/*


1. Mathematical Proof for O(n) Reversals:[cite: 1]
   - Goal: Sort a permutation p of integers {1, ..., n} using at most O(n) reversal operations.[cite: 1]
   - Selection / Pancake-style Construction:
     Consider placing elements into their correct final positions one by one, from k = 1 to n:
     For the k-th step (placing integer k at index k - 1):
       a. Locate the current index `pos` where integer k resides (where pos >= k - 1).
       b. If pos == k - 1, the element is already in place (0 reversals needed).
       c. Otherwise, perform at most 2 reversals:
          - Reversal 1: reverse(p, k - 1, pos).
            This flips the segment from index k - 1 to pos, bringing the element k directly to index k - 1.
          - (Even without a two-step flip, a single reversal reverse(p, k - 1, pos) places k at position k - 1;
             further relative order in that prefix is preserved because elements 1 to k-1 are already fixed).
     Therefore, placing each element k into its correct sorted position requires at most 1 reversal.
     Across all n elements, the total number of reversals is at most (n - 1) <= n, which is strictly O(n).

2. Sorting in O(n log^2 n) Cost when cost(reverse(p, i, j)) = |j - i| + 1:[cite: 1]
   - Definition: The cost of an operation reverse(p, i, j) is the length of the reversed range L = (j - i + 1).[cite: 1]
   - Divide-and-Conquer Merge Sort Strategy:
     To sort a subarray p[low ... high] of length m = high - low + 1:
       a. Divide: Recursively sort the left half p[low ... mid] and right half p[mid + 1 ... high],
          where mid = low + (m / 2) - 1.
       b. In-Place Block Exchange (Reversal Vector Merge):
          Standard merging can be accomplished in-place using cyclic block rotations via reversals.
          Rotating two adjacent contiguous blocks A of length |A| and B of length |B| (to transform AB -> BA)
          can be achieved using 3 reversals (the classic 3-reversal block-swap trick):
             1. reverse(A)         -> cost = |A|
             2. reverse(B)         -> cost = |B|
             3. reverse(A_rev B_rev) = BA -> cost = |A| + |B|
          Total reversal cost to exchange adjacent blocks A and B is:
             |A| + |B| + (|A| + |B|) = 2 * (|A| + |B|) = O(|A| + |B|).
       c. Recursive Block Merge (In-Place Merging via Binary Search / Median Split):
          To merge two sorted contiguous arrays A and B of combined length m:
          - Pick the median element of A.
          - Use binary search in B to find its corresponding insertion index.
          - Swap the right sub-block of A with the left sub-block of B using the 3-reversal rotation.
          - The cost of the 3 reversals at this merge step is O(m).
          - Recursively merge the two disjoint halves.
          - The recurrence for merging two sorted lists of total size m using this divide-and-conquer strategy is:
               M(m) = 2 * M(m / 2) + O(m)
            By the Master Theorem (Case 2), M(m) = O(m log m).
       d. Overall Sorting Recurrence:
          Let C(n) denote the total reversal cost to sort an array of size n:
             C(n) = 2 * C(n / 2) + M(n)
             C(n) = 2 * C(n / 2) + O(n log n)
          Applying the Master Theorem (Case 2 generalized, or substitution):
             - At recursion level i (from 0 to log2(n)), there are 2^i subproblems of size (n / 2^i).
             - The cost across level i is:
               2^i * O((n / 2^i) * log(n / 2^i)) <= 2^i * (n / 2^i) * O(log n) = O(n log n).
             - Summing over all log2(n) levels of the recursion tree:
               C(n) = sum_{i=0}^{log2(n)} O(n log n) = O(n log^2 n).
   - Thus, the total reversal cost is strictly bounded by O(n log^2 n).
*/

long long reverse_subsequence(int p[], int i, int j) {
    if (i >= j) return 0;

    long long cost = (long long)(j - i + 1);

    int left = i;
    int right = j;
    while (left < right) {
        int temp = p[left];
        p[left] = p[right];
        p[right] = temp;
        left++;
        right--;
    }

    return cost;
}

long long rotate_blocks(int p[], int left, int mid, int right) {
    if (left > mid || mid >= right) return 0;

    long long cost = 0;
    cost += reverse_subsequence(p, left, mid);
    cost += reverse_subsequence(p, mid + 1, right);
    cost += reverse_subsequence(p, left, right);

    return cost;
}

int find_upper_bound(const int p[], int low, int high, int val) {
    int l = low;
    int r = high;
    int ans = high + 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (p[mid] > val) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

long long in_place_reversal_merge(int p[], int l1, int r1, int l2, int r2) {
    if (l1 > r1 || l2 > r2) return 0;

    if (r1 - l1 + 1 == 1 && r2 - l2 + 1 == 1) {
        if (p[l1] > p[l2]) {
            return reverse_subsequence(p, l1, l2);
        }
        return 0;
    }

    long long cost = 0;

    if ((r1 - l1) >= (r2 - l2)) {
        int mid1 = l1 + (r1 - l1) / 2;
        int mid2 = find_upper_bound(p, l2, r2, p[mid1]);

        cost += rotate_blocks(p, mid1 + 1, r1, mid2 - 1);

        int new_mid = mid1 + (mid2 - l2);
        cost += in_place_reversal_merge(p, l1, mid1, mid1 + 1, new_mid);
        cost += in_place_reversal_merge(p, new_mid + 1, mid2 - 1 + (r1 - mid1), mid2, r2);
    } else {
        int mid2 = l2 + (r2 - l2) / 2;
        int mid1 = find_upper_bound(p, l1, r1, p[mid2]);

        cost += rotate_blocks(p, mid1, r1, mid2);

        int new_mid = mid1 + (mid2 - l2);
        cost += in_place_reversal_merge(p, l1, mid1 - 1, mid1, new_mid - 1);
        cost += in_place_reversal_merge(p, new_mid + 1, mid2 + (r1 - mid1 + 1), mid2 + 1, r2);
    }

    return cost;
}

long long reversal_sort(int p[], int low, int high) {
    if (low >= high) return 0;

    int mid = low + (high - low) / 2;
    long long cost = 0;

    cost += reversal_sort(p, low, mid);
    cost += reversal_sort(p, mid + 1, high);

    cost += in_place_reversal_merge(p, low, mid, mid + 1, high);

    return cost;
}

int sort_using_on_reversals(int arr[], int n) {
    int num_reversals = 0;

    for (int target = 1; target <= n; target++) {
        int target_idx = -1;
        for (int i = target - 1; i < n; i++) {
            if (arr[i] == target) {
                target_idx = i;
                break;
            }
        }

        if (target_idx != target - 1) {
            reverse_subsequence(arr, target - 1, target_idx);
            num_reversals++;
        }
    }

    return num_reversals;
}

void print_permutation(const int p[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", p[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

int main() {
    int n;
    printf("Enter the size of the permutation (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *p1 = (int *)malloc(n * sizeof(int));
    int *p2 = (int *)malloc(n * sizeof(int));

    printf("Enter %d integers (permutation of 1 to %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p1[i]);
        p2[i] = p1[i];
    }

    printf("\nInitial Permutation: ");
    print_permutation(p1, n);

    int reversals_count = sort_using_on_reversals(p1, n);
    printf("\nPart 1: Sorted using O(n) reversals algorithm:\n");
    print_permutation(p1, n);
    printf("Total number of reversal operations performed: %d (<= %d)\n", reversals_count, n);

    long long total_weighted_cost = reversal_sort(p2, 0, n - 1);
    printf("\nPart 2: Sorted using O(n log^2 n) cost divide-and-conquer merge algorithm:\n");
    print_permutation(p2, n);
    printf("Total weighted reversal cost: %lld\n", total_weighted_cost);

    free(p1);
    free(p2);
    return 0;
}