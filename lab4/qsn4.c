#include <stdio.h>
#include <stdlib.h>

/*
ALGORITHM: Maximum Overlapping Intervals (Sweep-Line) in O(n log n) Time

1. Input Representation:
   - Deconstruct each person's interval [a_i, b_i] into two discrete events:
       - Entry Event: (time = a_i, type = +1)
       - Exit Event:  (time = b_i, type = -1)
   - Store all 2n events in an array of `Event` structs.
2. Sorting Step:
   - Sort the 2n events in ascending order of their timestamp using 
     QuickSort / Mergesort / C qsort() -> O(2n log(2n)) = O(n log n).
   - (Since all timestamps are distinct, no tie-breaking logic is necessary).
3. Linear Sweep (Prefix Running Sum):
   - Maintain a running counter `current_count = 0`.
   - Maintain `max_count = 0` and `peak_time = -1`.
   - Iterate through the sorted events from index 0 to 2n - 1:
       - Update: `current_count += event.type`
       - If `current_count > max_count`:
           - `max_count = current_count`
           - `peak_time = event.time`
4. The peak occurs at `peak_time` (specifically, during the interval starting 
   at `peak_time` until the subsequent event), with a maximum of `max_count` people.

Complexity Analysis:
- Time Complexity:
    - Event Creation: O(n)
    - Sorting 2n events: O(n log n)
    - Single-pass sweep: O(n)
    - Total Time Complexity: O(n log n)
- Space Complexity: O(n) auxiliary space to store the 2n events.

*/

typedef enum {
    EXIT = -1,
    ENTRY = 1
} EventType;

typedef struct {
    double time;
    EventType type;
    int person_id;
} Event;

int compare_events(const void *a, const void *b) {
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;
    if (e1->time < e2->time) return -1;
    if (e1->time > e2->time) return 1;
    return 0;
}

void find_peak_time(Event events[], int total_events, int *max_people, double *peak_time) {
    qsort(events, total_events, sizeof(Event), compare_events);

    int current_people = 0;
    *max_people = 0;
    *peak_time = 0.0;

    for (int i = 0; i < total_events; i++) {
        current_people += events[i].type;

        if (current_people > *max_people) {
            *max_people = current_people;
            *peak_time = events[i].time;
        }
    }
}

int main() {
    int n;
    printf("Enter number of persons attending the party (n): ");
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

    printf("Enter entry time  and exit time  for each person :\n");
    for (int i = 0; i < n; i++) {
        double entry_time, exit_time;
        printf("Person %d: ", i + 1);
        if (scanf("%lf %lf", &entry_time, &exit_time) != 2 || exit_time <= entry_time) {
            printf("Invalid time intervals. Ensure b_i > a_i.\n");
            free(events);
            return 1;
        }

        events[2 * i].time = entry_time;
        events[2 * i].type = ENTRY;
        events[2 * i].person_id = i + 1;

        events[2 * i + 1].time = exit_time;
        events[2 * i + 1].type = EXIT;
        events[2 * i + 1].person_id = i + 1;
    }

    int max_people = 0;
    double peak_time = 0.0;

    find_peak_time(events, total_events, &max_people, &peak_time);

    printf("\n================ RESULT ================\n");
    printf("Peak Attendance : %d people\n", max_people);
    printf("Peak Time       : Starts at time %.2lf\n", peak_time);
    printf("\n");

    free(events);
    return 0;
}