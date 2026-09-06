#include <stdio.h>
#include <stdlib.h>

/*
0/1 Knapsack Problem using Dynamic Programming

1. Recurrence Relation:
   Let dp[i][w] represent the maximum profit considering the first i items with a knapsack capacity w.
   
   Base Cases:
     dp[0][w] = 0  for all 0 <= w <= W (0 items available)
     dp[i][0] = 0  for all 0 <= i <= n (capacity is 0)

   Recursive Step (for item i with weight wt[i-1] and profit val[i-1]):
     - If wt[i-1] <= w:
         dp[i][w] = max(val[i-1] + dp[i-1][w - wt[i-1]], dp[i-1][w])
     - If wt[i-1] > w:
         dp[i][w] = dp[i-1][w]

2. Complexity Analysis:
   - Time Complexity: O(n * W)
     Filling an (n + 1) x (W + 1) DP table requires constant time O(1) computation per cell.
     Total runtime is Theta(n * W), which is pseudo-polynomial.
   - Space Complexity: O(n * W)
     Requires a 2D table of size (n + 1) x (W + 1) to store intermediate states.
     (Can be optimized to O(W) using a 1D array traversed in reverse).
*/

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack_01(int W, const int wt[], const int val[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][W];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n, W;

    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int *wt = (int *)malloc(n * sizeof(int));
    int *val = (int *)malloc(n * sizeof(int));

    printf("Enter weights of %d items:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter profits of %d items:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter capacity of knapsack (W): ");
    if (scanf("%d", &W) != 1 || W < 0) {
        free(wt);
        free(val);
        return 1;
    }

    int max_profit = knapsack_01(W, wt, val, n);
    printf("\nMaximum Profit = %d\n", max_profit);

    free(wt);
    free(val);
    return 0;
}