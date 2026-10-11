
#include <stdio.h>
#include <limits.h>

#define MAX 100
/*
Algorithm: Optimal Alphabetic Binary Tree
(Dynamic Programming Validation)

1. Read ordered leaf weights.
2. Compute prefix sums.
3. For each interval [i, j], try every split k.
4. Calculate:
   dp[i][j] = intervalSum(i,j)
              + dp[i][k] + dp[k+1][j]
5. Store the split giving minimum cost.
6. Reconstruct the tree using stored split points.

Time Complexity: O(n^3)
Auxiliary Space: O(n^2)
*/

long long weight[MAX];
long long prefix[MAX + 1];
long long dp[MAX][MAX];
int split[MAX][MAX];
int n;

long long intervalSum(int i, int j) {
    return prefix[j + 1] - prefix[i];
}

void buildTree(int i, int j) {
    if (i == j) {
        printf("%lld", weight[i]);
        return;
    }

    int k = split[i][j];

    printf("(");
    buildTree(i, k);
    printf(" + ");
    buildTree(k + 1, j);
    printf(")");
}

int main(void) {
    printf("Enter number of weights (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of weights.\n");
        return 1;
    }

    printf("Enter ordered weights:\n");

    prefix[0] = 0;

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &weight[i]) != 1 ||
            weight[i] <= 0 ||
            prefix[i] > LLONG_MAX - weight[i]) {
            printf("Invalid weight or weight sum overflow.\n");
            return 1;
        }

        prefix[i + 1] = prefix[i] + weight[i];
        dp[i][i] = 0;
        split[i][i] = i;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length <= n; i++) {
            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            long long sum = intervalSum(i, j);

            for (int k = i; k < j; k++) {
                long long left = dp[i][k];
                long long right = dp[k + 1][j];

                if (left > LLONG_MAX - right)
                    continue;

                long long candidate = left + right;

                if (candidate > LLONG_MAX - sum)
                    continue;

                candidate += sum;

                if (candidate < dp[i][j]) {
                    dp[i][j] = candidate;
                    split[i][j] = k;
                }
            }

            if (dp[i][j] == LLONG_MAX) {
                printf("Cost overflow.\n");
                return 1;
            }
        }
    }

    printf("\nOptimal alphabetic merge pattern:\n");
    buildTree(0, n - 1);

    printf("\nMinimum weighted path length = %lld\n",
           dp[0][n - 1]);

    return 0;
}
