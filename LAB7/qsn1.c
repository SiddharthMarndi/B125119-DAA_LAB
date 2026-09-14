#include <stdio.h>

// Calculate minimum moves required to invert a coin triangle
// Total coins = n(n + 1) / 2
// Minimum moves = floor(total coins / 3)
// Therefore, minimum moves = n(n + 1) / 6

long long calculateMinMoves(int n) {
    return (long long)n * (n + 1) / 6;
}

int main() {
    int height;

    printf("Enter the height (number of rows) of the coin triangle: ");

    if (scanf("%d", &height) != 1 || height <= 0) {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }

    long long min_moves = calculateMinMoves(height);

    printf("\n--- Coin Triangle Inversion Results ---\n");
    printf("Height of triangle (n): %d\n", height);
    printf("Minimum number of moves required: %lld\n", min_moves);

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(1)\n");
    printf("Space Complexity: O(1)\n");

    return 0;
}