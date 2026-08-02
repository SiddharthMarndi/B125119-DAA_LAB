#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define MAX_DISCS 15

long long move_count = 0;

void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod, bool print_steps) {
    if (n == 0) return;
    
    tower_of_hanoi(n - 1, from_rod, aux_rod, to_rod, print_steps);
    
    move_count++;
    if (print_steps) {
        printf("Move disc %d from %c -> %c\n", n, from_rod, to_rod);
    }
    
    tower_of_hanoi(n - 1, aux_rod, to_rod, from_rod, print_steps);
}

int main() {
    printf("--- Towers of Hanoi Step-by-Step Simulation (n = 3) ---\n");
    move_count = 0;
    tower_of_hanoi(3, 'A', 'C', 'B', true);
    printf("Total moves for n=3: %lld\n\n", move_count);

    long long moves[MAX_DISCS + 1];
    for (int n = 1; n <= MAX_DISCS; n++) {
        move_count = 0;
        tower_of_hanoi(n, 'A', 'C', 'B', false);
        moves[n] = move_count;
    }

    InitWindow(900, 600, "DAA Lab - Towers of Hanoi Moves Plot");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Towers of Hanoi: Total Moves vs Discs (n)", 220, 20, 22, DARKBLUE);
        DrawText("Theoretical & Simulated: T(n) = 2^n - 1", 280, 50, 16, DARKGREEN);

        DrawLine(80, 520, 850, 520, BLACK);
        DrawLine(80, 80, 80, 520, BLACK);

        DrawText("Number of Discs (n)", 400, 550, 16, BLACK);
        DrawText("Moves", 15, 280, 16, BLACK);

        for (int n = 1; n <= MAX_DISCS; n++) {
            int x = 80 + (n - 1) * 52;
            
            int y = 520 - (int)((moves[n] / 32767.0) * 400.0);

            DrawCircle(x, y, 5, RED);

            if (n > 1) {
                int prev_x = 80 + (n - 2) * 52;
                int prev_y = 520 - (int)((moves[n - 1] / 32767.0) * 400.0);
                DrawLine(prev_x, prev_y, x, y, RED);
            }

            DrawText(TextFormat("%d", n), x - 4, 530, 12, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}