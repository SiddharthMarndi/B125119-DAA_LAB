//  [Online Graph-Bipartiteness Testing] A graph is bipartite if and only if it contains
// no odd-length cycles. Given an undirected graph with V vertices, edges arrive online
// one by one. Maintain whether the graph remains bipartite. If adding an edge (u,v) does 
// not introduce an odd cycle, add it; otherwise, report that it violates bipartiteness 
// and skip it. By choosing the proper input representation, write a program in C to 
// validate your algorithm and derive the complexity analysis of your algorithm

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int *parent;
    int *rank;
    int *parity;
    int vertices;
} DSU;
DSU *createDSU(int vertices) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->vertices = vertices;
    dsu->parent = (int *)malloc(vertices * sizeof(int));
    dsu->rank = (int *)malloc(vertices * sizeof(int));
    dsu->parity = (int *)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
        dsu->parity[i] = 0;
    }
    return dsu;
}
/*  Returns the root of x.
    Also updates parity[x] to be the parity of the path from x to its root. */
int find(DSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    int root = find(dsu, dsu->parent[x]);
    /*  Path compression: parity[x] becomes parity from x directly to root.
        Old relation: parity[x] = parity from x to old parent
                      parity[old parent] = parity from old parent to root
        New relation: parity[x] = parity[x] XOR parity[old parent] */
    dsu->parity[x] ^= dsu->parity[dsu->parent[x]];
    dsu->parent[x] = root;
    return root;
}
/* Adds edge (u, v).
    Returns: 1 if edge is accepted, 0 if edge would create an odd cycle and is skipped. */
int addEdge(DSU *dsu, int u, int v) {
    int rootU = find(dsu, u);
    int rootV = find(dsu, v);
    /* If u and v are already connected, the edge creates a cycle.
        The cycle is odd iff: parity[u] == parity[v] */
    if (rootU == rootV) {
        if (dsu->parity[u] == dsu->parity[v]) return 0;
        return 1;
    }
    /*  We need: parity[u] XOR parity[v] XOR edgeParity = 1
        Since an edge connects opposite colors,
        edgeParity = 1. */
    int requiredParity = dsu->parity[u] ^ dsu->parity[v] ^ 1;
    /* Attach smaller-rank tree under larger-rank tree. */
    if (dsu->rank[rootU] < dsu->rank[rootV]) {
        dsu->parent[rootU] = rootV;
        dsu->parity[rootU] = requiredParity;
    } else if (dsu->rank[rootU] > dsu->rank[rootV]) {
        dsu->parent[rootV] = rootU;
        dsu->parity[rootV] = requiredParity;
    } else {
        dsu->parent[rootV] = rootU;
        dsu->parity[rootV] = requiredParity;
        dsu->rank[rootU]++;
    }
    return 1;
}

int main() {
    int V, E;
    printf("Enter number of vertices and number of incoming edges: ");
    scanf("%d %d", &V, &E);
    DSU *dsu = createDSU(V);
    printf("Enter %d edges one by one:\n", E);
    int acceptedEdges = 0;
    for (int i = 1; i <= E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= V || v < 0 || v >= V) {
            printf("Edge %d (%d, %d): invalid vertex\n", i, u, v);
            continue;
        }
        if (addEdge(dsu, u, v)) {
            acceptedEdges++;
            printf("Edge %d (%d, %d): accepted, graph remains bipartite\n",i, u, v);
        } else printf("Edge %d (%d, %d): rejected, creates an odd cycle\n",i, u, v);
    }
    printf("\nTotal accepted edges: %d\n", acceptedEdges);
    printf("Final graph is bipartite: YES\n");
    free(dsu->parent);
    free(dsu->rank);
    free(dsu->parity);
    free(dsu);
    return 0;
}
// Complexity Analysis:
// 1. DSU operations (find and union) take O(α(V)) time, where α is the inverse Ackermann function.
// 2. Each edge addition takes O(α(V)) time in the worst case.
// 3. Overall, for E edges, the total time complexity is O(E * α(V)).
// 4. Space complexity is O(V) for storing the DSU data structure.