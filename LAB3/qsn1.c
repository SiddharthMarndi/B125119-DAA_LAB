#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 1000
#define STEP 50
#define START_N 50

long long binary_search(const int arr[], int n, int target) {
    long long comps = 0;
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        comps++;
        if (arr[mid] == target) return comps;

        comps++;
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return comps;
}

long long ternary_search(const int arr[], int n, int target) {
    long long comps = 0;
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        comps++;
        if (arr[mid1] == target) return comps;

        comps++;
        if (arr[mid2] == target) return comps;

        comps++;
        if (target < arr[mid1]) {
            high = mid1 - 1;
        } else {
            comps++;
            if (target > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return comps;
}

int main() {
    SetTraceLogLevel(LOG_NONE);

    long long bin_comps[MAX_N + 1] = {0};
    long long ter_comps[MAX_N + 1] = {0};

    for (int n = START_N; n <= MAX_N; n += STEP) {
        int* arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            arr[i] = i * 2;
        }

        int target = -1; 

        bin_comps[n] = binary_search(arr, n, target);
        ter_comps[n] = ternary_search(arr, n, target);

        free(arr);
    }

    InitWindow(1150, 700, "DAA Lab 3 Q1 - Binary Search vs. Ternary Search");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Theoretical Justification", 25, 20, 20, DARKBLUE);
        DrawRectangle(15, 50, 440, 620, (Color){245, 245, 250, 255});
        DrawRectangleLines(15, 50, 440, 620, LIGHTGRAY);

        int startX = 25, startY = 65, lh = 22;

        DrawText("1. Binary Search:", startX, startY, 15, BLACK);
        DrawText("   * Splits array into 2 halves.", startX, startY + lh, 13, DARKGRAY);
        DrawText("   * Max comparisons / iteration = 2", startX, startY + 2 * lh, 13, DARKGRAY);
        DrawText("   * Total iterations = log2(N)", startX, startY + 3 * lh, 13, DARKGRAY);
        DrawText("   * Worst-case comps: 2 * log2(N)", startX, startY + 4 * lh, 14, BLUE);
        DrawText("     = 2 * (ln N / ln 2) ~ 2.885 * ln(N)", startX, startY + 5 * lh, 13, DARKBLUE);

        DrawText("2. Ternary Search:", startX, startY + 7 * lh, 15, BLACK);
        DrawText("   * Splits array into 3 intervals.", startX, startY + 8 * lh, 13, DARKGRAY);
        DrawText("   * Max comparisons / iteration = 4", startX, startY + 9 * lh, 13, DARKGRAY);
        DrawText("   * Total iterations = log3(N)", startX, startY + 10 * lh, 13, DARKGRAY);
        DrawText("   * Worst-case comps: 4 * log3(N)", startX, startY + 11 * lh, 14, RED);
        DrawText("     = 4 * (ln N / ln 3) ~ 3.641 * ln(N)", startX, startY + 12 * lh, 13, MAROON);

        DrawText("3. Core Conclusion:", startX, startY + 14 * lh, 15, BLACK);
        DrawText("   * 3.641 * ln(N) > 2.885 * ln(N)", startX, startY + 15 * lh, 14, BLACK);
        DrawText("   * Ternary Search performs ~26% MORE", startX, startY + 16 * lh, 13, RED);
        DrawText("     comparisons than Binary Search.", startX, startY + 17 * lh, 13, RED);
        DrawText("   * Hence, Binary Search is strictly better", startX, startY + 18 * lh, 14, DARKBLUE);
        DrawText("     for searching sorted arrays in memory.", startX, startY + 19 * lh, 13, DARKBLUE);

        DrawText("Worst-Case Comparisons Plot", 490, 20, 20, DARKBLUE);
        DrawText("Blue: Binary Search [2 * log2(N)]", 490, 50, 14, BLUE);
        DrawText("Red: Ternary Search [4 * log3(N)]", 820, 50, 14, RED);

        int originX = 530, originY = 620, graphWidth = 560, graphHeight = 520;
        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("N (Array Size)", originX + graphWidth / 2 - 40, originY + 25, 14, BLACK);
        DrawText("Comparisons", originX - 35, originY - graphHeight - 20, 14, BLACK);

        float xScale = (float)graphWidth / (MAX_N - START_N);
        float maxComps = (float)ter_comps[MAX_N] + 5;
        float yScale = (float)graphHeight / maxComps;

        for (int n = START_N; n <= MAX_N; n += STEP) {
            int x = originX + (int)((n - START_N) * xScale);

            int y_bin = originY - (int)(bin_comps[n] * yScale);
            int y_ter = originY - (int)(ter_comps[n] * yScale);

            DrawCircle(x, y_bin, 4, BLUE);
            DrawCircle(x, y_ter, 4, RED);

            if (n > START_N) {
                int prev_n = n - STEP;
                int prev_x = originX + (int)((prev_n - START_N) * xScale);

                int prev_y_bin = originY - (int)(bin_comps[prev_n] * yScale);
                int prev_y_ter = originY - (int)(ter_comps[prev_n] * yScale);

                DrawLine(prev_x, prev_y_bin, x, y_bin, BLUE);
                DrawLine(prev_x, prev_y_ter, x, y_ter, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
