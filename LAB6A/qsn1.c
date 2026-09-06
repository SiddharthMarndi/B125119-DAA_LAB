#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

Given an unsorted 1D array with n integer elements:

(i) Finding the maximum element:
    - Worst-case Time Complexity: O(n)
    - Derivation: Any algorithm must examine every element at least once; otherwise, an unexamined
      element could be larger than the identified maximum. Requires (n - 1) comparisons.
    - Space Complexity: O(1)

(ii) Finding the first and second largest elements:
    - Worst-case Time Complexity: O(n)
    - Derivation: Can be accomplished in a single pass by tracking two variables (max1 and max2)
      with at most 2n comparisons. Alternatively, using a tournament tree takes n + ceil(log2(n)) - 2
      comparisons, which is asymptotically O(n).
    - Space Complexity: O(1)

(iii) Finding the mean:
    - Worst-case Time Complexity: O(n)
    - Derivation: Summing all n elements requires visiting each element once (n additions),
      followed by one division: Mean = (sum / n).
    - Space Complexity: O(1)

(iv) Finding the median:
    - Worst-case Time Complexity: O(n) [using Median-of-Medians / BFPRT algorithm]
      or O(n^2) worst-case / O(n) average-case [using standard Quickselect].
      or O(n log n) [by sorting first].
    - Derivation: Finding the k-th order statistic where k = n/2 takes guaranteed O(n) worst-case
      time via the deterministic Median-of-Medians selection algorithm (T(n) <= T(n/5) + T(7n/10) + O(n)).
    - Space Complexity: O(1) to O(log n) auxiliary stack space.

(v) Finding the standard deviation:
    - Worst-case Time Complexity: O(n)
    - Derivation: Standard deviation sigma = sqrt( (1/n) * sum((x_i - mean)^2) ).
      Pass 1: Compute mean in O(n).
      Pass 2: Accumulate squared differences in O(n).
      Total time = O(n) + O(n) = O(n).
    - Space Complexity: O(1)

(vi) Finding the mode:
    - Worst-case Time Complexity:
        * O(n log n) by sorting the array first and finding the longest consecutive run.
        * O(n^2) if using a brute-force pairwise count without extra space.
        * O(n) average-case if using a Hash Table.
        * O(n) worst-case if the range of values is bounded (Counting/Buckets).
    - Derivation: For arbitrary unbounded integers in comparison-based models with O(1) extra space,
      sorting the array takes O(n log n) followed by a linear scan O(n), giving O(n log n).
    - Space Complexity: O(1) auxiliary space (if sorting in place).

(vii) Removing all duplicates:
    - Worst-case Time Complexity:
        * O(n log n) by sorting first, then running a two-pointer linear scan in O(n) to overwrite duplicates.
        * O(n^2) in-place without sorting via brute-force pair checking.
        * O(n) average time using a Hash Set.
    - Derivation: Comparison-based lower bound to detect all identical elements is Element Uniqueness,
      which is Omega(n log n). Thus, sorting in O(n log n) followed by an O(n) unique-filter yields O(n log n).
    - Space Complexity: O(1) auxiliary space (in-place).

(viii) Reversing the elements of the array:
    - Worst-case Time Complexity: O(n)
    - Derivation: Using two pointers (left = 0, right = n - 1), swap elements and move inward until
      they meet. Total number of swaps = floor(n / 2), each taking O(1), giving O(n).
    - Space Complexity: O(1)

(ix) Partitioning the array with respect to a given random pivot element so that all elements
    less than the pivot appear AFTER all elements greater than or equal to the pivot:
    - Note on condition: [Elements >= Pivot] followed by [Elements < Pivot].
    - Worst-case Time Complexity: O(n)
    - Derivation: A two-pointer Hoare-like partition scheme starting from both ends sweeps each
      element at most once, performing swaps in O(1). Total time is strictly O(n).
    - Space Complexity: O(1)
*/

