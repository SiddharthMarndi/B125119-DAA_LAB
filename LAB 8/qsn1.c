/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Minimum Coin Change

 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Create a DP array 'dp' of size (V + 1) and initialize all entries to (V + 1) 
 *    to represent an initial state of infinity.
 * 2. Set dp[0] = 0 as the base case (zero coins are needed to make amount 0).
 * 3. Iterate 'i' from 1 to V. For each 'i', iterate through all coin denominations 'j'.
 * 4. If the coin value is less than or equal to 'i', update dp[i] to the minimum 
 *    between its current value and (dp[i - coin_value] + 1).
 * 5. After filling the table, if dp[V] exceeds V, return -1 (amount cannot be formed); 
 *    otherwise, return dp[V].
 * 
 * Complexity Analysis:
 * - Time Complexity: O(V * n), where V is the target amount and n is the number 
 *   of coin denominations. The outer loop executes V times and the inner loop 
 *   executes n times.
 * - Space Complexity: O(V), because a 1D DP array of size V + 1 is allocated 
 *   to store the optimal subproblem solutions.
*/

#include <stdio.h>
#include <limits.h>

int minCoins(int coins[], int n, int V) {
    int dp[V + 1];
    
    for (int i = 0; i <= V; i++) {
        dp[i] = V + 1; 
    }
    
    dp[0] = 0;

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= coins[j]) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    if (dp[V] > V) {
        return -1;
    }
    
    return dp[V];
}

int main() {
    int n, V;
    
    printf("Enter the number of coin denominations: ");
    scanf("%d", &n);
    
    int coins[n];
    printf("Enter the coin denominations:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }
    
    printf("Enter the target amount V: ");
    scanf("%d", &V);

    int result = minCoins(coins, n, V);

    if (result != -1) {
        printf("Minimum number of coins required: %d\n", result);
    } else {
        printf("The amount cannot be made up by any combination of the given coins (-1).\n");
    }

    return 0;
}