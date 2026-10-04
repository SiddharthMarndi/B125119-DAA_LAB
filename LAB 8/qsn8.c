/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Optimal Binary Search Trees (OBST)
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given n distinct keys with search probabilities p[1..n] and n+1 dummy key 
 *    probabilities q[0..n], create three tables: 'e' for expected costs, 'w' for 
 *    probabilities sum, and 'root' for root choices, all of size (n+2) x (n+1).
 * 2. Initialize base cases for empty subtrees where i = j + 1:
 *    - e[i][i-1] = q[i-1] and w[i][i-1] = q[i-1] for i = 1 to n + 1.
 * 3. Iterate through chain lengths 'l' from 1 to n. For each length, iterate through 
 *    starting index 'i' from 1 to n - l + 1, and set j = i + l - 1.
 * 4. Compute w[i][j] = w[i][j-1] + p[j] + q[j].
 * 5. For each possible root 'r' from i to j, compute the cost of forming a tree with 
 *    r as root, and find the minimum expected cost to update e[i][j] and root[i][j].
 * 6. The minimum expected search cost for the entire set is stored in e[1][n].
 * 
 * Complexity Analysis:
 * - Time Complexity: O(n^3), because there are three nested loops over the number 
 *   of keys 'n' to compute the optimal subtree costs for all chains and root choices.
 * - Space Complexity: O(n^2) to store the 2D DP tables (e, w, and root).
 */

#include <stdio.h>

void optimalBST(float p[], float q[], int n) {
    float e[n + 2][n + 1];
    float w[n + 2][n + 1];
    int root[n + 1][n + 1];

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = 99999.0; // Initialize with a large value
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            
            for (int r = i; r <= j; r++) {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Minimum Expected Search Cost: %.4f\n", e[1][n]);
}

int main() {
    int n;
    
    printf("Enter the number of keys (n): ");
    scanf("%d", &n);
    
    float p[n + 1];
    float q[n + 1];
    
    printf("Enter search probabilities for %d keys (p[1] to p[%d]):\n", n, n);
    for (int i = 1; i <= n; i++) {
        scanf("%f", &p[i]);
    }
    
    printf("Enter dummy key search probabilities for %d keys (q[0] to q[%d]):\n", n, n);
    for (int i = 0; i <= n; i++) {
        scanf("%f", &q[i]);
    }

    optimalBST(p, q, n);

    return 0;
}