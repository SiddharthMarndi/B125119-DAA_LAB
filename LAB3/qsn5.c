#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long op_count = 0;

int** allocate_matrix(int n) {
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*)calloc(n, sizeof(int));
    }
    return mat;
}

void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
            op_count++;
        }
    }
}

void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
            op_count++;
        }
    }
}

void multiply_special_pattern(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        op_count++;
        return;
    }

    int k = n / 2;

    int** A1 = allocate_matrix(k);
    int** A2 = allocate_matrix(k);
    int** B1 = allocate_matrix(k);
    int** B2 = allocate_matrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    int** A_sum = allocate_matrix(k);
    int** B_sum = allocate_matrix(k);
    int** A_diff = allocate_matrix(k);
    int** B_diff = allocate_matrix(k);

    add_matrix(A1, A2, A_sum, k);
    add_matrix(B1, B2, B_sum, k);
    sub_matrix(A1, A2, A_diff, k);
    sub_matrix(B1, B2, B_diff, k);

    int** P = allocate_matrix(k);
    int** Q = allocate_matrix(k);

    multiply_special_pattern(A_sum, B_sum, P, k);
    multiply_special_pattern(A_diff, B_diff, Q, k);

    int** C1 = allocate_matrix(k);
    int** C2 = allocate_matrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C1[i][j] = (P[i][j] + Q[i][j]) / 2;
            C2[i][j] = (P[i][j] - Q[i][j]) / 2;
            op_count += 4;
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C1[i][j];
            C[i][j + k]     = C2[i][j];
            C[i + k][j]     = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }

    free_matrix(A1, k); free_matrix(A2, k);
    free_matrix(B1, k); free_matrix(B2, k);
    free_matrix(A_sum, k); free_matrix(B_sum, k);
    free_matrix(A_diff, k); free_matrix(B_diff, k);
    free_matrix(P, k); free_matrix(Q, k);
    free_matrix(C1, k); free_matrix(C2, k);
}

void construct_special_matrix(int** M, int n, int val1, int val2) {
    if (n == 1) {
        M[0][0] = val1;
        return;
    }
    int k = n / 2;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            M[i][j]         = val1;
            M[i][j + k]     = val2;
            M[i + k][j]     = val2;
            M[i + k][j + k] = val1;
        }
    }
}

