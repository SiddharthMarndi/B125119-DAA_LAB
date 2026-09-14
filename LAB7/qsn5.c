#include <stdio.h>

// Calculate the number of shots required
// to guarantee hitting the moving target.
//
// We shoot positions 2 to n-1 twice.
// Number of positions in one sweep = n - 2
// Total shots = 2 * (n - 2)

int calculateShots(int n) {
    if (n == 2)
        return 2;

    return 2 * (n - 2);
}

int main() {
    int n;

    printf("Enter the number of hiding spots: ");

    if (scanf("%d", &n) != 1 || n <= 1) {
        printf("Please enter a valid number greater than 1.\n");
        return 1;
    }

    printf("\n--- Moving Target Problem ---\n");
    printf("Number of hiding spots: %d\n", n);

    printf("Shooting sequence: ");

    if (n == 2) {
        printf("1 1");
    } else {
        // First sweep
        for (int i = 2; i <= n - 1; i++) {
            printf("%d ", i);
        }

        // Second sweep
        for (int i = 2; i <= n - 1; i++) {
            printf("%d ", i);
        }
    }

    printf("\nMinimum guaranteed shots: %d\n", calculateShots(n));

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(n)\n");
    printf("Space Complexity: O(1)\n");

    return 0;
}