// Question 3:
// [Maximum Weight Component with Size Constraints] Given a graph where each
// vertex v has weight wv, edges are added sequentially with weights. At any point,
// compute the maximum total vertex weight of any connected component whose size does 
// not exceed a threshold K. By choosing the proper input representation, write a program
// in C to validate your algorithm and derive the complexity analysis of your algorithm


#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int parent;
    int rank;
    int size;
    long long weight;
    int version;
} DSUNode;
typedef struct {
    long long weight;
    int size;
    int root;
    int version;
} HeapNode;
/* ---------------- DSU ---------------- */
DSUNode *createDSU(int V, int weights[]) {
    DSUNode *dsu = (DSUNode *)malloc(V * sizeof(DSUNode));
    for (int i = 0; i < V; i++) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
        dsu[i].size = 1;
        dsu[i].weight = weights[i];
        dsu[i].version = 0;
    }
    return dsu;
}
int find(DSUNode *dsu, int x) {
    if (dsu[x].parent == x) {
        return x;
    }
    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}
/* ---------------- Max-heap ---------------- */
void swapHeapNodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}
void maxHeapify(HeapNode heap[], int heapSize, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heapSize && heap[left].weight > heap[largest].weight) {
        largest = left;
    }
    if (right < heapSize && heap[right].weight > heap[largest].weight) {
        largest = right;
    }
    if (largest != index) {
        swapHeapNodes(&heap[index], &heap[largest]);
        maxHeapify(heap, heapSize, largest);
    }
}
void insertMaxHeap(HeapNode heap[], int *heapSize, HeapNode value) {
    heap[*heapSize] = value;
    int index = *heapSize;
    (*heapSize)++;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].weight >= heap[index].weight) {
            break;
        }
        swapHeapNodes(&heap[parent], &heap[index]);
        index = parent;
    }
}
HeapNode extractMax(HeapNode heap[], int *heapSize) {
    HeapNode maxValue = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;
    maxHeapify(heap, *heapSize, 0);
    return maxValue;
}
/* ---------------- Query with lazy deletion ---------------- */
/*  Returns maximum component weight with size <= K.
    Returns -1 if no such component exists. */
long long queryMaximumWeight(DSUNode *dsu,HeapNode heap[],int *heapSize,int K) {
    while (*heapSize > 0) {
        HeapNode top = heap[0];
        int currentRoot = find(dsu, top.root);
        /*  Entry is stale if:
            1. Its root is no longer the current root.
            2. Its recorded version is old.
            3. Its component size exceeds K. */
        if (currentRoot != top.root ||
            dsu[currentRoot].version != top.version ||
            dsu[currentRoot].size > K) {
            extractMax(heap, heapSize);
            continue;
        }
        return top.weight;
    }
    return -1;
}
/* ---------------- Add edge and answer query ---------------- */
void addEdgeAndQuery( DSUNode *dsu, HeapNode heap[], int *heapSize, int u, int v,int K){
    int rootU = find(dsu, u);
    int rootV = find(dsu, v);
    if (rootU == rootV) {
        printf("Edge (%d, %d): already connected, ", u, v);
    } else {
        /*  Union by rank.
            Attach smaller-rank root under larger-rank root. */
        if (dsu[rootU].rank < dsu[rootV].rank) {
            int temp = rootU;
            rootU = rootV;
            rootV = temp;
        }
        dsu[rootV].parent = rootU;
        dsu[rootU].size += dsu[rootV].size;
        dsu[rootU].weight += dsu[rootV].weight;
        dsu[rootU].version++;
        HeapNode newEntry;
        newEntry.weight = dsu[rootU].weight;
        newEntry.size = dsu[rootU].size;
        newEntry.root = rootU;
        newEntry.version = dsu[rootU].version;
        insertMaxHeap(heap, heapSize, newEntry);
        printf("Edge (%d, %d): components merged, ", u, v);
    }
    long long answer = queryMaximumWeight(dsu, heap, heapSize, K);
    if (answer == -1) {
        printf("no valid component with size <= %d\n", K);
    } else {
        printf("maximum valid component weight = %lld\n", answer);
    }
}

int main() {
    int V, E, K;
    printf("Enter vertices, edges, and size threshold K: ");
    scanf("%d %d %d", &V, &E, &K);
    int *weights = (int *)malloc(V * sizeof(int));
    printf("Enter %d vertex weights:\n", V);
    for (int i = 0; i < V; i++) scanf("%d", &weights[i]);
    DSUNode *dsu = createDSU(V, weights);
    /*  Initially, every single vertex is a component.
        Insert all valid initial components into the heap. */
    HeapNode *heap = (HeapNode *)malloc((V + E + 1) * sizeof(HeapNode));
    int heapSize = 0;
    for (int i = 0; i < V; i++) {
        HeapNode entry;
        entry.weight = dsu[i].weight;
        entry.size = dsu[i].size;
        entry.root = i;
        entry.version = dsu[i].version;
        insertMaxHeap(heap, &heapSize, entry);
    }
    printf("\nEnter %d edges one by one:\n", E);
    for (int i = 1; i <= E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= V || v < 0 || v >= V) {
            printf("Edge %d: invalid vertices\n", i);
            continue;
        }
        printf("After edge %d ", i);
        addEdgeAndQuery(dsu, heap, &heapSize, u, v, K);
    }
    free(weights);
    free(dsu);
    free(heap);
    return 0;
}
// Complexity Analysis:
// 1. DSU operations (find and union) take O(α(V)) time, where α is the inverse Ackermann function.
// 2. Heap operations take O(log(V)) time.
// 3. Each edge addition and query takes O(log(V)) time in the worst case.
// 4. Overall, for E edges, the total time complexity is O(E log(V)).
// 5. Space complexity is O(V + E) for storing the graph and the heap.
