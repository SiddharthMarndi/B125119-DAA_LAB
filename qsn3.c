#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_N 50

long long bubble_sort_standard(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

long long bubble_sort_optimized(int arr[], int n) {
    long long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return comparisons;
}

int main() {
    srand(time(NULL));

    long long std_comp[MAX_N + 1];
    long long opt_comp[MAX_N + 1];

    for (int n = 5; n <= MAX_N; n++) {
        int a1[MAX_N], a2[MAX_N];
        for (int i = 0; i < n; i++) {
            int val = rand() % 100;
            a1[i] = val;
            a2[i] = val;
        }

        std_comp[n] = bubble_sort_standard(a1, n);
        opt_comp[n] = bubble_sort_optimized(a2, n);
    }

    InitWindow(900, 600, "DAA Lab - Bubble Sort Performance Comparison");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Bubble Sort Performance Analysis", 250, 20, 22, DARKBLUE);
        DrawText("Red: Standard (Completes n-1 passes)", 50, 60, 16, RED);
        DrawText("Green: Optimized (Early termination)", 450, 60, 16, DARKGREEN);

        DrawLine(80, 520, 850, 520, BLACK);
        DrawLine(80, 100, 80, 520, BLACK);

        DrawText("N (Array Size)", 420, 550, 16, BLACK);
        DrawText("Comparisons", 10, 280, 16, BLACK);

        for (int n = 5; n <= MAX_N; n += 2) {
            int x = 80 + (n - 5) * 16;
            
            int y_std = 520 - (int)(std_comp[n] * 0.35);
            int y_opt = 520 - (int)(opt_comp[n] * 0.35);

            DrawCircle(x, y_std, 4, RED);
            DrawCircle(x, y_opt, 4, DARKGREEN);

            if (n > 5) {
                int prev_x = 80 + (n - 7) * 16;
                int prev_y_std = 520 - (int)(std_comp[n - 2] * 0.35);
                int prev_y_opt = 520 - (int)(opt_comp[n - 2] * 0.35);

                DrawLine(prev_x, prev_y_std, x, y_std, RED);
                DrawLine(prev_x, prev_y_opt, x, y_opt, DARKGREEN);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}