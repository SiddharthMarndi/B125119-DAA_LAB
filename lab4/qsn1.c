#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
ALGORITHM: Stable Color Sort with User Input in O(n) Time and O(n) Space

1. Represent each pair as a struct with an integer 'number' and a 'Color' enum:
      RED = 0, BLUE = 1, YELLOW = 2.
2. Read 'n' (number of pairs) dynamically from standard user input.
3. Read 'n' pairs of (number, color_string) into a dynamically allocated array:
   - Convert color strings (e.g., "red", "RED", "blue", "yellow") to enum values.
4. Frequency Count (First Pass):
   - Traverse the input array of size n.
   - Increment count[item.color] for each entry.
5. Prefix Sums (Starting Indices):
   - start_index[RED] = 0
   - start_index[BLUE] = count[RED]
   - start_index[YELLOW] = count[RED] + count[BLUE]
6. Stable Placement (Second Pass):
   - Allocate an auxiliary array `output` of size n.
   - Scan input left-to-right (from index 0 to n-1).
   - Place current element at output[start_index[item.color]].
   - Increment start_index[item.color].
   (Left-to-right processing guarantees stability, preserving the pre-sorted
    order of numbers for identical colors).
7. Copy sorted entries back to the original array, print results, and free memory.

Complexity Analysis:
- Time Complexity: O(n) — single pass to count, single pass to distribute.
- Space Complexity: O(n) — output buffer of size n to preserve stability.

*/

typedef enum {
    RED = 0,
    BLUE = 1,
    YELLOW = 2,
    INVALID = -1
} Color;

typedef struct {
    int number;
    Color color;
} Item;

Color parse_color(const char *str) {
    char lower[16];
    int i = 0;
    while (str[i] && i < 15) {
        lower[i] = (char)tolower((unsigned char)str[i]);
        i++;
    }
    lower[i] = '\0';

    if (strcmp(lower, "red") == 0 || strcmp(lower, "r") == 0) return RED;
    if (strcmp(lower, "blue") == 0 || strcmp(lower, "b") == 0) return BLUE;
    if (strcmp(lower, "yellow") == 0 || strcmp(lower, "y") == 0) return YELLOW;
    return INVALID;
}

const char* color_to_string(Color c) {
    switch (c) {
        case RED:    return "RED";
        case BLUE:   return "BLUE";
        case YELLOW: return "YELLOW";
        default:     return "UNKNOWN";
    }
}

void stable_color_sort(Item arr[], int n) {
    int count[3] = {0, 0, 0};
    int start_index[3] = {0, 0, 0};
    Item *output = (Item *)malloc(n * sizeof(Item));

    for (int i = 0; i < n; i++) {
        count[arr[i].color]++;
    }

    start_index[RED] = 0;
    start_index[BLUE] = count[RED];
    start_index[YELLOW] = count[RED] + count[BLUE];

    for (int i = 0; i < n; i++) {
        int c = arr[i].color;
        output[start_index[c]] = arr[i];
        start_index[c]++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void print_items(Item arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %s) ", arr[i].number, color_to_string(arr[i].color));
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of items (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    Item *items = (Item *)malloc(n * sizeof(Item));

    printf("Enter %d items as '<number> <color>' in ascending order of numbers:\n", n);
    printf("Allowed colors: red, blue, yellow (case-insensitive)\n");

    for (int i = 0; i < n; i++) {
        char color_str[32];
        printf("Item %d: ", i + 1);
        if (scanf("%d %s", &items[i].number, color_str) != 2) {
            printf("Error reading input for item %d.\n", i + 1);
            free(items);
            return 1;
        }

        Color c = parse_color(color_str);
        if (c == INVALID) {
            printf("Invalid color '%s'. Please enter red, blue, or yellow.\n", color_str);
            i--;
            continue;
        }
        items[i].color = c;
    }

    printf("Input (sorted by number)\n");
    print_items(items, n);

    stable_color_sort(items, n);

    printf("Output (sorted by color: RED -> BLUE -> YELLOW)\n");
    print_items(items, n);

    free(items);
    return 0;
}