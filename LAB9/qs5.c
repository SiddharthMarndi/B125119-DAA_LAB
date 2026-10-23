
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

/*
Algorithm: Candy Distribution using Bi-directional Greedy

1. Initialize each child's candy count to 1.
2. Traverse left to right:
   If rating[i] > rating[i-1],
   candy[i] = candy[i-1] + 1.
3. Traverse right to left:
   If rating[i] > rating[i+1],
   candy[i] = max(candy[i], candy[i+1] + 1).
4. Sum all candy counts and display the result.

Time Complexity: O(n)
Auxiliary Space: O(n)
*/

int main(void) {
    int n;
    int *rating, *candy;
    long long total = 0;

    printf("Enter number of children: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of children.\n");
        return 1;
    }

    rating = malloc(n * sizeof(int));
    candy = malloc(n * sizeof(int));

    if (rating == NULL || candy == NULL) {
        printf("Memory allocation failed.\n");
        free(rating);
        free(candy);
        return 1;
    }

    printf("Enter the ratings of the children:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &rating[i]) != 1) {
            printf("Invalid rating input.\n");
            free(rating);
            free(candy);
            return 1;
        }

        candy[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1]) {
            if (candy[i] < candy[i + 1] + 1) {
                candy[i] = candy[i + 1] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        total += candy[i];
    }

    printf("\nCandy distribution:\n");

    for (int i = 0; i < n; i++) {
        printf("Child %d (Rating %d): %d candies\n",
               i + 1, rating[i], candy[i]);
    }

    printf("\nMinimum total candies = %lld\n", total);

    free(rating);
    free(candy);

    return 0;
}
