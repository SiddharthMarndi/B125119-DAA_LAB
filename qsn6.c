#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int compare_integers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

bool check_uniqueness_brute_force(int arr[], int n, long long *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[i] == arr[j]) {
                return false; 
            }
        }
    }
    return true; 
}

bool check_uniqueness_sorting(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare_integers);

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            return false; 
        }
    }
    return true; 
}

int main() {
    srand(time(NULL));

    int test_sizes[] = {1000, 5000, 20000};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

    printf("=========================================================\n");
    printf("         DAA LAB 01 - ELEMENT UNIQUENESS CHECK           \n");
    printf("=========================================================\n\n");

    for (int t = 0; t < num_tests; t++) {
        int n = test_sizes[t];
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int val = rand() % (2 * n);
            arr1[i] = val;
            arr2[i] = val;
        }

        long long comparisons = 0;

        clock_t start_bf = clock();
        bool is_unique_bf = check_uniqueness_brute_force(arr1, n, &comparisons);
        clock_t end_bf = clock();
        double time_bf = (double)(end_bf - start_bf) / CLOCKS_PER_SEC;

        clock_t start_sort = clock();
        bool is_unique_sort = check_uniqueness_sorting(arr2, n);
        clock_t end_sort = clock();
        double time_sort = (double)(end_sort - start_sort) / CLOCKS_PER_SEC;

        printf("--- Test Case: N = %d ---\n", n);
        printf("Brute Force Method [O(n^2)]  : %s | Time: %.4f sec | Comparisons: %lld\n",
               is_unique_bf ? "Unique" : "Duplicates Found", time_bf, comparisons);
        printf("Sorting Method     [O(n log n)]: %s | Time: %.4f sec\n\n",
               is_unique_sort ? "Unique" : "Duplicates Found", time_sort);

        free(arr1);
        free(arr2);
    }

    printf("=========================================================\n");

    return 0;
}