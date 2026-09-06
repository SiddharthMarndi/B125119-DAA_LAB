#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
Matrix Chain Multiplication using Dynamic Programming

1. Recurrence Relation:
   Let m[i][j] be the minimum number of scalar multiplications needed to compute
   the matrix product A_i * A_{i+1} * ... * A_j, where matrix A_k has dimensions
   arr[k-1] x arr[k].

   Base Case:
     m[i][i] = 0   for all 1 <= i < N (a single matrix requires 0 multiplications)

   Recursive Step (for chain length L from 2 to N - 1, and split point k from i to j - 1):
     m[i][j] = min_{i <= k < j} { m[i][k] + m[k+1][j] + arr[i-1] * arr[k] * arr[j] }

2. Complexity Analysis:
   - Time Complexity: O(N^3)
     There are three nested loops:
       * Outer loop for chain length L: runs (N - 1) times.
       * Middle loop for starting index i: runs at most N times.
       * Inner loop for split point k: runs at most N times.
     Total operations = sum_{L=2}^{N-1} (N - L) * (L - 1) = O(N^3).
   - Space Complexity: O(N^2)
     Uses a 2D table m of size N x N to store optimal costs, and optionally an
     N x N table 'bracket' to store optimal split points.
*/

void print_optimal_parens(int **bracket, int i, int j, char *name) {
    if (i == j) {
        printf("%c%d", *name, i);
        return;
    }
    printf("(");
    print_optimal_parens(bracket, i, bracket[i][j], name);
    print_optimal_parens(bracket, bracket[i][j] + 1, j, name);
    printf(")");
}

int matrix_chain_order(const int arr[], int N) {
    int n = N - 1; 

    int **m = (int **)malloc(N * sizeof(int *));
    int **bracket = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        m[i] = (int *)malloc(N * sizeof(int));
        bracket[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }
    }

    int min_cost = m[1][n];

    char name = 'A';
    printf("Optimal Parenthesization: ");
    print_optimal_parens(bracket, 1, n, &name);
    printf("\n");

    for (int i = 0; i < N; i++) {
        free(m[i]);
        free(bracket[i]);
    }
    free(m);
    free(bracket);

    return min_cost;
}

int main() {
    int N;
    printf("Enter N (size of dimension array arr): ");
    if (scanf("%d", &N) != 1 || N < 2) {
        printf("Invalid input. N must be at least 2.\n");
        return 1;
    }

    int *arr = (int *)malloc(N * sizeof(int));
    printf("Enter %d dimensions:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int min_multiplications = matrix_chain_order(arr, N);
    printf("Minimum number of scalar multiplications: %d\n", min_multiplications);

    free(arr);
    return 0;
}