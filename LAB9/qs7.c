
#include <stdio.h>
#include <limits.h>

#define MAX 100000

/*
Algorithm: Minimise Deviation using Max-Heap

1. Multiply every odd element by 2.
2. Insert all elements into a max-heap.
3. Track the minimum element.
4. While the maximum element is even:
   a. Remove the maximum element.
   b. Divide it by 2.
   c. Insert it back into the heap.
   d. Update the minimum deviation.
5. Stop when the maximum becomes odd.
6. Print the minimum deviation.

Time Complexity: O(n log n + n log M)
Auxiliary Space: O(n)
where M is the maximum transformed element.
*/

long long heap[MAX];
int heapSize = 0;

void insert(long long value) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = value;
}

long long extractMax(void) {
    long long result = heap[1];
    long long last = heap[heapSize--];
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

long long peekMax(void) {
    return heap[1];
}

int main(void) {
    int n;
    long long x, minimum = LLONG_MAX;
    long long deviation;

    printf("Enter number of elements: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &x) != 1 || x <= 0 ||
            x > LLONG_MAX / 2) {
            printf("Invalid element.\n");
            return 1;
        }

        if (x % 2 != 0)
            x *= 2;

        insert(x);

        if (x < minimum)
            minimum = x;
    }

    deviation = peekMax() - minimum;

    while (peekMax() % 2 == 0) {
        long long maximum = extractMax();
        long long reduced = maximum / 2;

        insert(reduced);

        if (reduced < minimum)
            minimum = reduced;

        long long currentDeviation = peekMax() - minimum;

        if (currentDeviation < deviation)
            deviation = currentDeviation;
    }

    printf("Minimum deviation = %lld\n", deviation);

    return 0;
}
