#include <stdio.h>
#include <stdlib.h>

/*
ALGORITHM: Merge Overlapping Intervals in O(n log n) Time

1. Input Representation:
   - Represent each interval as a struct `Interval` with `start` (x_i) and `end` (y_i).
   - Read n and the n intervals from user input into a dynamically allocated array.
2. Sorting Step:
   - Sort the array of intervals in ascending order of their `start` values.
   - Break ties by sorting on `end` values.
   - Sorting takes O(n log n) time using QuickSort / Mergesort / C qsort().
3. Merging Step (Linear Scan):
   - Allocate an array `merged` of capacity n for the output.
   - Initialize `merged[0]` with the first interval and set `merged_count = 1`.
   - Iterate through the remaining intervals from index 1 to n - 1:
       Let `last` be the currently active merged interval (`merged[merged_count - 1]`)
       and `curr` be the current interval (`intervals[i]`):
       a. Overlap / Touch condition: If `curr.start <= last.end`:
            - Merge by extending the current end: `last.end = max(last.end, curr.end)`.
       b. Disjoint condition: If `curr.start > last.end`:
            - No overlap; append `curr` as a new interval in `merged`.
            - `merged[merged_count++] = curr`.
4. Output Representation:
   - Return the `merged` array of size `merged_count`.

Complexity Analysis:
- Time Complexity:
    - Sorting intervals: O(n log n)
    - Merging pass: O(n)
    - Total Time Complexity: O(n log n)
- Space Complexity:
    - O(n) auxiliary space to store and return the merged output list.

*/

typedef struct {
    double start; // x_i
    double end;   // y_i
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *i1 = (const Interval *)a;
    const Interval *i2 = (const Interval *)b;

    if (i1->start < i2->start) return -1;
    if (i1->start > i2->start) return 1;
    if (i1->end < i2->end) return -1;
    if (i1->end > i2->end) return 1;
    return 0;
}

Interval* merge_intervals(Interval intervals[], int n, int *out_count) {
    if (n <= 0) {
        *out_count = 0;
        return NULL;
    }

    qsort(intervals, n, sizeof(Interval), compare_intervals);

    Interval *merged = (Interval *)malloc(n * sizeof(Interval));
    if (!merged) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    merged[count] = intervals[0];
    count++;

    for (int i = 1; i < n; i++) {
        Interval *last = &merged[count - 1];
        Interval curr = intervals[i];

        if (curr.start <= last->end) {
            if (curr.end > last->end) {
                last->end = curr.end;
            }
        } else {
            merged[count] = curr;
            count++;
        }
    }

    *out_count = count;
    return merged;
}

void print_intervals(const Interval arr[], int count) {
    printf("{ ");
    for (int i = 0; i < count; i++) {
        printf("(%.2f, %.2f)%s", arr[i].start, arr[i].end, (i == count - 1) ? "" : ", ");
    }
    printf(" }\n");
}

int main() {
    int n;
    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of intervals.\n");
        return 1;
    }

    Interval *intervals = (Interval *)malloc(n * sizeof(Interval));
    if (!intervals) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d intervals:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Interval %d: ", i + 1);
        if (scanf("%lf %lf", &intervals[i].start, &intervals[i].end) != 2 || intervals[i].end < intervals[i].start) {
            printf("Invalid interval boundaries. Ensure y_i >= x_i.\n");
            free(intervals);
            return 1;
        }
    }

    printf("\n--- Original Intervals ---\n");
    print_intervals(intervals, n);

    int merged_count = 0;
    Interval *merged = merge_intervals(intervals, n, &merged_count);

    printf("\n--- Merged Intervals (O(n log n)) ---\n");
    print_intervals(merged, merged_count);

    free(intervals);
    free(merged);
    return 0;
}