/* 
 * ALGORITHM & COMPLEXITY ANALYSIS: Collatz Conjecture Simulation & Analysis
 * 
 * Algorithm Steps (Iterative Simulation & Modular Design):
 * 1. Define a function 'analyzeCollatz' to trace a single starting value n >= 1:
 *    - While n != 1, apply the recurrence relation: if even, n = n / 2; if odd, n = 3 * n + 1.
 *    - Count the total steps and track the maximum peak value reached during the trajectory.
 *    - Include integer overflow protection checks using standard limits.
 * 2. Define a function 'analyzeInterval' to scan across an interval [a, b]:
 *    - Iterate through each integer in the range, simulating its sequence to find which number produces the longest trajectory.
 * 3. Use modular functional decomposition in C for single-value tracking and interval analysis.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(k) per number, where k is the total number of steps required to reach 1. For an interval [a, b] of size N, the time complexity depends on the trajectory lengths of the numbers in the range.
 * - Space Complexity: O(1) auxiliary space as simulation variables are maintained iteratively.
 */

#include <stdio.h>
#include <limits.h>

void analyzeCollatz(long long n) {
    if (n < 1) {
        printf("Error: Starting value must be >= 1[cite: 2].\n");
        return;
    }

    long long current = n;
    long long steps = 0;
    long long max_val = n;

    printf("Trajectory for n = %lld: %lld ", n, current);

    while (current != 1) {
        if (current % 2 == 0) {
            current = current / 2;
        } else {
            if (current > (LLONG_MAX - 1) / 3) {
                printf("\nOverflow detected during sequence computation!\n");
                return;
            }
            current = 3 * current + 1;
        }
        
        printf("-> %lld ", current);
        steps++;
        if (current > max_val) {
            max_val = current;
        }
    }

    printf("\nTotal Steps: %lld | Peak Value: %lld\n\n", steps, max_val);
}

void analyzeInterval(long long a, long long b) {
    if (a > b || a < 1) {
        printf("Invalid interval range. Ensure a <= b and a >= 1[cite: 2].\n");
        return;
    }

    long long max_steps = 0;
    long long max_steps_num = a;

    for (long long i = a; i <= b; i++) {
        long long current = i;
        long long steps = 0;
        
        while (current != 1) {
            if (current % 2 == 0) {
                current = current / 2;
            } else {
                if (current > (LLONG_MAX - 1) / 3) break;
                current = 3 * current + 1;
            }
            steps++;
        }

        if (steps > max_steps) {
            max_steps = steps;
            max_steps_num = i;
        }
    }

    printf("Interval Analysis [%lld, %lld]:\n", a, b);
    printf("Number with maximum steps: %lld (Steps: %lld)\n", max_steps_num, max_steps);
}

int main() {
    long long n, a, b;

    printf("Enter a starting value for single analysis: ");
    scanf("%lld", &n);
    analyzeCollatz(n);

    printf("Enter interval range [a b] for batch analysis: ");
    scanf("%lld %lld", &a, &b);
    analyzeInterval(a, b);

    return 0;
}