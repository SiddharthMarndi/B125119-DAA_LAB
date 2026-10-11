
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

/*
Algorithm: Minimum Number of Meeting Rooms

1. Sort meetings by their start times.
2. Maintain a min-heap of meeting end times.
3. For each meeting:
   a. If the earliest room is free, reuse it.
   b. Insert the current meeting's end time.
   c. Track the maximum heap size.
4. Display the maximum heap size.

Time Complexity: O(n log n)
Auxiliary Space: O(n)
*/

typedef struct {
    int start;
    int end;
} Meeting;

Meeting meetings[MAX];
int heap[MAX];
int heapSize = 0;

int compareMeetings(const void *a, const void *b) {
    const Meeting *x = a;
    const Meeting *y = b;

    if (x->start < y->start)
        return -1;
    if (x->start > y->start)
        return 1;
    return x->end - y->end;
}

void insert(int endTime) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] > endTime) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = endTime;
}

int extractMin(void) {
    int result = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (i * 2 <= heapSize) {
        child = i * 2;

        if (child + 1 <= heapSize &&
            heap[child + 1] < heap[child])
            child++;

        if (last <= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int main(void) {
    int n;

    printf("Enter number of meetings: ");

    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter start and end time for meeting %d: ", i + 1);

        if (scanf("%d %d", &meetings[i].start,
                  &meetings[i].end) != 2 ||
            meetings[i].start >= meetings[i].end) {
            printf("Invalid meeting interval.\n");
            return 1;
        }
    }

    if (n == 0) {
        printf("Minimum number of meeting rooms = 0\n");
        return 0;
    }

    qsort(meetings, n, sizeof(Meeting), compareMeetings);

    int maxRooms = 0;

    for (int i = 0; i < n; i++) {
        if (heapSize > 0 && heap[1] <= meetings[i].start)
            extractMin();

        insert(meetings[i].end);

        if (heapSize > maxRooms)
            maxRooms = heapSize;
    }

    printf("Minimum number of meeting rooms = %d\n", maxRooms);

    return 0;
}
