/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Rod Cutting with Reconstruction
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given a rod of length n and an array of prices P (where P[i] is the price for length i+1), 
 *    create a DP array 'r' of size (n + 1) initialized to 0, and a 's' (solution) array of size (n + 1).
 * 2. Iterate 'i' from 1 to n:
 *    - Initialize max_val = -1.
 *    - For 'j' from 1 to i, find the maximum revenue using the recurrence:
 *      r[i] = max(r[i], price[j-1] + r[i-j]), and record the optimal first cut size in s[i].
 * 3. The maximum revenue for length n is stored in r[n].
 * 4. Reconstruct the exact piece lengths by following the choices stored in the 's' array 
 *    (subtracting the cut length from the remaining rod length until the rod length becomes 0).
 * 
 * Complexity Analysis:
 * - Time Complexity: O(n^2), where n is the length of the rod, due to the nested loops 
 *   computing the optimal revenue for each sub-length.
 * - Space Complexity: O(n), because we use 1D arrays of size (n + 1) for DP values and 
 *   reconstruction tracking.
 */

#include <stdio.h>

void cutRod(int prices[], int n) {
    int r[n + 1];
    int s[n + 1];
    
    r[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        for (int j = 1; j <= i; j++) {
            if (max_val < prices[j - 1] + r[i - j]) {
                max_val = prices[j - 1] + r[i - j];
                s[i] = j; // Store the optimal first cut length
            }
        }
        r[i] = max_val;
    }

    printf("Maximum Revenue Obtainable: %d\n", r[n]);
    printf("Optimal Piece Lengths (Reconstruction): ");
    
    int n_temp = n;
    while (n_temp > 0) {
        printf("%d ", s[n_temp]);
        n_temp -= s[n_temp];
    }
    printf("\n");
}

int main() {
    int n;
    
    printf("Enter the length of the rod (n): ");
    scanf("%d", &n);
    
    int prices[n];
    printf("Enter the prices for lengths 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    cutRod(prices, n);

    return 0;
}