int main() {
    SetTraceLogLevel(LOG_NONE);

    int sizes[] = {2, 4, 8, 16, 32, 64, 128};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    long long actual_ops[7] = {0};
    long long bound_ops[7] = {0};

    for (int idx = 0; idx < num_sizes; idx++) {
        int n = sizes[idx];
        int** A = allocate_matrix(n);
        int** B = allocate_matrix(n);
        int** C = allocate_matrix(n);

        construct_special_matrix(A, n, 2, 1);
        construct_special_matrix(B, n, 3, 4);

        op_count = 0;
        multiply_special_pattern(A, B, C, n);
        actual_ops[idx] = op_count;
        bound_ops[idx] = (long long)n * n * 5;

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    InitWindow(1180, 720, "DAA Lab 3 Q5 - Special-Pattern Matrix Multiplication [O(n^2)]");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Theoretical Formulation & Proof", 25, 18, 19, DARKBLUE);
        DrawRectangle(15, 45, 470, 655, (Color){245, 245, 250, 255});
        DrawRectangleLines(15, 45, 470, 655, LIGHTGRAY);

        int startX = 25, startY = 55, lh = 21;

        DrawText("1. Recursive Block Structure:", startX, startY, 14, BLACK);
        DrawText("   M = [ M1  M2 ]", startX, startY + lh, 13, MAROON);
        DrawText("       [ M2  M1 ]", startX, startY + 2 * lh, 13, MAROON);

        DrawText("2. Product Equations:", startX, startY + 3 * lh + 5, 14, BLACK);
        DrawText("   C1 = M1*N1 + M2*N2", startX, startY + 4 * lh + 5, 12, DARKGRAY);
        DrawText("   C2 = M1*N2 + M2*N1", startX, startY + 5 * lh + 5, 12, DARKGRAY);

        DrawText("3. D&C Optimization (2 Mults instead of 4):", startX, startY + 7 * lh, 14, BLACK);
        DrawText("   P = (M1 + M2)(N1 + N2) = C1 + C2", startX, startY + 8 * lh, 12, DARKBLUE);
        DrawText("   Q = (M1 - M2)(N1 - N2) = C1 - C2", startX, startY + 9 * lh, 12, DARKBLUE);
        DrawText("   => C1 = (P + Q) / 2", startX, startY + 10 * lh + 2, 12, MAROON);
        DrawText("   => C2 = (P - Q) / 2", startX, startY + 11 * lh + 2, 12, MAROON);

        DrawText("4. Recurrence Relation:", startX, startY + 13 * lh, 14, BLACK);
        DrawText("   T(n) = 2 * T(n/2) + c * n^2", startX, startY + 14 * lh, 13, RED);

        DrawText("5. Master Theorem Derivation:", startX, startY + 16 * lh, 14, BLACK);
        DrawText("   a = 2,  b = 2,  f(n) = Theta(n^2)", startX, startY + 17 * lh, 12, DARKGRAY);
        DrawText("   n^(log_b a) = n^(log_2 2) = n^1", startX, startY + 18 * lh, 12, DARKGRAY);
        DrawText("   Since f(n) = Omega(n^(1 + eps)) with eps = 1:", startX, startY + 19 * lh, 12, DARKGRAY);
        DrawText("   T(n) = Theta(f(n)) = Theta(n^2)", startX, startY + 20 * lh + 3, 14, DARKBLUE);

        DrawText("6. Complexity Verdict:", startX, startY + 22 * lh + 5, 14, BLACK);
        DrawText("   * Standard Strassen: O(n^2.81)", startX, startY + 23 * lh + 5, 12, DARKGRAY);
        DrawText("   * Special Symmetric D&C: O(n^2)", startX, startY + 24 * lh + 5, 13, RED);
        DrawText("   * Optimal quadratic complexity achieved.", startX, startY + 25 * lh + 5, 12, DARKBLUE);

        DrawText("Order of Growth Plot [O(n^2) Validation]", 520, 18, 19, DARKBLUE);
        DrawText("Blue: D&C Actual Operations", 520, 48, 13, BLUE);
        DrawText("Red: Reference Theoretical O(n^2)", 830, 48, 13, RED);

        int originX = 550, originY = 640, graphWidth = 590, graphHeight = 550;
        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("Matrix Dimension (n = 2^k)", originX + graphWidth / 2 - 80, originY + 25, 14, BLACK);
        DrawText("Operations", originX - 45, originY - graphHeight - 20, 14, BLACK);

        float maxOperations = (float)bound_ops[num_sizes - 1];
        float xScale = (float)graphWidth / (sizes[num_sizes - 1] - sizes[0]);
        float yScale = (float)graphHeight / maxOperations;

        for (int i = 0; i < num_sizes; i++) {
            int x = originX + (int)((sizes[i] - sizes[0]) * xScale);
            int y_act = originY - (int)(actual_ops[i] * yScale);
            int y_bound = originY - (int)(bound_ops[i] * yScale);

            DrawCircle(x, y_act, 4, BLUE);
            DrawCircle(x, y_bound, 4, RED);

            DrawText(TextFormat("n=%d", sizes[i]), x - 12, originY + 8, 10, DARKGRAY);

            if (i > 0) {
                int prev_x = originX + (int)((sizes[i - 1] - sizes[0]) * xScale);
                int prev_y_act = originY - (int)(actual_ops[i - 1] * yScale);
                int prev_y_bound = originY - (int)(bound_ops[i - 1] * yScale);

                DrawLine(prev_x, prev_y_act, x, y_act, BLUE);
                DrawLine(prev_x, prev_y_bound, x, y_bound, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}