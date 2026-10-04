/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Maximum Sum Increasing Subsequence
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given an array A of n positive integers, create a DP array 'dp' of size n, 
 *    initialized with the values of array A itself (since each element forms an 
 *    increasing subsequence of sum A[i] by itself).
 * 2. Iterate 'i' from 1 to n-1. For each 'i', iterate 'j' from 0 to i-1.
 * 3. If A[i] > A[j] and dp[j] + A[i] > dp[i], update dp[i] = dp[j] + A[i].
 * 4. Find and return the maximum value in the 'dp' array, which represents the 
 *    maximum possible sum of a strictly increasing subsequence.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(n^2), where n is the number of elements in the array, due 
 *   to the nested loops checking all previous elements for each index.
 * - Space Complexity: O(n), because a 1D DP array of size n is used to store 
 *   subproblem results.
 */

#include <stdio.h>

int maxSumIncreasingSubsequence(int arr[], int n) {
    if (n == 0) return 0;
    
    int dp[n];
    int maxSum = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }

    maxSum = dp[0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[j] + arr[i] > dp[i]) {
                dp[i] = dp[j] + arr[i];
            }
        }
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }
    }

    return maxSum;
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

    int result = maxSumIncreasingSubsequence(arr, n);

    printf("Maximum Sum of Increasing Subsequence: %d\n", result);

    return 0;
}