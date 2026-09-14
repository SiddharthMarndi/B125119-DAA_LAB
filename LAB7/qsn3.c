#include <stdio.h>
#include <limits.h>

#define MAX_DISKS 30

// Calculate minimum moves for Reve's Puzzle
// using the Frame-Stewart dynamic programming approach.
unsigned long long revePuzzle(int n) {
    unsigned long long dp[MAX_DISKS + 1];

    dp[0] = 0;
    dp[1] = 1;

    for (int disks = 2; disks <= n; disks++) {
        dp[disks] = ULLONG_MAX;

        // Try every possible split k
        for (int k = 1; k < disks; k++) {

            // Number of moves for the remaining disks
            // using the ordinary 3-peg Tower of Hanoi:
            // 2^(disks-k) - 1
            unsigned long long hanoi =
                (1ULL << (disks - k)) - 1;

            unsigned long long moves =
                2 * dp[k] + hanoi;

            if (moves < dp[disks]) {
                dp[disks] = moves;
            }
        }
    }

    return dp[n];
}

int main() {
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_DISKS) {
        printf("Invalid input.\n");
        return 1;
    }

    unsigned long long result = revePuzzle(n);

    printf("\n--- Reve's Puzzle ---\n");
    printf("Number of disks: %d\n", n);
    printf("Minimum number of moves: %llu\n", result);

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(n^2)\n");
    printf("Space Complexity: O(n)\n");

    return 0;
}