#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Longest Common Subsequence (LCS) using Dynamic Programming

1. Recurrence Relation:
   Let dp[i][j] denote the length of the LCS of prefixes X[0...i-1] and Y[0...j-1].
   
   Base Cases:
     dp[i][0] = 0 for all 0 <= i <= m
     dp[0][j] = 0 for all 0 <= j <= n

   State Transitions:
     - If X[i-1] == Y[j-1]:
         dp[i][j] = 1 + dp[i-1][j-1]
     - If X[i-1] != Y[j-1]:
         dp[i][j] = max(dp[i-1][j], dp[i][j-1])

2. Backtracking for the Subsequence:
   - Start from dp[m][n].
   - If X[i-1] == Y[j-1], character is part of LCS -> move diagonally to dp[i-1][j-1].
   - Else, move in the direction of the larger neighbor:
       If dp[i-1][j] >= dp[i][j-1], move up to dp[i-1][j].
       Else, move left to dp[i][j-1].

3. Complexity Analysis:
   - Time Complexity:
       * Table construction: O(m * n) since each of the (m + 1) * (n + 1) cells takes O(1) operations.
       * Backtracking: O(m + n) steps in the worst case to reconstruct the string.
       * Overall Time Complexity: O(m * n).
   - Space Complexity:
       * 2D table of size (m + 1) * (n + 1): O(m * n).
       * String storage for the result: O(min(m, n)).
       * Overall Space Complexity: O(m * n).
*/

int max(int a, int b) {
    return (a > b) ? a : b;
}

void find_lcs(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcs_len = dp[m][n];
    char *lcs = (char *)malloc((lcs_len + 1) * sizeof(char));
    lcs[lcs_len] = '\0';

    int i = m;
    int j = n;
    int idx = lcs_len - 1;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[idx] = X[i - 1];
            i--;
            j--;
            idx--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("Length of Longest Common Subsequence: %d\n", lcs_len);
    printf("Longest Common Subsequence: %s\n", lcs);

    free(lcs);
    for (int k = 0; k <= m; k++) {
        free(dp[k]);
    }
    free(dp);
}

int main() {
    char X[1000];
    char Y[1000];

    printf("Enter first string: ");
    if (scanf("%999s", X) != 1) {
        return 1;
    }

    printf("Enter second string: ");
    if (scanf("%999s", Y) != 1) {
        return 1;
    }

    find_lcs(X, Y);

    return 0;
}