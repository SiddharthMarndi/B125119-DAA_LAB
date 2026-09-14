#include <stdio.h>

long long calculateMinMoves(int n) {
    long long moves = 1;

    for (int i = 1; i < n; i++) {
        moves = 2 * moves + 1;
    }

    return moves;
}

int main() {
    int n;

    printf("Enter the number of switches: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n >= 63) {
        printf("Please enter a valid number of switches.\n");
        return 1;
    }

    long long minMoves = calculateMinMoves(n);

    printf("\n--- Security Switches Results ---\n");
    printf("Number of switches: %d\n", n);
    printf("Minimum number of moves required: %lld\n", minMoves);

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(n)\n");
    printf("Space Complexity: O(1)\n");

    return 0;
}