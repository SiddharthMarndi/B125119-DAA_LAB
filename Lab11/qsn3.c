
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 10

// Hash function
unsigned int hashWord(char *s) {

    unsigned int h = 2166136261u;

    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 16777619u;
    }

    return h;
}

// Search word in hash table
int findWord(char *s, char words[][MAXL + 1],
             int *table, int size) {

    unsigned int pos = hashWord(s) & (size - 1);

    while (table[pos] != -1) {

        int id = table[pos];

        if (strcmp(words[id], s) == 0)
            return id;

        pos = (pos + 1) & (size - 1);
    }

    return -1;
}

// Insert word into hash table
void insertWord(char *s, int id, int *table, int size) {

    unsigned int pos = hashWord(s) & (size - 1);

    while (table[pos] != -1)
        pos = (pos + 1) & (size - 1);

    table[pos] = id;
}

// Expand one complete BFS level
int expandFrontier(
    int *front, int count,
    int *nextFront, int *nextCount,
    int *distThis, int *distOther,
    char words[][MAXL + 1],
    int L, int *table, int size
) {

    int best = -1;

    for (int i = 0; i < count; i++) {

        int u = front[i];

        char temp[MAXL + 1];

        strcpy(temp, words[u]);

        // Generate neighbouring words
        for (int j = 0; j < L; j++) {

            char original = temp[j];

            for (char c = 'a'; c <= 'z'; c++) {

                if (c == original)
                    continue;

                temp[j] = c;

                int v = findWord(
                    temp, words, table, size
                );

                if (v != -1) {

                    if (distThis[v] == -1) {

                        distThis[v] = distThis[u] + 1;

                        nextFront[(*nextCount)++] = v;
                    }

                    // Check intersection of searches
                    if (distOther[v] != -1) {

                        int candidate =
                            distThis[v] + distOther[v];

                        if (best == -1 || candidate < best)
                            best = candidate;
                    }
                }
            }

            temp[j] = original;
        }
    }

    return best;
}

// Bidirectional BFS
int bidirectionalBFS(
    int start, int target,
    char words[][MAXL + 1],
    int N, int L,
    int *table, int size
) {

    if (start == target)
        return 0;

    int *distA = malloc((N + 1) * sizeof(int));
    int *distB = malloc((N + 1) * sizeof(int));

    int *frontA = malloc((N + 1) * sizeof(int));
    int *nextA = malloc((N + 1) * sizeof(int));

    int *frontB = malloc((N + 1) * sizeof(int));
    int *nextB = malloc((N + 1) * sizeof(int));

    for (int i = 0; i <= N; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    // Initialize both searches
    int countA = 1, countB = 1;

    frontA[0] = start;
    frontB[0] = target;

    distA[start] = 0;
    distB[target] = 0;

    int answer = -1;

    while (countA > 0 && countB > 0) {

        int nextCount = 0;
        int result;

        // Expand smaller frontier
        if (countA <= countB) {

            result = expandFrontier(
                frontA, countA,
                nextA, &nextCount,
                distA, distB,
                words, L, table, size
            );

            int *temp = frontA;
            frontA = nextA;
            nextA = temp;

            countA = nextCount;
        }

        else {

            result = expandFrontier(
                frontB, countB,
                nextB, &nextCount,
                distB, distA,
                words, L, table, size
            );

            int *temp = frontB;
            frontB = nextB;
            nextB = temp;

            countB = nextCount;
        }

        if (result != -1) {
            answer = result;
            break;
        }
    }

    free(distA);
    free(distB);
    free(frontA);
    free(nextA);
    free(frontB);
    free(nextB);

    return answer;
}

int main(void) {

    int N;

    printf("Enter number of dictionary words:\n");
    scanf("%d", &N);

    char (*words)[MAXL + 1] =
        malloc((N + 1) * sizeof(*words));

    printf("Enter dictionary words:\n");

    for (int i = 0; i < N; i++)
        scanf("%10s", words[i]);

    char A[MAXL + 1], B[MAXL + 1];

    printf("Enter starting and target words:\n");
    scanf("%10s %10s", A, B);

    int L = strlen(A);

    if (strlen(B) != (size_t)L) {
        printf("Invalid word lengths\n");
        free(words);
        return 0;
    }

    // Target must exist in dictionary
    int size = 1;

    while (size < 4 * N)
        size *= 2;

    int *table = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        table[i] = -1;

    // Build hash table
    for (int i = 0; i < N; i++)
        insertWord(words[i], i, table, size);

    int start = findWord(A, words, table, size);
    int target = findWord(B, words, table, size);

    if (target == -1) {

        printf("Target word not found in dictionary\n");
        free(words);
        free(table);
        return 0;
    }

    // Starting word need not be in dictionary
    if (start == -1) {

        start = N;
        strcpy(words[N], A);
    }

    int answer = bidirectionalBFS(
        start, target, words, N,
        L, table, size
    );

    if (answer == -1)
        printf("No valid transformation exists\n");
    else
        printf("Minimum transformations = %d\n", answer);

    free(words);
    free(table);

    return 0;
}

// Complexity Analysis:
//
// 1. Hash table construction takes O(N * L) expected time.
// 2. Each word is expanded at most once in each
//    direction of Bidirectional BFS.
// 3. For every word, we change each of its L characters
//    into 25 other lowercase characters.
// 4. Each generated word is searched in the hash table
//    in expected O(1) time.
//
// Overall Expected Time Complexity: O(26 * N * L)
//                                  = O(N * L)
//
// Space Complexity: O(N * L)
//
// Dictionary Storage: O(N * L)
// Hash Table: O(N)
// Distance Arrays: O(N)
// BFS Frontiers: O(N)
