#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 600
#define STEP 25
#define START_N 25

typedef struct {
    int min;
    int max;
} MinMax;

MinMax find_min_max(const int arr[], int low, int high, int* comps) {
    MinMax result, left, right;

    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    if (high == low + 1) {
        (*comps)++;
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    int mid = low + (high - low) / 2;
    left = find_min_max(arr, low, mid, comps);
    right = find_min_max(arr, mid + 1, high, comps);

    (*comps)++;
    if (left.max > right.max) {
        result.max = left.max;
    } else {
        result.max = right.max;
    }

    (*comps)++;
    if (left.min < right.min) {
        result.min = left.min;
    } else {
        result.min = right.min;
    }

    return result;
}

int main() {
    SetTraceLogLevel(LOG_NONE);
    srand((unsigned int)time(NULL));

    int actual_comps[MAX_N + 1] = {0};
    int bound_comps[MAX_N + 1] = {0};

    for (int n = START_N; n <= MAX_N; n += STEP) {
        int* arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

        int comps = 0;
        find_min_max(arr, 0, n - 1, &comps);
        actual_comps[n] = comps;
        bound_comps[n] = (3 * n) / 2;

        free(arr);
    }

    InitWindow(1150, 700, "DAA Lab 3 Q3 - D&C Min-Max Comparisons Bound");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Theoretical Analysis", 25, 20, 20, DARKBLUE);
        DrawRectangle(15, 50, 440, 620, (Color){245, 245, 250, 255});
        DrawRectangleLines(15, 50, 440, 620, LIGHTGRAY);

        int startX = 25, startY = 65, lh = 24;

        DrawText("1. Recurrence Relation:", startX, startY, 15, BLACK);
        DrawText("   T(n) = 2 * T(n/2) + 2", startX, startY + lh, 14, MAROON);
        DrawText("   Base Cases:", startX, startY + 2 * lh, 13, DARKGRAY);
        DrawText("   T(1) = 0 comparisons", startX, startY + 3 * lh, 13, DARKGRAY);
        DrawText("   T(2) = 1 comparison", startX, startY + 4 * lh, 13, DARKGRAY);

        DrawText("2. Exact Solution (for n = 2^k):", startX, startY + 6 * lh, 15, BLACK);
        DrawText("   T(n) = (3n / 2) - 2", startX, startY + 7 * lh, 14, DARKBLUE);

        DrawText("3. Bound Validation:", startX, startY + 9 * lh, 15, BLACK);
        DrawText("   * Naive Linear Scan: 2n - 2 comps", startX, startY + 10 * lh, 13, DARKGRAY);
        DrawText("   * D&C Approach: <= 3n / 2 comps", startX, startY + 11 * lh, 13, DARKGRAY);
        DrawText("   * Achieves ~25% reduction in comps.", startX, startY + 12 * lh, 13, RED);

        DrawText("Worst-Case Comparisons Plot", 490, 20, 20, DARKBLUE);
        DrawText("Red: Upper Bound [3n / 2]", 490, 50, 14, RED);
        DrawText("Blue: D&C Actual Comps [3n/2 - 2]", 780, 50, 14, BLUE);

        int originX = 530, originY = 620, graphWidth = 560, graphHeight = 520;
        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("N (Array Size)", originX + graphWidth / 2 - 40, originY + 25, 14, BLACK);
        DrawText("Comparisons", originX - 35, originY - graphHeight - 20, 14, BLACK);

        float xScale = (float)graphWidth / (MAX_N - START_N);
        float maxY = (float)bound_comps[MAX_N] + 20;
        float yScale = (float)graphHeight / maxY;

        for (int n = START_N; n <= MAX_N; n += STEP) {
            int x = originX + (int)((n - START_N) * xScale);
            int y_bound = originY - (int)(bound_comps[n] * yScale);
            int y_act = originY - (int)(actual_comps[n] * yScale);

            DrawCircle(x, y_bound, 4, RED);
            DrawCircle(x, y_act, 4, BLUE);

            if (n > START_N) {
                int prev_n = n - STEP;
                int prev_x = originX + (int)((prev_n - START_N) * xScale);
                int prev_y_bound = originY - (int)(bound_comps[prev_n] * yScale);
                int prev_y_act = originY - (int)(actual_comps[prev_n] * yScale);

                DrawLine(prev_x, prev_y_bound, x, y_bound, RED);
                DrawLine(prev_x, prev_y_act, x, y_act, BLUE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}