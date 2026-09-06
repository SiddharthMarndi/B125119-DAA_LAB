#include <stdio.h>
#include <stdlib.h>

long long fibonacci_dp(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    long long result = dp[n];
    free(dp);
    return result;
}

long long fibonacci_optimized(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main() {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }

    long long result_dp = fibonacci_dp(n);
    long long result_opt = fibonacci_optimized(n);

    printf("Fibonacci number F(%d) [Tabulation]      : %lld\n", n, result_dp);
    printf("Fibonacci number F(%d) [Space-Optimized] : %lld\n", n, result_opt);

    return 0;
}