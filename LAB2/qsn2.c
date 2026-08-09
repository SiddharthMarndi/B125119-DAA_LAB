#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 600
#define STEP 25
#define START_N 25

// --- Standard 2-Way Merge Sort ---
long long merge_2way(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    long long comps = 0;

    while (i < n1 && j < n2) {
        comps++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
    return comps;
}

long long merge_sort_2way(int arr[], int l, int r) {
    long long comps = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        comps += merge_sort_2way(arr, l, m);
        comps += merge_sort_2way(arr, m + 1, r);
        comps += merge_2way(arr, l, m, r);
    }
    return comps;
}

// --- Modified 3-Way Merge Sort ---
long long merge_3way(int arr[], int l, int m1, int m2, int r) {
    int n1 = m1 - l + 1;
    int n2 = m2 - m1;
    int n3 = r - m2;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* M = (int*)malloc(n2 * sizeof(int));
    int* R = (int*)malloc(n3 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) M[i] = arr[m1 + 1 + i];
    for (int i = 0; i < n3; i++) R[i] = arr[m2 + 1 + i];

    int i = 0, j = 0, k = 0, idx = l;
    long long comps = 0;

    // 3-way comparison loop
    while (i < n1 && j < n2 && k < n3) {
        comps++;
        if (L[i] <= M[j]) {
            comps++;
            if (L[i] <= R[k]) arr[idx++] = L[i++];
            else arr[idx++] = R[k++];
        } else {
            comps++;
            if (M[j] <= R[k]) arr[idx++] = M[j++];
            else arr[idx++] = R[k++];
        }
    }

    // Pairwise remaining merges
    while (i < n1 && j < n2) {
        comps++;
        if (L[i] <= M[j]) arr[idx++] = L[i++];
        else arr[idx++] = M[j++];
    }
    while (j < n2 && k < n3) {
        comps++;
        if (M[j] <= R[k]) arr[idx++] = M[j++];
        else arr[idx++] = R[k++];
    }
    while (i < n1 && k < n3) {
        comps++;
        if (L[i] <= R[k]) arr[idx++] = L[i++];
        else arr[idx++] = R[k++];
    }

    // Leftovers
    while (i < n1) arr[idx++] = L[i++];
    while (j < n2) arr[idx++] = M[j++];
    while (k < n3) arr[idx++] = R[k++];

    free(L);
    free(M);
    free(R);
    return comps;
}

long long merge_sort_3way(int arr[], int l, int r) {
    long long comps = 0;
    if (l < r) {
        int len = r - l + 1;
        if (len == 2) {
            comps++;
            if (arr[l] > arr[r]) {
                int temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
            }
            return comps;
        }

        int m1 = l + len / 3 - 1;
        int m2 = l + 2 * (len / 3) - 1;

        comps += merge_sort_3way(arr, l, m1);
        comps += merge_sort_3way(arr, m1 + 1, m2);
        comps += merge_sort_3way(arr, m2 + 1, r);
        comps += merge_3way(arr, l, m1, m2, r);
    }
    return comps;
}

int main() {
    // Silence Raylib logs
    SetTraceLogLevel(LOG_NONE);
    srand((unsigned int)time(NULL));

    long long comp_2way[MAX_N + 1] = {0};
    long long comp_3way[MAX_N + 1] = {0};

    // Benchmark algorithms
    for (int n = START_N; n <= MAX_N; n += STEP) {
        int* a1 = (int*)malloc(n * sizeof(int));
        int* a2 = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int val = rand() % 10000;
            a1[i] = val;
            a2[i] = val;
        }

        comp_2way[n] = merge_sort_2way(a1, 0, n - 1);
        comp_3way[n] = merge_sort_3way(a2, 0, n - 1);

        free(a1);
        free(a2);
    }

    // Raylib Window
    InitWindow(1150, 700, "DAA Lab Q2 - Merge Sort vs. Modified 3-Way Merge Sort");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- Left Side: Theoretical Proof Panel ---
        DrawText("Theoretical Analysis", 25, 20, 20, DARKBLUE);
        
        int startX = 20;
        int startY = 55;
        int lh = 22;

        DrawText("1. Recurrence Relation:", startX, startY, 15, BLACK);
        DrawText("   T(n) = 3 T(n/3) + O(n)", startX, startY + lh, 14, MAROON);

        DrawText("2. Master Theorem Solution:", startX, startY + 2 * lh + 5, 15, BLACK);
        DrawText("   a = 3,  b = 3,  f(n) = O(n)", startX, startY + 3 * lh + 5, 14, DARKGRAY);
        DrawText("   n^(log_b a) = n^(log_3 3) = n^1 = n", startX, startY + 4 * lh + 5, 14, DARKGRAY);
        DrawText("   Since f(n) = Theta(n^(log_b a)), Case 2 applies:", startX, startY + 5 * lh + 5, 13, DARKGRAY);
        
        DrawText("   T(n) = Theta(n log_3 n) = Theta(n log n)", startX, startY + 6 * lh + 10, 14, DARKBLUE);

        DrawText("3. Constant Factor Insight:", startX, startY + 8 * lh, 15, BLACK);
        DrawText("   * Both algorithms are O(n log n).", startX, startY + 9 * lh, 13, DARKGRAY);
        DrawText("   * 3-Way Merge needs up to 2 comps", startX, startY + 10 * lh, 13, DARKGRAY);
        DrawText("     per placed element (vs 1 in 2-way).", startX, startY + 11 * lh, 13, DARKGRAY);
        DrawText("   * Thus, 3-Way has a higher slope.", startX, startY + 12 * lh, 13, RED);

        DrawRectangleLines(15, 45, 430, 310, LIGHTGRAY);

        // --- Right Side: Plot ---
        DrawText("Order of Growth Plot", 480, 20, 20, DARKBLUE);
        DrawText("Blue: Standard 2-Way Merge [O(n log n)]", 480, 50, 14, BLUE);
        DrawText("Red: Modified 3-Way Merge [O(n log n)]", 800, 50, 14, RED);

        int originX = 520;
        int originY = 640;
        int graphWidth = 580;
        int graphHeight = 540;

        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("N (Array Size)", originX + graphWidth / 2 - 40, originY + 25, 14, BLACK);
        DrawText("Comparisons", originX - 35, originY - graphHeight - 20, 14, BLACK);

        float xScale = (float)graphWidth / (MAX_N - START_N);
        float maxComps = (float)comp_3way[MAX_N];
        float yScale = (float)graphHeight / maxComps;

        for (int n = START_N; n <= MAX_N; n += STEP) {
            int x = originX + (int)((n - START_N) * xScale);

            int y_2way = originY - (int)(comp_2way[n] * yScale);
            int y_3way = originY - (int)(comp_3way[n] * yScale);

            DrawCircle(x, y_2way, 4, BLUE);
            DrawCircle(x, y_3way, 4, RED);

            if (n > START_N) {
                int prev_n = n - STEP;
                int prev_x = originX + (int)((prev_n - START_N) * xScale);

                int prev_y_2way = originY - (int)(comp_2way[prev_n] * yScale);
                int prev_y_3way = originY - (int)(comp_3way[prev_n] * yScale);

                DrawLine(prev_x, prev_y_2way, x, y_2way, BLUE);
                DrawLine(prev_x, prev_y_3way, x, y_3way, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}