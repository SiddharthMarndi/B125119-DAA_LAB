
#include <stdio.h>
#include <stdlib.h>

#define MAXV 1005
#define MAXE 200005

typedef struct {
    int to, next;
} Edge;

Edge edges[2 * MAXE];
int head[MAXV];
int edgeCount = 0;

int owner[MAXV];
int dist[MAXV];
int queue[MAXV];

void addEdge(int u, int v) {

    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;

    edges[edgeCount].to = u;
    edges[edgeCount].next = head[v];
    head[v] = edgeCount++;
}

void multiSourceBFS(int n, int K, int hubs[], int R) {

    int front = 0, rear = 0;

    for (int i = 1; i <= n; i++) {
        owner[i] = -1;
        dist[i] = -1;
    }

    // Insert all hubs in increasing index order
    for (int i = 1; i <= K; i++) {

        int h = hubs[i];

        owner[h] = i;
        dist[h] = 0;

        queue[rear++] = h;
    }

    // Multi-source BFS
    while (front < rear) {

        int u = queue[front++];

        for (int e = head[u]; e != -1;
             e = edges[e].next) {

            int v = edges[e].to;

            // First arrival determines ownership
            // Hubs are inserted in increasing index order
            if (dist[v] == -1) {

                dist[v] = dist[u] + 1;
                owner[v] = owner[u];

                queue[rear++] = v;
            }
        }
    }

    // Apply radius constraint
    for (int i = 1; i <= n; i++) {

        if (dist[i] == -1 || dist[i] > R) {
            owner[i] = -1;
            dist[i] = -1;
        }
    }
}

int main(void) {

    int n, m, K, R;

    printf("Enter number of vertices and edges:\n");
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        head[i] = -1;

    printf("Enter undirected edges:\n");

    for (int i = 0; i < m; i++) {

        int u, v;
        scanf("%d %d", &u, &v);

        addEdge(u, v);
    }

    printf("Enter number of hubs:\n");
    scanf("%d", &K);

    int hubs[MAXV];

    printf("Enter hubs in increasing index order:\n");

    for (int i = 1; i <= K; i++)
        scanf("%d", &hubs[i]);

    printf("Enter radius R:\n");
    scanf("%d", &R);

    multiSourceBFS(n, K, hubs, R);

    printf("\nVertex\tOwner\tDistance\n");

    for (int i = 1; i <= n; i++) {

        printf("%d\t%d\t%d\n",
               i, owner[i], dist[i]);
    }

    return 0;
}

// Complexity Analysis:
//
// 1. Building adjacency list takes O(V + E) time.
// 2. Initializing arrays takes O(V) time.
// 3. Inserting K hubs takes O(K) time.
// 4. Multi-source BFS visits every vertex and edge
//    at most once, taking O(V + E) time.
// 5. Applying radius constraint takes O(V) time.
//
// Overall Time Complexity: O(V + E)
//
// Space Complexity: O(V + E)
//
// Adjacency List: O(V + E)
// Queue: O(V)
// Owner and Distance Arrays: O(V)
