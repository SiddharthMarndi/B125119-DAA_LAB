
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define MAXLEN 10000

char *str[MAXN];

// Find maximum suffix-prefix overlap
int overlap(char *a, char *b) {

    int lenA = strlen(a);
    int lenB = strlen(b);

    int max = lenA < lenB ? lenA : lenB;

    for (int k = max; k >= 1; k--) {

        if (strncmp(a + lenA - k, b, k) == 0)
            return k;
    }

    return 0;
}

// Merge two strings using their maximum overlap
char *mergeStrings(char *a, char *b, int k) {

    int lenA = strlen(a);
    int lenB = strlen(b);

    char *result = malloc(lenA + lenB + 1);

    strcpy(result, a);

    strcat(result, b + k);

    return result;
}

// Remove strings that are substrings of another string
void removeContained(int *n) {

    for (int i = 0; i < *n; i++) {

        for (int j = 0; j < *n; j++) {

            if (i != j && str[i] != NULL &&
                str[j] != NULL &&
                strstr(str[j], str[i]) != NULL) {

                free(str[i]);
                str[i] = NULL;
                break;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < *n; i++) {

        if (str[i] != NULL) {
            str[count++] = str[i];
        }
    }

    *n = count;
}

int main() {

    int n;

    printf("Enter number of strings:\n");
    scanf("%d", &n);

    if (n <= 0 || n > MAXN) {
        printf("Invalid number of strings\n");
        return 0;
    }

    printf("Enter strings:\n");

    for (int i = 0; i < n; i++) {

        char temp[MAXLEN];

        scanf("%9999s", temp);

        str[i] = malloc(strlen(temp) + 1);

        strcpy(str[i], temp);
    }

    // Remove duplicates and contained strings
    removeContained(&n);

    // Greedy merging
    while (n > 1) {

        int maxOverlap = -1;
        int bestI = -1, bestJ = -1;

        // Find pair with maximum overlap
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                if (i == j)
                    continue;

                int k = overlap(str[i], str[j]);

                if (k > maxOverlap) {

                    maxOverlap = k;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        // Merge selected strings
        char *merged = mergeStrings(
            str[bestI],
            str[bestJ],
            maxOverlap
        );

        free(str[bestI]);
        free(str[bestJ]);

        str[bestI] = merged;

        // Remove second string
        for (int i = bestJ; i < n - 1; i++)
            str[i] = str[i + 1];

        n--;

        // Remove strings contained in merged result
        removeContained(&n);
    }

    printf("\nShortest Superstring (Greedy):\n");
    printf("%s\n", str[0]);

    printf("\nLength of superstring: %lu\n",
           (unsigned long)strlen(str[0]));

    free(str[0]);

    return 0;
}

// Complexity Analysis:
//
// 1. Finding overlap between two strings takes O(L) time.
// 2. Finding maximum overlap among all pairs takes
//    O(N^2 * L) time per iteration.
// 3. There are at most N-1 merging iterations.
// 4. Removing contained strings takes O(N^2 * L)
//    time per iteration.
//
// Overall Time Complexity: O(N^3 * L)
//
// Space Complexity: O(N * S)
//
// N = Number of input strings
// L = Maximum length of an intermediate string
// S = Total length of all input strings
//
// Note:
// This is a greedy heuristic, not an exact algorithm.
// It does not guarantee the shortest possible superstring.
