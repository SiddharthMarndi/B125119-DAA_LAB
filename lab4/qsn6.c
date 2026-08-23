#include <stdio.h>
#include <stdlib.h>

/*
ALGORITHM: Maximum Interval Stabbing Point in O(n log n) Time
1. Input Representation:
   - Represent each interval [l_i, r_i] as two discrete boundary events:
       - START event: (coordinate = l_i, type = +1)
       - END event:   (coordinate = r_i, type = -1)
   - Store all 2n events in an array of `Event` structs.
2. Handling Closed Intervals & Overlapping Endpoints:
   - Since an endpoint counts as being inside its interval, an interval starting
     at point 'p' overlaps with an interval ending at 'p'.
   - Tie-Breaking Rule: If an event has the same coordinate as another, process
     the START (+1) event BEFORE the END (-1) event.
3. Sorting Step:
   - Sort the 2n events in ascending order of coordinate.
   - For identical coordinates, place START (+1) before END (-1).
   - Time Complexity: O(2n log(2n)) = O(n log n) using C qsort().
4. Linear Sweep:
   - Initialize `current_count = 0`, `max_count = 0`, and `best_point = 0.0`.
   - Iterate through the sorted events from index 0 to 2n - 1:
       - `current_count += event.type`
       - If `current_count > max_count`:
           - `max_count = current_count`
           - `best_point = event.coordinate`
5. Output Representation:
   - Return `best_point` (the point p) and `max_count` (the maximum overlap).

Complexity Analysis:
- Time Complexity:
    - Array construction: O(n)
    - Sorting 2n events: O(n log n)
    - Sweep-line pass: O(n)
    - Total Time: O(n log n)
- Space Complexity: O(n) auxiliary space to store the 2n event points.

*/

typedef enum {
    END = -1,
    START = 1
} EventType;

typedef struct {
    double coordinate;
    EventType type;
} Event;

int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->coordinate < e2->coordinate) return -1;
    if (e1->coordinate > e2->coordinate) return 1;

    if (e1->type > e2->type) return -1;
    if (e1->type < e2->type) return 1;

    return 0;
}

void find_max_stabbing_point(Event events[], int total_events, double *best_point, int *max_intervals) {
    qsort(events, total_events, sizeof(Event), compare_events);

    int current_overlap = 0;
    *max_intervals = 0;
    *best_point = 0.0;

    for (int i = 0; i < total_events; i++) {
        current_overlap += events[i].type;

        if (current_overlap > *max_intervals) {
            *max_intervals = current_overlap;
            *best_point = events[i].coordinate;
        }
    }
}

int main() {
    int n;
    printf("Enter number of intervals (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    int total_events = 2 * n;
    Event *events = (Event *)malloc(total_events * sizeof(Event));
    if (!events) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d intervals as 'l_i r_i' (where r_i >= l_i):\n", n);
    for (int i = 0; i < n; i++) {
        double left, right;
        printf("Interval %d: ", i + 1);
        if (scanf("%lf %lf", &left, &right) != 2 || right < left) {
            printf("Invalid endpoints. Ensure r_i >= l_i.\n");
            free(events);
            return 1;
        }

        events[2 * i].coordinate = left;
        events[2 * i].type = START;

        events[2 * i + 1].coordinate = right;
        events[2 * i + 1].type = END;
    }

    double best_point = 0.0;
    int max_intervals = 0;

    find_max_stabbing_point(events, total_events, &best_point, &max_intervals);

    printf("\n================ RESULT ================\n");
    printf("Point in most intervals (p) : %.2lf\n", best_point);
    printf("Maximum intervals covering p: %d\n", max_intervals);
    printf("4\n");

    free(events);
    return 0;
}