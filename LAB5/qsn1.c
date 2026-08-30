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

int quickSelect(int arr[], int n, int k) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int pIndex = partition(arr, low, high);

        if (pIndex == k) {
            return arr[pIndex];
        } else if (pIndex > k) {
            high = pIndex - 1;
        } else {
            low = pIndex + 1;
        }
    }
    return -1;
}

double findMedian(int arr[], int n) {
    if (n % 2 != 0) {
        return (double)quickSelect(arr, n, n / 2);
    } else {
        int mid2 = quickSelect(arr, n, n / 2);
        int mid1 = quickSelect(arr, n, (n / 2) - 1);
        return (mid1 + mid2) / 2.0;
    }
}

int main() {
    int n;
    printf("Enter number of elements (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 0;
    }

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    double median = findMedian(arr, n);

    printf("\n--- Result ---\n");
    if (n % 2 != 0) {
        printf("Median: %.0f\n", median);
    } else {
        printf("Median: %.2f\n", median);
    }

    return 0;
}