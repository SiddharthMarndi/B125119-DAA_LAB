#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int weighings_count = 0;

int weigh(const double coins[], int l_start, int l_end, int r_start, int r_end) {
    weighings_count++;
    double sum_l = 0.0;
    double sum_r = 0.0;

    for (int i = l_start; i <= l_end; i++) sum_l += coins[i];
    for (int i = r_start; i <= r_end; i++) sum_r += coins[i];

    if (sum_l < sum_r) return -1;
    if (sum_l > sum_r) return 1;
    return 0;
}

int find_lighter_coin(const double coins[], int low, int high, double standard_weight) {
    int count = high - low + 1;

    if (count == 1) {
        if (coins[low] < standard_weight) return low;
        return -1;
    }

    if (count % 2 == 0) {
        int half = count / 2;
        int mid = low + half - 1;

        int res = weigh(coins, low, mid, mid + 1, high);

        if (res == -1) {
            return find_lighter_coin(coins, low, mid, standard_weight);
        } else if (res == 1) {
            return find_lighter_coin(coins, mid + 1, high, standard_weight);
        } else {
            return -1;
        }
    } else {
        int half = count / 2;
        int l_start = low;
        int l_end = low + half - 1;
        int r_start = low + half;
        int r_end = low + 2 * half - 1;
        int extra = high;

        int res = weigh(coins, l_start, l_end, r_start, r_end);

        if (res == -1) {
            return find_lighter_coin(coins, l_start, l_end, standard_weight);
        } else if (res == 1) {
            return find_lighter_coin(coins, r_start, r_end, standard_weight);
        } else {
            weighings_count++;
            if (coins[extra] < coins[low]) {
                return extra;
            } else {
                return -1;
            }
        }
    }
}

void run_test(const char* test_name, int n, int defective_index, double std_weight, double def_weight) {
    double* coins = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        coins[i] = std_weight;
    }

    if (defective_index >= 0 && defective_index < n) {
        coins[defective_index] = def_weight;
    }

    weighings_count = 0;
    int result = find_lighter_coin(coins, 0, n - 1, std_weight);

    printf("%s (n = %d):\n", test_name, n);
    if (result == -1) {
        printf("Result: None (All coins perfect)\n");
    } else {
        printf("Result: Defective coin found at index %d\n", result);
    }
    printf("Weighings: %d\n\n", weighings_count);

    free(coins);
}

int main() {
    double std_weight = 10.0;
    double def_weight = 9.0;

    run_test("Test 1 (Even n, Defective Present)", 16, 7, std_weight, def_weight);
    run_test("Test 2 (Even n, No Defective)", 16, -1, std_weight, def_weight);
    run_test("Test 3 (Odd n, Defective at End)", 15, 14, std_weight, def_weight);
    run_test("Test 4 (Odd n, Defective in Middle)", 27, 12, std_weight, def_weight);
    run_test("Test 5 (Large n, Defective Present)", 100, 43, std_weight, def_weight);
    run_test("Test 6 (Large n, No Defective)", 100, -1, std_weight, def_weight);

    return 0;
}