
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*
Algorithm: Canonical Huffman Coding

1. Store symbols and frequencies.
2. Build a min-heap of Huffman nodes.
3. Repeatedly combine the two minimum-frequency nodes.
4. Traverse the final tree to obtain code lengths.
5. Sort symbols by length and then lexicographically.
6. Generate canonical codes and display the codebook.

Time Complexity: O(n log n)
Auxiliary Space: O(n)
*/

typedef struct Node {
    char symbol;
    long long freq;
    int minSymbol;
    struct Node *left, *right;
} Node;

Node *heap[2 * MAX];
int heapSize = 0;

char symbols[MAX];
long long frequencies[MAX];
int lengths[MAX];
char codes[MAX][MAX];
int n;

Node *createNode(char symbol, long long freq,
                 Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;

    int minSymbol = (unsigned char)symbol;

    if (left != NULL && left->minSymbol < minSymbol)
        minSymbol = left->minSymbol;

    if (right != NULL && right->minSymbol < minSymbol)
        minSymbol = right->minSymbol;

    node->minSymbol = minSymbol;
    return node;
}

int smaller(Node *a, Node *b) {
    if (a->freq != b->freq)
        return a->freq < b->freq;

    return a->minSymbol < b->minSymbol;
}

void push(Node *node) {
    int i = ++heapSize;

    while (i > 1 && smaller(node, heap[i / 2])) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = node;
}

Node *pop(void) {
    Node *result = heap[1];
    Node *last = heap[heapSize--];

    int i = 1, child;

    while (i * 2 <= heapSize) {
        child = i * 2;

        if (child + 1 <= heapSize &&
            smaller(heap[child + 1], heap[child]))
            child++;

        if (smaller(last, heap[child]))
            break;

        heap[i] = heap[child];
        i = child;
    }

    if (heapSize > 0)
        heap[i] = last;

    return result;
}

void findLengths(Node *root, int depth) {
    if (root->left == NULL && root->right == NULL) {
        int index = root->symbol;

        lengths[index] = depth == 0 ? 1 : depth;
        return;
    }

    if (root->left != NULL)
        findLengths(root->left, depth + 1);

    if (root->right != NULL)
        findLengths(root->right, depth + 1);
}

int compareSymbols(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (lengths[x] != lengths[y])
        return lengths[x] - lengths[y];

    return x - y;
}

void incrementCode(char *code, int length) {
    int i = length - 1;

    while (i >= 0 && code[i] == '1') {
        code[i] = '0';
        i--;
    }

    if (i >= 0)
        code[i] = '1';
}

void generateCanonical(void) {
    int order[MAX];

    for (int i = 0; i < n; i++)
        order[i] = (unsigned char)symbols[i];

    qsort(order, n, sizeof(int), compareSymbols);

    char current[MAX];
    int previousLength = lengths[order[0]];

    memset(current, '0', previousLength);
    current[previousLength] = '\0';

    strcpy(codes[order[0]], current);

    for (int i = 1; i < n; i++) {
        int symbol = order[i];
        int length = lengths[symbol];

        incrementCode(current, previousLength);

        for (int j = previousLength; j < length; j++)
            current[j] = '0';

        current[length] = '\0';

        strcpy(codes[symbol], current);
        previousLength = length;
    }
}

int main(void) {
    printf("Enter number of symbols (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char symbol;
        long long freq;

        printf("Enter symbol and frequency: ");

        if (scanf(" %c %lld", &symbol, &freq) != 2 ||
            freq <= 0 || (unsigned char)symbol == 0) {
            printf("Invalid input.\n");
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (symbols[j] == symbol) {
                printf("Symbols must be unique.\n");
                return 1;
            }
        }

        symbols[i] = symbol;
        frequencies[i] = freq;

        push(createNode(symbol, freq, NULL, NULL));
    }

    while (heapSize > 1) {
        Node *left = pop();
        Node *right = pop();

        if (left->freq > LLONG_MAX - right->freq) {
            printf("Frequency sum overflow.\n");
            return 1;
        }

        Node *parent = createNode(
            0, left->freq + right->freq, left, right
        );

        push(parent);
    }

    Node *root = pop();

    findLengths(root, 0);
    generateCanonical();

    int order[MAX];

    for (int i = 0; i < n; i++)
        order[i] = (unsigned char)symbols[i];

    qsort(order, n, sizeof(int), compareSymbols);

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    double totalFrequency = 0.0;
    double weightedLength = 0.0;

    for (int i = 0; i < n; i++) {
        int s = order[i];

        for (int j = 0; j < n; j++) {
            if ((unsigned char)symbols[j] == s) {
                printf("%c\t%lld\t\t%d\t%s\n",
                       symbols[j], frequencies[j],
                       lengths[s], codes[s]);

                totalFrequency += frequencies[j];
                weightedLength += frequencies[j] * lengths[s];
                break;
            }
        }
    }

    printf("\nExpected code length: %.4f bits/symbol\n",
           weightedLength / totalFrequency);

    return 0;
}
