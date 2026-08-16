#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 600
#define STEP 25
#define START_N 25

long long selection_sort(int arr[], int n) {
    long long comps = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
    return comps;
}

int main() {
    SetTraceLogLevel(LOG_NONE);
    srand((unsigned int)time(NULL));

    long long worst_comps[MAX_N + 1] = {0};
    long long best_comps[MAX_N + 1] = {0};
    long long theoretical_comps[MAX_N + 1] = {0};

    for (int n = START_N; n <= MAX_N; n += STEP) {
        int* arr_worst = (int*)malloc(n * sizeof(int));
        int* arr_best = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            arr_worst[i] = n - i;
            arr_best[i] = i + 1;
        }

        worst_comps[n] = selection_sort(arr_worst, n);
        best_comps[n] = selection_sort(arr_best, n);
        theoretical_comps[n] = ((long long)n * (n - 1)) / 2;

        free(arr_worst);
        free(arr_best);
    }

    InitWindow(1220, 740, "DAA Lab 3 Q6 - Selection Sort: Loop Invariants & Complexity Analysis");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Theoretical Proof & Loop Invariant", 25, 16, 19, DARKBLUE);
        DrawRectangle(15, 42, 500, 680, (Color){245, 245, 250, 255});
        DrawRectangleLines(15, 42, 500, 680, LIGHTGRAY);

        int startX = 25, startY = 52, lh = 20;

        DrawText("1. Pseudocode:", startX, startY, 14, BLACK);
        DrawText("   for i = 1 to n - 1:", startX, startY + lh, 12, MAROON);
        DrawText("       min_idx = i", startX, startY + 2 * lh, 12, DARKGRAY);
        DrawText("       for j = i + 1 to n: if A[j] < A[min_idx] min_idx = j", startX, startY + 3 * lh, 12, DARKGRAY);
        DrawText("       swap(A[i], A[min_idx])", startX, startY + 4 * lh, 12, DARKGRAY);

        DrawText("2. Loop Invariant Statement:", startX, startY + 6 * lh, 14, BLACK);
        DrawText("   At the start of outer iteration i, subarray A[1..i-1]", startX, startY + 7 * lh, 12, DARKBLUE);
        DrawText("   contains the (i-1) smallest elements in sorted order,", startX, startY + 8 * lh, 12, DARKBLUE);
        DrawText("   and all elements in A[i..n] >= elements in A[1..i-1].", startX, startY + 9 * lh, 12, DARKBLUE);

        DrawText("3. Correctness Proof (3 Invariant Conditions):", startX, startY + 11 * lh, 14, BLACK);
        DrawText("   * Init: Prior to i=1, A[1..0] is empty => trivially sorted.", startX, startY + 12 * lh, 11, DARKGRAY);
        DrawText("   * Maint: Inner loop finds smallest in A[i..n]. Swapping into", startX, startY + 13 * lh, 11, DARKGRAY);
        DrawText("     A[i] ensures A[1..i] has i smallest sorted elements.", startX, startY + 14 * lh, 11, DARKGRAY);
        DrawText("   * Term: Terminates at i=n. A[1..n-1] is sorted, and the", startX, startY + 15 * lh, 11, DARKGRAY);
        DrawText("     last element A[n] is automatically the largest.", startX, startY + 16 * lh, 11, DARKGRAY);

        DrawText("4. Why Run for Only (n - 1) Elements?", startX, startY + 18 * lh, 14, BLACK);
        DrawText("   When the first n-1 elements are placed in order,", startX, startY + 19 * lh, 12, DARKGRAY);
        DrawText("   the nth element has no other candidate and is already", startX, startY + 20 * lh, 12, DARKGRAY);
        DrawText("   in its final position.", startX, startY + 21 * lh, 12, DARKGRAY);

        DrawText("5. Complexity & Best-Case Analysis:", startX, startY + 23 * lh, 14, BLACK);
        DrawText("   * Total Comparisons: Sum_{i=1}^{n-1} (n - i) = n(n-1)/2", startX, startY + 24 * lh, 12, MAROON);
        DrawText("   * Worst-Case Time: Theta(n^2)", startX, startY + 25 * lh, 13, RED);
        DrawText("   * Is Best-Case better? NO.", startX, startY + 26 * lh, 13, RED);
        DrawText("     Inner loop ALWAYS performs n(n-1)/2 comparisons", startX, startY + 27 * lh, 12, DARKGRAY);
        DrawText("     regardless of initial array order => Best Case = Theta(n^2).", startX, startY + 28 * lh, 12, DARKGRAY);

        DrawText("Order of Growth Plot [Theta(n^2) Validation]", 545, 16, 19, DARKBLUE);
        DrawText("Red: Reverse Sorted (Worst Case)", 545, 45, 12, RED);
        DrawText("Blue: Already Sorted (Best Case)", 775, 45, 12, BLUE);
        DrawText("Black (Dotted): n(n-1)/2 Bound", 1000, 45, 12, BLACK);

        int originX = 575, originY = 660, graphWidth = 600, graphHeight = 580;
        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("N (Array Size)", originX + graphWidth / 2 - 40, originY + 25, 14, BLACK);
        DrawText("Comparisons", originX - 45, originY - graphHeight - 20, 14, BLACK);

        float maxComps = (float)theoretical_comps[MAX_N];
        float xScale = (float)graphWidth / (MAX_N - START_N);
        float yScale = (float)graphHeight / maxComps;

        for (int n = START_N; n <= MAX_N; n += STEP) {
            int x = originX + (int)((n - START_N) * xScale);
            int y_worst = originY - (int)(worst_comps[n] * yScale);
            int y_best = originY - (int)(best_comps[n] * yScale);
            int y_theo = originY - (int)(theoretical_comps[n] * yScale);

            DrawCircle(x, y_worst, 4, RED);
            DrawCircle(x, y_best, 3, BLUE);

            if (n % 100 == 0) {
                DrawText(TextFormat("n=%d", n), x - 15, originY + 8, 10, DARKGRAY);
            }

            if (n > START_N) {
                int prev_n = n - STEP;
                int prev_x = originX + (int)((prev_n - START_N) * xScale);
                int prev_y_worst = originY - (int)(worst_comps[prev_n] * yScale);
                int prev_y_best = originY - (int)(best_comps[prev_n] * yScale);
                int prev_y_theo = originY - (int)(theoretical_comps[prev_n] * yScale);

                DrawLine(prev_x, prev_y_worst, x, y_worst, RED);
                DrawLine(prev_x, prev_y_best, x, y_best, BLUE);
                DrawLine(prev_x, prev_y_theo, x, y_theo, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}