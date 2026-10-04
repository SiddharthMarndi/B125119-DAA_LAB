/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Longest Common Subsequence (LCS)
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given two sequences X of length m and Y of length n, create a 2D DP table 'dp' of size (m + 1) x (n + 1).
 * 2. Initialize the first row and first column of the DP table to 0 (base cases for empty sub-sequences).
 * 3. Iterate 'i' from 1 to m and 'j' from 1 to n:
 *    - If X[i-1] == Y[j-1], set dp[i][j] = dp[i-1][j-1] + 1.
 *    - Else, set dp[i][j] = maximum of dp[i-1][j] and dp[i][j-1].
 * 4. The length of the longest common subsequence is stored in dp[m][n].
 * 5. Reconstruct the actual subsequence string by backtracking from dp[m][n]: if characters match, add to the string and move diagonally up-left; otherwise, move toward the maximum adjacent cell.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(m * n), where m and n are the lengths of the two sequences, because we fill an (m + 1) x (n + 1) table.
 * - Space Complexity: O(m * n) to store the 2D DP table values.
 */

#include <stdio.h>
#include <string.h>

void printLCS(char X[], char Y[], int m, int n) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int index = dp[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Length of LCS: %d\n", dp[m][n]);
    printf("Longest Common Subsequence: %s\n", lcs);
}

int main() {
    char X[100], Y[100];

    printf("Enter the first string: ");
    scanf("%s", X);

    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    printLCS(X, Y, m, n);

    return 0;
}