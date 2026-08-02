#include <stdio.h>


int find_partition_point(int arr[], int n) {
    int low = 0, high = n - 1;
    int transition_index = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1) {
            transition_index = mid; 
            high = mid - 1;         
        } else {
            low = mid + 1;          
        }
    }

    return transition_index;
}

int main() {
    int arr[] = {0, 0, 0, 0, 0, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("===================================================\n");
    printf("       DAA LAB 01 - FIND PARTITION POINT           \n");
    printf("===================================================\n");
    
    printf("Array: [ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n\n");

    int index = find_partition_point(arr, n);

    if (index != -1) {
        printf("Partition (Transition from 0 to 1) found at index: %d\n", index);
        printf("Verification: arr[%d] = %d, arr[%d] = %d\n", index - 1, arr[index - 1], index, arr[index]);
    } else {
        printf("No transition point found (array contains only 0s).\n");
    }

    printf("===================================================\n");

    return 0;
}