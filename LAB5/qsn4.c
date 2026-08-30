/**
 * Complexity Analysis:
 * Time Complexity:
 *   - Build Heap:    O(N)
 *   - Sort/Heapify:  O(N log N)
 *   - Best Case:     O(N log N)
 *   - Average Case:  O(N log N)
 *   - Worst Case:    O(N log N)
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

void heapify(int arr[], int n, int i) {
    int largest = i;       
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter number of random elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
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

    heapSort(arr, n);

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
    if (n > 10) printf("... [see sorted.txt for full list]");
    printf("\n");

    free(arr);
    return 0;
}