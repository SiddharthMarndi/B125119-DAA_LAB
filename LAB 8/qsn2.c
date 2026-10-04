/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Coin Change (Total Number of Ways)
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Create a DP array 'dp' of size (V + 1) and initialize all entries to 0.
 * 2. Set dp[0] = 1 as the base case (there is 1 way to make amount 0 by choosing no coins).
 * 3. Iterate through each coin denomination in the coin array.
 * 4. For each coin, iterate 'j' from the coin's value up to V, updating dp[j] += dp[j - coin].
 * 5. Finally, return dp[V] which stores the total number of distinct combinations to make amount V.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(n * V), where n is the number of coin denominations and V is the target amount.
 * - Space Complexity: O(V), because a 1D DP array of size (V + 1) is used to store subproblem solutions.
 */

#include <stdio.h>

long long countWays(int coins[], int n, int V) {
    long long dp[V + 1];
    
    for (int i = 0; i <= V; i++) {
        dp[i] = 0;
    }
    
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= V; j++) {
            dp[j] += dp[j - coins[i]];
        }
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

    long long result = countWays(coins, n, V);

    printf("Total number of distinct combinations: %lld\n", result);

    return 0;
}