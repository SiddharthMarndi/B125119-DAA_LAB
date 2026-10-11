
#include <stdio.h>
#include <math.h>

#define MAX 10

/*
Algorithm: Fractional Knapsack with Deterioration

1. Store each item's value, weight, and decay rate.
2. Generate every possible ordering using backtracking.
3. For each ordering:
   a. Calculate effective density at its scheduled time.
   b. Take items sequentially until capacity is exhausted.
   c. Take a fraction of the last item if required.
   d. Calculate the total effective value.
4. Keep the ordering and fractions with the maximum value.
5. Display the optimal schedule and total value.

Time Complexity: O(n! * n)
Auxiliary Space: O(n), excluding stored output.
*/

typedef struct {
    int id;
    double value;
    double weight;
    double decay;
} Item;

Item items[MAX], bestOrder[MAX];
double bestFraction[MAX];
double bestValue = 0.0;
int n;
double capacity;

void evaluate(int order[]) {
    double remaining = capacity;
    double total = 0.0;
    double fractions[MAX] = {0.0};

    for (int t = 0; t < n; t++) {
        int i = order[t];

        double density =
            items[i].value / items[i].weight
            - items[i].decay * t;

        if (density <= 0.0 || remaining <= 0.0)
            continue;

        double take = fmin(items[i].weight, remaining);

        fractions[i] = take / items[i].weight;
        total += take * density;
        remaining -= take;
    }

    if (total > bestValue) {
        bestValue = total;

        for (int i = 0; i < n; i++) {
            bestOrder[i] = items[order[i]];
            bestFraction[order[i]] = fractions[order[i]];
        }
    }
}

void generate(int order[], int used[], int level) {
    if (level == n) {
        evaluate(order);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            order[level] = i;

            generate(order, used, level + 1);

            used[i] = 0;
        }
    }
}

int main(void) {
    int order[MAX], used[MAX] = {0};

    printf("Enter number of items (max %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of items.\n");
        return 1;
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &capacity);

    if (capacity <= 0.0) {
        printf("Capacity must be positive.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        items[i].id = i + 1;

        printf("Enter value, weight and decay rate for item %d: ",
               i + 1);

        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);

        if (items[i].value < 0.0 ||
            items[i].weight <= 0.0 ||
            items[i].decay <= 0.0) {
            printf("Invalid item data.\n");
            return 1;
        }
    }

    generate(order, used, 0);

    printf("\nOptimal scheduling order:\n");

    for (int t = 0; t < n; t++) {
        int id = bestOrder[t].id;
        double fraction = bestFraction[id - 1];

        printf("Time %d: Item %d, Fraction = %.2f\n",
               t, id, fraction);
    }

    printf("\nMaximum total value = %.2f\n", bestValue);

    return 0;
}
