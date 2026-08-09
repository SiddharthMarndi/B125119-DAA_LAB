#include <stdio.h>
#include <stdlib.h>

// Merge subroutine tracking total element comparisons
int merge_track(const int arr1[], int size1, const int arr2[], int size2, int result[]) {
    int i = 0, j = 0, k = 0, comps = 0;
    while (i < size1 && j < size2) {
        comps++;
        if (arr1[i] <= arr2[j]) result[k++] = arr1[i++];
        else result[k++] = arr2[j++];
    }
    while (i < size1) result[k++] = arr1[i++];
    while (j < size2) result[k++] = arr2[j++];
    return comps;
}

int main() {
    int k = 4, n = 3;
    int data[4][3] = {
        {1, 5, 9},
        {2, 6, 10},
        {3, 7, 11},
        {4, 8, 12}
    };

    printf("===============================================================\n");
    printf("   QUESTION 3(b): PAIRWISE MERGE (METHOD 2) VALIDATION        \n");
    printf("===============================================================\n\n");

    printf("Input Configuration: k = %d arrays, n = %d elements each\n", k, n);
    for (int i = 0; i < k; i++) {
        printf("  Array %d: ", i + 1);
        for (int j = 0; j < n; j++) printf("%d ", data[i][j]);
        printf("\n");
    }
    printf("\n------------------- Round-by-Round Trace -------------------\n");

    int num_arrays = k;
    int current_size = n;
    int total_comps = 0;
    int round = 1;

    int** current_arrays = (int**)malloc(k * sizeof(int*));
    int** next_arrays = (int**)malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        current_arrays[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) current_arrays[i][j] = data[i][j];
    }

    // Pairwise tree-merge loop
    while (num_arrays > 1) {
        int next_count = 0;
        int next_size = current_size * 2;
        int round_comps = 0;

        for (int i = 0; i < num_arrays; i += 2) {
            if (i + 1 < num_arrays) {
                next_arrays[next_count] = (int*)malloc(next_size * sizeof(int));
                int comps = merge_track(current_arrays[i], current_size, current_arrays[i + 1], current_size, next_arrays[next_count]);
                round_comps += comps;
                free(current_arrays[i]);
                free(current_arrays[i + 1]);
                next_count++;
            } else {
                next_arrays[next_count++] = current_arrays[i];
            }
        }

        total_comps += round_comps;
        printf("[Round %d] Merged pairs into %d array(s) of size %d | Comps: %d\n", 
               round++, next_count, next_size, round_comps);

        for (int i = 0; i < next_count; i++) current_arrays[i] = next_arrays[i];
        num_arrays = next_count;
        current_size = next_size;
    }

    printf("\n---------------- Theoretical Validation ----------------\n");
    printf("Total Key Comparisons Made : %d\n", total_comps);
    printf("Tree Height / Rounds       : log2(k) = log2(%d) = 2\n", k);
    printf("Theoretical Time Complexity: O(n * k * log2 k) = O(%d * %d * 2) = O(%d)\n", 
           n, k, n * k * 2);

    printf("\n------------------ Final Merged Result ------------------\n");
    printf("Merged Array: ");
    for (int j = 0; j < k * n; j++) printf("%d ", current_arrays[0][j]);
    printf("\n===============================================================\n");

    free(current_arrays[0]);
    free(current_arrays);
    free(next_arrays);
    return 0;
}