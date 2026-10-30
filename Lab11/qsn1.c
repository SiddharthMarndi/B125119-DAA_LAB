#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXV 1005
#define MAXE 200005
#define INF (LLONG_MAX / 4)
typedef long long ll;
typedef struct {
    int to, weight, next;
} Edge;
typedef struct {
    int vertex, parity;
    ll distance;
} State;
Edge edges[MAXE];
int head[MAXV];
int edgeCount = 0;
ll dist[MAXV][2];
State *deque;
int front = 0, back = 0, count = 0, capacity;
void pushFront(State s) {
    front = (front - 1 + capacity) % capacity;
    deque[front] = s;
    count++;
}
void pushBack(State s) {
    deque[back] = s;
    back = (back + 1) % capacity;
    count++;
}
State popFront(void) {
    State s = deque[front];
    front = (front + 1) % capacity;
    count--;
    return s;
}
void addEdge(int u, int v, int w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}
void zeroOneBFS(int n, int source) {
    for (int i = 1; i <= n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    front = back = count = 0;
    dist[source][0] = 0;
    State start = {source, 0, 0};
    pushFront(start);
    while (count > 0) {
        State cur = popFront();
        int u = cur.vertex;
        int parity = cur.parity;
        // Ignore outdated deque entries.
        if (cur.distance != dist[u][parity])
            continue;
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            int newParity = parity ^ w;
            ll newDist = dist[u][parity] + w;
            if (newDist < dist[v][newParity]) {
                dist[v][newParity] = newDist;
                State next = {v, newParity, newDist};
                if (w == 0)
                    pushFront(next);
                else
                    pushBack(next);
            }
        }
    }
}
int main(void) {
    int n, m, source;
    ll C;
    printf("Enter vertices, edges, source and penalty C:\n");
    scanf("%d %d %d %lld", &n, &m, &source, &C);
    for (int i = 1; i <= n; i++)
        head[i] = -1;
    printf("Enter edges (u v w), where w is 0 or 1:\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    // Enough space for the O(E) successful relaxations.
    capacity = 2 * m + 2 * n + 10;
    deque = malloc((size_t)capacity * sizeof(State));
    zeroOneBFS(n, source);
    printf("\nMinimum effective costs:\n");
    for (int v = 1; v <= n; v++) {
        if (dist[v][0] == INF && dist[v][1] == INF) {
            printf("Vertex %d: Unreachable\n", v);
        } else {
            ll evenCost = dist[v][0];
            ll oddCost = (dist[v][1] == INF) ? INF : dist[v][1] + C;
            ll answer = evenCost < oddCost ? evenCost : oddCost;
            printf("Vertex %d: %lld\n", v, answer);
        }
    }
    free(deque);
    return 0;
}

//Complexity Analysis
//Time complexity O(V+E)
//Space complexity O(V+E)