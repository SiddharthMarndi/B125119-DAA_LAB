#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int change;   // +1 for birth, -1 for death
} Event;

// Comparator for sorting events
// Events are sorted by year.
// If two events have the same year,
// death (-1) is processed before birth (+1).
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year) {
        return e1->year - e2->year;
    }

    return e1->change - e2->change;
}

int main() {
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read birth and death years
    for (int i = 0; i < n; i++) {
        int birth, death;

        printf("Enter birth year and death year for scientist %d: ",
               i + 1);

        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].change = +1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].change = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    // Process events
    for (int i = 0; i < 2 * n; i++) {
        alive += events[i].change;

        if (alive > maximum) {
            maximum = alive;
            bestYear = events[i].year;
        }
    }

    printf("\n--- Best Time to Be Alive ---\n");
    printf("Year with maximum number of scientists alive: %d\n",
           bestYear);
    printf("Maximum number of scientists alive: %d\n",
           maximum);

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");

    free(events);

    return 0;
}