int cmp_int(const void *a, const void *b) {
    int val_a = *(const int *)a;
    int val_b = *(const int *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void print_array(const int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");
}

void copy_array(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int find_max(const int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

void find_first_and_second_largest(const int arr[], int n, int *first, int *second) {
    if (n < 2) {
        printf("Error: Array needs at least 2 elements.\n");
        return;
    }
    int max1, max2;
    if (arr[0] >= arr[1]) {
        max1 = arr[0];
        max2 = arr[1];
    } else {
        max1 = arr[1];
        max2 = arr[0];
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }
    }
    *first = max1;
    *second = max2;
}

double find_mean(const int arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double find_median(const int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    copy_array(arr, temp, n);
    qsort(temp, n, sizeof(int), cmp_int);

    double median;
    if (n % 2 != 0) {
        median = temp[n / 2];
    } else {
        median = (temp[(n / 2) - 1] + temp[n / 2]) / 2.0;
    }
    free(temp);
    return median;
}

double find_standard_deviation(const int arr[], int n) {
    double mean = find_mean(arr, n);
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum_sq_diff / n);
}

int find_mode(const int arr[], int n, int *frequency) {
    int *temp = (int *)malloc(n * sizeof(int));
    copy_array(arr, temp, n);
    qsort(temp, n, sizeof(int), cmp_int);

    int mode_val = temp[0];
    int max_freq = 1;
    int curr_val = temp[0];
    int curr_freq = 1;

    for (int i = 1; i < n; i++) {
        if (temp[i] == curr_val) {
            curr_freq++;
        } else {
            if (curr_freq > max_freq) {
                max_freq = curr_freq;
                mode_val = curr_val;
            }
            curr_val = temp[i];
            curr_freq = 1;
        }
    }
    if (curr_freq > max_freq) {
        max_freq = curr_freq;
        mode_val = curr_val;
    }

    *frequency = max_freq;
    free(temp);
    return mode_val;
}

int remove_duplicates(int arr[], int n) {
    if (n <= 1) return n;

    qsort(arr, n, sizeof(int), cmp_int);

    int write_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[write_idx]) {
            write_idx++;
            arr[write_idx] = arr[i];
        }
    }
    return write_idx + 1; // new length
}

void reverse_array(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void partition_descending_pivot(int arr[], int n, int pivot_val) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        while (left <= right && arr[left] >= pivot_val) {
            left++;
        }
        while (left <= right && arr[right] < pivot_val) {
            right--;
        }
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements in the array (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    int *working_copy = (int *)malloc(n * sizeof(int));
    if (!arr || !working_copy) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input at index %d.\n", i);
            free(arr);
            free(working_copy);
            return 1;
        }
    }

    printf("\n ORIGINAL ARRAY \n");
    print_array(arr, n);

    int max_val = find_max(arr, n);
    printf("\n(i)   Maximum element                  : %d  [Complexity: O(n)]\n", max_val);

    if (n >= 2) {
        int first_max, second_max;
        find_first_and_second_largest(arr, n, &first_max, &second_max);
        printf("(ii)  1st and 2nd largest elements     : %d, %d  [Complexity: O(n)]\n", first_max, second_max);
    } else {
        printf("(ii)  1st and 2nd largest elements     : N/A (n < 2)\n");
    }

    double mean_val = find_mean(arr, n);
    printf("(iii) Mean                             : %.4lf  [Complexity: O(n)]\n", mean_val);

    double median_val = find_median(arr, n);
    printf("(iv)  Median                           : %.4lf  [Complexity: O(n log n) via sort / O(n) via Median-of-Medians]\n", median_val);

    double std_dev = find_standard_deviation(arr, n);
    printf("(v)   Standard Deviation               : %.4lf  [Complexity: O(n)]\n", std_dev);

    int mode_freq;
    int mode_val = find_mode(arr, n, &mode_freq);
    printf("(vi)  Mode                             : %d (occurs %d time(s))  [Complexity: O(n log n)]\n", mode_val, mode_freq);

    copy_array(arr, working_copy, n);
    int new_len = remove_duplicates(working_copy, n);
    printf("(vii) After Removing Duplicates (sorted): ");
    print_array(working_copy, new_len);
    printf("      [Complexity: O(n log n)]\n");

    copy_array(arr, working_copy, n);
    reverse_array(working_copy, n);
    printf("(viii)Reversed Array                   : ");
    print_array(working_copy, n);
    printf("      [Complexity: O(n)]\n");

    copy_array(arr, working_copy, n);
    int pivot_idx = rand() % n;
    int pivot_val = working_copy[pivot_idx];
    printf("(ix)  Partitioning around pivot = %d (from index %d):\n", pivot_val, pivot_idx);
    partition_descending_pivot(working_copy, n, pivot_val);
    printf("      Partitioned (>= %d, then < %d) : ", pivot_val, pivot_val);
    print_array(working_copy, n);
    printf("      [Complexity: O(n)]\n");

    free(arr);
    free(working_copy);
    return 0;
}