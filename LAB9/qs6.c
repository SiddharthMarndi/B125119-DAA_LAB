
#include <stdio.h>
#include <string.h>

#define MAX 10000
#define CHARSET 256

/*
Algorithm: Reorganise String with K-Distance Apart

1. Count the frequency of each character.
2. Insert characters into a max-heap by frequency.
3. At each position, select the available character
   with the highest frequency.
4. Put the used character into a cooldown queue.
5. Release a character when K positions have passed.
6. If no character is available before completion,
   return an empty string.

Time Complexity: O(n log C)
Auxiliary Space: O(n + C)
where n = string length and C = character set size.
*/

typedef struct {
    unsigned char ch;
    int freq;
} Entry;

Entry heap[CHARSET];
int heapSize = 0;

typedef struct {
    unsigned char ch;
    int freq;
    int release;
} Waiting;

Waiting queue[MAX];
int front = 0, rear = 0;

int higherPriority(Entry a, Entry b) {
    if (a.freq != b.freq)
        return a.freq > b.freq;
    return a.ch < b.ch;
}

void push(Entry item) {
    int i = ++heapSize;

    while (i > 1 && higherPriority(item, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = item;
}

Entry pop(void) {
    Entry result = heap[1];
    Entry last = heap[heapSize--];
    int i = 1, child;

    while (i * 2 <= heapSize) {
        child = i * 2;

        if (child + 1 <= heapSize &&
            higherPriority(heap[child + 1], heap[child]))
            child++;

        if (higherPriority(last, heap[child]))
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

int main(void) {
    char s[MAX], result[MAX];
    int frequency[CHARSET] = {0};
    int n, k;

    printf("Enter string: ");
    if (scanf("%9999s", s) != 1) {
        printf("Invalid string.\n");
        return 1;
    }

    printf("Enter K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid K.\n");
        return 1;
    }

    n = (int)strlen(s);

    if (k <= 1) {
        printf("Reorganised string: %s\n", s);
        return 0;
    }

    for (int i = 0; i < n; i++)
        frequency[(unsigned char)s[i]]++;

    for (int i = 0; i < CHARSET; i++) {
        if (frequency[i] > 0) {
            Entry item = {(unsigned char)i, frequency[i]};
            push(item);
        }
    }

    int length = 0;

    for (int pos = 0; pos < n; pos++) {
        while (front < rear && queue[front].release <= pos) {
            Entry item = {queue[front].ch, queue[front].freq};
            push(item);
            front++;
        }

        if (heapSize == 0) {
            printf("Reorganised string: \n");
            return 0;
        }

        Entry item = pop();
        result[length++] = (char)item.ch;
        item.freq--;

        if (item.freq > 0) {
            queue[rear].ch = item.ch;
            queue[rear].freq = item.freq;
            queue[rear].release = pos + k;
            rear++;
        }
    }

    result[length] = '\0';

    printf("Reorganised string: %s\n", result);

    return 0;
}
