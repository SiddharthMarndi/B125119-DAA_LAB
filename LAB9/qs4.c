
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

/*
Algorithm: Minimum Cost to Connect Sticks

1. Insert all stick lengths into a min-heap.
2. While more than one stick remains:
   a. Extract the two smallest sticks.
   b. Add their sum to the total cost.
   c. Insert the combined stick back into the heap.
3. Display the minimum total cost.

Time Complexity: O(n log n)
Auxiliary Space: O(n)
*/

long long heap[MAX];
int heapSize = 0;

void insert(long long value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] > value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

long long extractMin(void) {
    long long result = heap[1];
    long long last = heap[heapSize--];
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
    long long length, totalCost = 0;

    printf("Enter number of sticks: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    printf("Enter lengths of the sticks:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &length) != 1 || length <= 0) {
            printf("Invalid stick length.\n");
            return 1;
        }

        insert(length);
    }

    while (heapSize > 1) {
        long long x = extractMin();
        long long y = extractMin();

        if (x > 0 && y > 0 && x > 9223372036854775807LL - y) {
            printf("Stick length overflow.\n");
            return 1;
        }

        long long cost = x + y;

        if (totalCost > 9223372036854775807LL - cost) {
            printf("Total cost overflow.\n");
            return 1;
        }

        totalCost += cost;
        insert(cost);
    }

    printf("Minimum total connection cost = %lld\n", totalCost);

    return 0;
}
