// Question 2:
// [Dynamic Connected Components in a Grid] Given an R×C grid initially completely
// filled with water, land cells are added one by one at positions (r1,c1),...,(rk,ck).
// After each operation, output the current number of 4-directionally connected land com
// ponents (islands). By choosing the proper input representation, write a program in C to
// validate your algorithm and derive the complexity analysis of your algorithm


#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int *parent;
    int *rank;
    int totalCells;
} DSU;
DSU *createDSU(int totalCells) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    dsu->totalCells = totalCells;
    dsu->parent = (int *)malloc(totalCells * sizeof(int));
    dsu->rank = (int *)malloc(totalCells * sizeof(int));
    for (int i = 0; i < totalCells; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}
int find(DSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    dsu->parent[x] = find(dsu, dsu->parent[x]);
    return dsu->parent[x];
}
/*  Returns 1 if two different components were merged.
    Returns 0 if they were already in the same component. */
int unionCells(DSU *dsu, int a, int b) {
    int rootA = find(dsu, a);
    int rootB = find(dsu, b);
    if (rootA == rootB) return 0;
    if (dsu->rank[rootA] < dsu->rank[rootB]) {
        dsu->parent[rootA] = rootB;
    } else if (dsu->rank[rootA] > dsu->rank[rootB]) {
        dsu->parent[rootB] = rootA;
    } else {
        dsu->parent[rootB] = rootA;
        dsu->rank[rootA]++;
    }
    return 1;
}

int main() {
    int R, C, k;
    printf("Enter rows, columns, and number of land additions: ");
    scanf("%d %d %d", &R, &C, &k);
    int totalCells = R * C;
    DSU *dsu = createDSU(totalCells);
    int *isLand = (int *)calloc(totalCells, sizeof(int));
    int islandCount = 0;
    printf("\nEnter %d land positions (row column):\n", k);
    for (int query = 1; query <= k; query++) {
        int r, c;
        scanf("%d %d", &r, &c);
        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Operation %d: invalid position (%d, %d), islands = %d\n",query, r, c, islandCount);
            continue;
        }
        int current = r * C + c;
        /* If the cell is already land, do not count it again. */
        if (isLand[current] == 1) {
            printf("Operation %d: (%d, %d) already land, islands = %d\n",query, r, c, islandCount);
            continue;
        }
        isLand[current] = 1;
        islandCount++;
        /* Four directions: up, down, left, right. */
        int rowDirection[] = {-1, 1, 0, 0};
        int colDirection[] = {0, 0, -1, 1};
        for (int direction = 0; direction < 4; direction++) {
            int newRow = r + rowDirection[direction];
            int newCol = c + colDirection[direction];
            if (newRow < 0 || newRow >= R || newCol < 0 || newCol >= C) continue;
            int neighbor = newRow * C + newCol;
            if (isLand[neighbor] == 1) {
                int merged = unionCells(dsu, current, neighbor);
                if (merged == 1) islandCount--;
            }
        }
        printf("Operation %d: land added at (%d, %d), islands = %d\n",query, r, c, islandCount);
    }
    free(isLand);
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
    return 0;
}
// Complexity analysis:
//  Let R = number of rows, C = number of columns, k = number of land additions.
//  Time complexity:
//  O(k) for processing k land additions.
//  Each union and find operation takes O(α(R*C)) time, where α is the inverse Ackermann function.
//  Overall time complexity: O(k * α(R*C)).
//  Space complexity:
//  O(R*C) for DSU data structure and isLand array.