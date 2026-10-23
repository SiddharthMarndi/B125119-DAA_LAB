// Question 5:
//  [Lexicographically Smallest Connected Component Permutation] Given a permu
// tation A of numbers 1...n, and a list of allowable pairwise swaps (u,v) forming edges
// in an undirected graph, find the lexicographically smallest permutation achievable 
// through any number of valid swaps. By choosing the proper input representation, write 
// a program in C  to validate your algorithm and derive the complexity analysis of your 
// algorithm

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int parent;
    int rank;
} DSU;
/* ---------------- DSU functions ---------------- */
int find(DSU *dsu, int x) {
    if (dsu[x].parent == x) return x;
    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}
void unionSets(DSU *dsu, int a, int b) {
    int rootA = find(dsu, a);
    int rootB = find(dsu, b);
    if (rootA == rootB) return;
    if (dsu[rootA].rank < dsu[rootB].rank) {
        dsu[rootA].parent = rootB;
    } else if (dsu[rootA].rank > dsu[rootB].rank) {
        dsu[rootB].parent = rootA;
    } else {
        dsu[rootB].parent = rootA;
        dsu[rootA].rank++;
    }
}
/* ---------------- Comparison functions ---------------- */
int compareInts(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}
int compareRoots(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return x - y;
}
/* ---------------- Main algorithm ---------------- */
int main() {
    int n, m;
    printf("Enter permutation size and number of swap edges: ");
    scanf("%d %d", &n, &m);
    int *A = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    DSU *dsu = (DSU *)malloc(n * sizeof(DSU));
    printf("Enter the permutation of 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }
    printf("Enter %d allowable swap edges:\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSets(dsu, u, v);
    }
    /* Group indices by their DSU root. */
    int **componentIndices = (int **)malloc(n * sizeof(int *));
    int *componentSize = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) componentIndices[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int root = find(dsu, i);
        componentIndices[root][componentSize[root]] = i;
        componentSize[root]++;
    }
    /* Process every connected component. */
    for (int root = 0; root < n; root++) {
        if (componentSize[root] == 0) continue;
        int size = componentSize[root];
        int *indices = componentIndices[root];
        int *values = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            values[i] = A[indices[i]];
        }
        /* Sort indices and values independently. */
        qsort(indices, size, sizeof(int), compareInts);
        qsort(values, size, sizeof(int), compareInts);
        /* Smallest value goes to smallest index. */
        for (int i = 0; i < size; i++) result[indices[i]] = values[i];
        free(values);
    }
    printf("\nOriginal permutation: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\nLexicographically smallest permutation: ");
    for (int i = 0; i < n; i++) printf("%d ", result[i]);
    printf("\n");
    for (int i = 0; i < n; i++) free(componentIndices[i]);
    free(componentIndices);
    free(componentSize); free(A);
    free(result);
    free(dsu);
    return 0;
}
// Complexity Analysis :
// Time complexity : Process m edges O(m α(n)) and sort component O(nlogn)
// Overall : O(nlogn + m α(n))
// Space complexity : O(n)