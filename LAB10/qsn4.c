// Question 4:
//  [Reverse Time-Step DSU Application] Given a vertex-weighted undirected graph,
// vertices are sequentially deleted one by one in an order P = [p1,p2,...,pV ]. After 
// each vertex deletion, compute the maximum sum of vertex values among all remaining 
// connected components. Note that deleting a vertex in a graph means removing that 
// specific vertex and all edges connected (incident) to it from the graph structure. By 
// choosing the proper input representation, write a program in C to validate your 
// algorithm and derive the complexity analysis of your algorithm.


#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int parent;
    int size;
    long long componentValue;
    int active;
} DSU;
/* ---------------- DSU functions ---------------- */
int find(DSU *dsu, int x) {
    if (dsu[x].parent == x) {
        return x;
    }
    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}
/*  Merges components of a and b.
    Returns the value of the newly merged component. */
long long unionComponents(DSU *dsu, int a, int b) {
    int rootA = find(dsu, a);
    int rootB = find(dsu, b);
    if (rootA == rootB) {
        return dsu[rootA].componentValue;
    }
    /*  Union by size:
        attach smaller component under larger component. */
    if (dsu[rootA].size < dsu[rootB].size) {
        int temp = rootA;
        rootA = rootB;
        rootB = temp;
    }
    dsu[rootB].parent = rootA;
    dsu[rootA].size += dsu[rootB].size;
    dsu[rootA].componentValue += dsu[rootB].componentValue;
    return dsu[rootA].componentValue;
}
/* ---------------- Main algorithm ---------------- */
int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    int *value = (int *)malloc(V * sizeof(int));
    int *active = (int *)calloc(V, sizeof(int));
    int *answer = (int *)malloc((V + 1) * sizeof(int));
    DSU *dsu = (DSU *)malloc(V * sizeof(DSU));
    printf("Enter %d vertex values:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%d", &value[i]);
        dsu[i].parent = i;
        dsu[i].size = 1;
        dsu[i].componentValue = value[i];
        dsu[i].active = 0;
    }
    /* Store graph using adjacency lists. */
    int *edgeU = (int *)malloc(E * sizeof(int));
    int *edgeV = (int *)malloc(E * sizeof(int));
    int *degree = (int *)calloc(V, sizeof(int));
    printf("Enter %d undirected edges:\n", E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &edgeU[i], &edgeV[i]);
        degree[edgeU[i]]++;
        degree[edgeV[i]]++;
    }
    /* Build adjacency lists using CSR-style arrays. */
    int *adjStart = (int *)malloc((V + 1) * sizeof(int));
    int *adjList = (int *)malloc(2 * E * sizeof(int));
    adjStart[0] = 0;
    for (int i = 0; i < V; i++) {
        adjStart[i + 1] = adjStart[i] + degree[i];
    }
    int *fill = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        fill[i] = adjStart[i];
    }
    for (int i = 0; i < E; i++) {
        int u = edgeU[i];
        int v = edgeV[i];
        adjList[fill[u]++] = v;
        adjList[fill[v]++] = u;
    }
    int *deletionOrder = (int *)malloc(V * sizeof(int));
    printf("Enter deletion order of %d vertices:\n", V);
    for (int i = 0; i < V; i++) {
        scanf("%d", &deletionOrder[i]);
    }
    /*  answer[i] = maximum component value after deleting p1, p2, ..., p_i
        After all V deletions, no vertices remain.*/
    answer[V] = 0;
    long long currentMax = 0;
    /*  Reverse-time simulation:
        add vertices from pV back to p1. */
    for (int time = V - 1; time >= 0; time--) {
        int vertex = deletionOrder[time];
        active[vertex] = 1;
        long long currentComponentValue = value[vertex];
        for (int j = adjStart[vertex]; j < adjStart[vertex + 1]; j++) {
            int neighbor = adjList[j];
            if (active[neighbor] == 1) {
                currentComponentValue = unionComponents(dsu, vertex, neighbor);
            }
        }
        if (currentComponentValue > currentMax)  currentMax = currentComponentValue;
        /*  After adding deletionOrder[time],
            the graph equals the state after deleting
            deletionOrder[0..time-1]. */
        answer[time] = currentMax;
    }
    printf("\nMaximum component value after each deletion:\n");
    for (int i = 1; i <= V; i++) {
        printf("After deleting vertex %d: %lld\n",deletionOrder[i - 1], answer[i]);
    }
    free(value);
    free(active);
    free(answer);
    free(edgeU);
    free(edgeV);
    free(degree);
    free(adjStart);
    free(adjList);
    free(fill);
    free(deletionOrder);
    free(dsu);
    return 0;
}
// Complexity analysis:
//  Let V = number of vertices, E = number of edges.
//  Time complexity:
//      O(V + E) for building adjacency lists.
//      O(V + E) for reverse-time simulation of vertex additions.
// Overall time complexity: O(V + E).
// Space complexity:
//  O(V + E) for adjacency lists.
//  O(V) for DSU data structure and other arrays.
// Overall space complexity: O(V + E).