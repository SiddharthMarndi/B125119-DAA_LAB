/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Edit Distance with Traceback Information
 * 
 * Algorithm Steps (Dynamic Programming - Bottom-Up):
 * 1. Given string A of length m and string B of length n, create a 2D DP table 'dp' of size (m + 1) x (n + 1).
 * 2. Initialize the base cases: dp[i][0] = i (i deletions) and dp[0][j] = j (j insertions).
 * 3. Iterate 'i' from 1 to m and 'j' from 1 to n:
 *    - If A[i-1] == B[j-1], dp[i][j] = dp[i-1][j-1] (no operation needed).
 *    - Else, dp[i][j] = 1 + min(dp[i-1][j] (deletion), dp[i][j-1] (insertion), dp[i-1][j-1] (substitution)).
 * 4. The minimum operations required is stored in dp[m][n].
 * 5. Backtrack from dp[m][n] to print the sequence of operations (insert, delete, substitute, or match) required to transform A into B.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(m * n), where m and n are the lengths of strings A and B, because we fill an (m + 1) x (n + 1) table.
 * - Space Complexity: O(m * n) to store the 2D DP table values.
 */

#include <stdio.h>
#include <string.h>

int min(int x, int y, int z) {
    int m = x;
    if (y < m) m = y;
    if (z < m) m = z;
    return m;
}

void editDistanceTraceback(char A[], char B[], int m, int n) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
        }
    }

    printf("Minimum Edit Distance: %d\n", dp[m][n]);
    printf("Traceback Operations:\n");

    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1]) {
            printf("Match: '%c'\n", A[i - 1]);
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            printf("Substitute '%c' in A with '%c' in B\n", A[i - 1], B[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            printf("Delete '%c' from A\n", A[i - 1]);
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            printf("Insert '%c' into A\n", B[j - 1]);
            j--;
        }
    }
}

int main() {
    char A[100], B[100];

    printf("Enter string A: ");
    scanf("%s", A);

    printf("Enter string B: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    editDistanceTraceback(A, B, m, n);

    return 0;
}