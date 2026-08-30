/**
 * Complexity Analysis:
 * Time Complexity:
 *   - Best Case:    O(N log N)
 *   - Average Case: O(N log N)
 *   - Worst Case:   O(N^2)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of random elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    srand(time(NULL));

    FILE *fin = fopen("input.txt", "w");
    if (fin == NULL) {
        printf("Error creating input file!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int num = rand() % 1000; 
        fprintf(fin, "%d ", num);
    }
    fclose(fin);
    printf("Generated %d random numbers in 'input.txt'.\n", n);

    fin = fopen("input.txt", "r");
    if (fin == NULL) {
        printf("Error opening input file for reading!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
    }
    fclose(fin);

    quickSort(arr, 0, n - 1);

    FILE *fout = fopen("sorted.txt", "w");
    if (fout == NULL) {
        printf("Error creating output file!\n");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d ", arr[i]);
    }
    fclose(fout);
    printf("Sorted numbers successfully written to 'sorted.txt'.\n");

    printf("\nSorted Array (First %d elements):\n", n < 10 ? n : 10);
    for (int i = 0; i < (n < 10 ? n : 10); i++) {
        printf("%d ", arr[i]);
    }
    if (n > 10) printf("... [check sorted.txt for full list]");
    printf("\n");

    free(arr);
    return 0;
}