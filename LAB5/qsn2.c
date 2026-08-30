/**
 * Complexity Analysis:
 * Time Complexity:
 *   - Average / Best Case: O(N)
 *     Recurrence: T(N) = T(N/2) + O(N) => O(N)
 *   - Worst Case: O(N^2)
 */

#include <stdio.h>

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

int findKthSmallest(int arr[], int n, int k) {
    int low = 0, high = n - 1;
    int target = k - 1; 

    while (low <= high) {
        int pIndex = partition(arr, low, high);

        if (pIndex == target) {
            return arr[pIndex];
        } else if (pIndex > target) {
            high = pIndex - 1; 
        } else {
            low = pIndex + 1;  
        }
    }
    return -1; 
}

int main() {
    int n, k;

    printf("Enter number of elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter K (1 <= K <= %d): ", n);
    if (scanf("%d", &k) != 1 || k < 1 || k > n) {
        printf("Invalid value of K.\n");
        return 0;
    }

    int result = findKthSmallest(arr, n, k);

    printf("\n--- Result ---\n");
    printf("The %d-th smallest element is: %d\n", k, result);

    return 0;
}