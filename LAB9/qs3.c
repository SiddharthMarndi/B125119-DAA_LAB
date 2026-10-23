
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

/*
Algorithm: Minimum Refuelling Stops

1. Sort stations by distance from the origin.
2. Initialize current fuel to F and stops to zero.
3. Insert the fuel amounts of all reachable stations
   into a max-heap.
4. While the target is not reachable:
   a. If the heap is empty, return -1.
   b. Refuel using the largest fuel amount in the heap.
   c. Increase the number of stops.
5. Return the number of stops.

Time Complexity: O(n log n)
Auxiliary Space: O(n)
*/

typedef struct {
    int distance;
    int fuel;
} Station;

Station stations[MAX];
int heap[MAX];
int heapSize = 0;

int compareStations(const void *a, const void *b) {
    const Station *x = a;
    const Station *y = b;

    if (x->distance < y->distance)
        return -1;
    if (x->distance > y->distance)
        return 1;
    return 0;
}

void push(int fuel) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < fuel) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = fuel;
}

int pop(void) {
    int result = heap[1];
    int last = heap[heapSize--];
    int i = 1, child;

    while (i * 2 <= heapSize) {
        child = i * 2;

        if (child + 1 <= heapSize &&
            heap[child + 1] > heap[child])
            child++;

        if (last >= heap[child])
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int minimumStops(int D, int F, int n) {
    long long reach = F;
    int i = 0, stops = 0;

    while (reach < D) {
        while (i < n && stations[i].distance <= reach) {
            push(stations[i].fuel);
            i++;
        }

        if (heapSize == 0)
            return -1;

        reach += pop();
        stops++;
    }

    return stops;
}

int main(void) {
    int D, F, n;

    printf("Enter target distance D: ");
    if (scanf("%d", &D) != 1 || D < 0) {
        printf("Invalid target distance.\n");
        return 1;
    }

    printf("Enter initial fuel F: ");
    if (scanf("%d", &F) != 1 || F < 0) {
        printf("Invalid initial fuel.\n");
        return 1;
    }

    printf("Enter number of stations: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > MAX) {
        printf("Invalid number of stations.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter distance and fuel for station %d: ", i + 1);

        if (scanf("%d %d", &stations[i].distance,
                  &stations[i].fuel) != 2 ||
            stations[i].distance < 0 ||
            stations[i].distance > D ||
            stations[i].fuel < 0) {
            printf("Invalid station data.\n");
            return 1;
        }
    }

    qsort(stations, n, sizeof(Station), compareStations);

    int result = minimumStops(D, F, n);

    if (result == -1)
        printf("Target cannot be reached.\n");
    else
        printf("Minimum refuelling stops = %d\n", result);

    return 0;
}
