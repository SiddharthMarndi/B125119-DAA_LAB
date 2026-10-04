/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Longest Increasing Subsequence (LIS)
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given an integer array A of size n, create a DP array 'dp' of size n, initialized to 1 
 *    (since every individual element is an increasing subsequence of length 1 by itself).
 * 2. Iterate 'i' from 1 to n-1. For each 'i', iterate 'j' from 0 to i-1.
 * 3. If A[i] > A[j] and dp[j] + 1 > dp[i], update dp[i] = dp[j] + 1.
 * 4. Find and return the maximum value in the 'dp' array, which represents the length of the longest increasing subsequence.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(n^2), where n is the number of elements in the array, due to the nested loops checking all previous elements for each index.
 * - Space Complexity: O(n), because a 1D DP array of size n is used to store subproblem results.
 */

#include <stdio.h>

int longestIncreasingSubsequence(int arr[], int n) {
    if (n == 0) return 0;
    
    int dp[n];
    int maxLen = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }

    return maxLen;
}

int main() {
    int n;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result = longestIncreasingSubsequence(arr, n);

    printf("Length of Longest Increasing Subsequence: %d\n", result);

    return 0;
}