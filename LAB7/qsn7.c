#include <stdio.h>
#include <limits.h>

#define MAX 100

// Print the optimal parenthesization
void printOptimalOrder(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    // Split point stored in s[i][j]
    printOptimalOrder(s, i, s[i][j]);
    printOptimalOrder(s, s[i][j] + 1, j);

    printf(")");
}

int main() {
    int n;
    int p[MAX];
    long long m[MAX][MAX];
    int s[MAX][MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX) {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    printf("Enter the %d matrix dimensions:\n", n + 1);

    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);

        if (p[i] <= 0) {
            printf("Invalid dimension.\n");
            return 1;
        }
    }

    // Cost of multiplying one matrix is zero
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // chainLength = number of matrices in the chain
    for (int chainLength = 2;
         chainLength <= n;
         chainLength++) {

        for (int i = 1;
             i <= n - chainLength + 1;
             i++) {

            int j = i + chainLength - 1;

            m[i][j] = LLONG_MAX;

            // Try every possible split
            for (int k = i; k < j; k++) {

                long long cost =
                    m[i][k]
                    + m[k + 1][j]
                    + (long long)p[i - 1]
                    * p[k]
                    * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\n--- Matrix Chain Multiplication ---\n");

    printf("Minimum number of scalar multiplications: %lld\n",
           m[1][n]);

    printf("Optimal parenthesization: ");
    printOptimalOrder(s, 1, n);
    printf("\n");

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(n^3)\n");
    printf("Space Complexity: O(n^2)\n");

    return 0;
}