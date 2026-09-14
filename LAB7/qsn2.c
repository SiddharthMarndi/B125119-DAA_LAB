#include <stdio.h>
#include <limits.h>

#define MAX_EGGS 50
#define MAX_FLOORS 1000

// Returns the minimum number of drops required
// with e eggs and f floors.
int eggDrop(int e, int f) {
    int dp[MAX_EGGS + 1][MAX_FLOORS + 1];

    // Base cases
    for (int i = 1; i <= e; i++) {
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    // With one egg, we must test every floor sequentially
    for (int j = 0; j <= f; j++) {
        dp[1][j] = j;
    }

    // Fill the DP table
    for (int eggs = 2; eggs <= e; eggs++) {
        for (int floors = 2; floors <= f; floors++) {

            dp[eggs][floors] = INT_MAX;

            // Try dropping the egg from every possible floor
            for (int x = 1; x <= floors; x++) {

                int breaks = dp[eggs - 1][x - 1];
                int survives = dp[eggs][floors - x];

                int worstCase = 1 + (breaks > survives ? breaks : survives);

                if (worstCase < dp[eggs][floors]) {
                    dp[eggs][floors] = worstCase;
                }
            }
        }
    }

    return dp[e][f];
}

int main() {
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || eggs > MAX_EGGS ||
        floors < 0 || floors > MAX_FLOORS) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = eggDrop(eggs, floors);

    printf("\n--- Super Egg Testing Results ---\n");
    printf("Number of eggs: %d\n", eggs);
    printf("Number of floors: %d\n", floors);
    printf("Minimum number of droppings required: %d\n", result);

    printf("\nComplexity Analysis:\n");
    printf("Time Complexity: O(E * F^2)\n");
    printf("Space Complexity: O(E * F)\n");

    return 0;
}