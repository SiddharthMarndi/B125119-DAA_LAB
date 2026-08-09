#include <stdio.h>
#include <stdlib.h>

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
    printf("   QUESTION 3(a): SEQUENTIAL MERGE (METHOD 1) VALIDATION      \n");
    printf("===============================================================\n\n");

    printf("Input Configuration: k = %d arrays, n = %d elements each\n", k, n);
    for (int i = 0; i < k; i++) {
        printf("  Array %d: ", i + 1);
        for (int j = 0; j < n; j++) printf("%d ", data[i][j]);
        printf("\n");
    }
    printf("\n------------------- Step-by-Step Trace -------------------\n");

    int* current = (int*)malloc(k * n * sizeof(int));
    for (int j = 0; j < n; j++) current[j] = data[0][j];

    int current_size = n;
    int total_comps = 0;
    int* temp = (int*)malloc(k * n * sizeof(int));

    for (int i = 1; i < k; i++) {
        int comps = merge_track(current, current_size, data[i], n, temp);
        total_comps += comps;
        current_size += n;

        for (int j = 0; j < current_size; j++) current[j] = temp[j];

        printf("[Step %d] Merging result (%d elem) with Array %d (%d elem) | Comps: %d\n", 
               i, current_size - n, i + 1, n, comps);
    }

    printf("\n---------------- Theoretical Validation ----------------\n");
    printf("Total Key Comparisons Made : %d\n", total_comps);
    printf("Worst-Case Recurrence      : Sum_{i=2}^{k} (i * n)\n");
    printf("Theoretical Time Complexity: O(n * k^2) = O(%d * %d^2) = O(%d)\n", 
           n, k, n * k * k);

    printf("\n------------------ Final Merged Result ------------------\n");
    printf("Merged Array: ");
    for (int i = 0; i < k * n; i++) printf("%d ", current[i]);
    printf("\n===============================================================\n");

    free(current);
    free(temp);
    return 0;
}