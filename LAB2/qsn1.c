#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 500
#define STEP 25
#define START_N 25

// --- Data Structure Definitions ---
typedef struct Node {
    int key;
    struct Node* next;
    struct Node* prev;
} Node;

// --- Benchmark Operations ---

// 1. Unsorted Array Search - Worst-case: O(N)
long long search_unsorted_array(int arr[], int n, int target) {
    long long comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == target) return comparisons;
    }
    return comparisons;
}

// 2. Sorted Array Search (Binary Search) - Worst-case: O(log N)
long long search_sorted_array(int arr[], int n, int target) {
    long long comparisons = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return comparisons;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return comparisons;
}

// 3. Singly Linked List Search - Worst-case: O(N)
long long search_singly_linked_list(Node* head, int target) {
    long long comparisons = 0;
    Node* curr = head;
    while (curr != NULL) {
        comparisons++;
        if (curr->key == target) return comparisons;
        curr = curr->next;
    }
    return comparisons;
}

// Memory Allocation Helpers
Node* create_list(int n) {
    if (n <= 0) return NULL;
    Node* head = (Node*)malloc(sizeof(Node));
    head->key = 0;
    head->next = NULL;
    head->prev = NULL;

    Node* curr = head;
    for (int i = 1; i < n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = i * 2;
        newNode->next = NULL;
        newNode->prev = curr;
        curr->next = newNode;
        curr = newNode;
    }
    return head;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Silence verbose Raylib startup logs
    SetTraceLogLevel(LOG_NONE);
    srand((unsigned int)time(NULL));

    // Data buffers for comparison counts indexed by N
    long long unsorted_arr_comp[MAX_N + 1] = {0};
    long long sorted_arr_comp[MAX_N + 1] = {0};
    long long list_comp[MAX_N + 1] = {0};

    // Benchmark Execution
    for (int n = START_N; n <= MAX_N; n += STEP) {
        int* unsorted_arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) unsorted_arr[i] = rand() % 1000;

        int* sorted_arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) sorted_arr[i] = i * 2;

        Node* list_head = create_list(n);

        int target = -1; // Target not present forces worst-case search

        unsorted_arr_comp[n] = search_unsorted_array(unsorted_arr, n, target);
        sorted_arr_comp[n]   = search_sorted_array(sorted_arr, n, target);
        list_comp[n]         = search_singly_linked_list(list_head, target);

        free(unsorted_arr);
        free(sorted_arr);
        free_list(list_head);
    }

    // Launch Raylib Visualization Window
    InitWindow(1200, 700, "DAA Lab Q1 - Dictionary Operations Complexity & Order of Growth");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // --- Left Side: Complete Theoretical Matrix ---
        DrawText("Theoretical Worst-Case Running Times", 25, 20, 20, DARKBLUE);

        int startX = 25;
        int startY = 60;
        int lh = 28;

        DrawRectangle(15, 50, 560, 610, (Color){245, 245, 250, 255});
        DrawRectangleLines(15, 50, 560, 610, LIGHTGRAY);

        // Table Headers
        DrawText("Data Structure", startX, startY, 13, BLACK);
        DrawText("Srch", startX + 170, startY, 13, BLACK);
        DrawText("Ins", startX + 225, startY, 13, BLACK);
        DrawText("Del*", startX + 275, startY, 13, BLACK);
        DrawText("Max/Min", startX + 325, startY, 13, BLACK);
        DrawText("Pred", startX + 400, startY, 13, BLACK);
        DrawText("Succ", startX + 465, startY, 13, BLACK);

        DrawLine(startX, startY + 22, startX + 535, startY + 22, GRAY);

        // Rows data
        const char* ds_names[] = {
            "Unsorted Array",
            "Sorted Array",
            "Singly List (Unsorted)",
            "Singly List (Sorted)",
            "Doubly List (Unsorted)",
            "Doubly List (Sorted)"
        };

        const char* ops[6][6] = {
            {"O(n)",     "O(1)", "O(1)", "O(n)", "O(n)", "O(n)"},
            {"O(log n)", "O(n)", "O(n)", "O(1)", "O(1)", "O(1)"},
            {"O(n)",     "O(1)", "O(n)", "O(n)", "O(n)", "O(n)"},
            {"O(n)",     "O(n)", "O(n)", "O(1)", "O(n)", "O(1)"},
            {"O(n)",     "O(1)", "O(1)", "O(n)", "O(n)", "O(n)"},
            {"O(n)",     "O(n)", "O(1)", "O(1)", "O(1)", "O(1)"}
        };

        for (int i = 0; i < 6; i++) {
            int y = startY + 32 + i * lh * 2;
            
            // Alternating row background
            if (i % 2 == 1) {
                DrawRectangle(18, y - 5, 554, lh + 10, (Color){235, 238, 245, 255});
            }

            DrawText(ds_names[i], startX, y, 12, DARKBLUE);
            DrawText(ops[i][0], startX + 170, y, 12, MAROON);
            DrawText(ops[i][1], startX + 225, y, 12, DARKGRAY);
            DrawText(ops[i][2], startX + 275, y, 12, DARKGRAY);
            DrawText(ops[i][3], startX + 325, y, 12, DARKGRAY);
            DrawText(ops[i][4], startX + 400, y, 12, DARKGRAY);
            DrawText(ops[i][5], startX + 465, y, 12, DARKGRAY);
        }

        // Table Footnotes
        DrawLine(startX, startY + 410, startX + 535, startY + 410, LIGHTGRAY);
        DrawText("* Delete assumes a direct pointer/index to target node.", startX, startY + 425, 11, DARKGRAY);
        DrawText("* Max/Min in sorted lists assumes head/tail pointers.", startX, startY + 445, 11, DARKGRAY);
        DrawText("* Search in Sorted Array uses Binary Search [O(log n)].", startX, startY + 465, 11, DARKGRAY);

        // --- Right Side: Plot ---
        DrawText("Search: Order of Growth Plot", 610, 20, 20, DARKBLUE);
        DrawText("Red: Unsorted Array / Linked List [O(N)]", 610, 50, 13, RED);
        DrawText("Blue: Sorted Array Binary Search [O(log N)]", 890, 50, 13, BLUE);

        int originX = 640;
        int originY = 620;
        int graphWidth = 520;
        int graphHeight = 520;

        DrawLine(originX, originY, originX + graphWidth, originY, BLACK);
        DrawLine(originX, originY - graphHeight, originX, originY, BLACK);

        DrawText("N (Elements)", originX + graphWidth / 2 - 40, originY + 25, 14, BLACK);
        DrawText("Comparisons", originX - 35, originY - graphHeight - 20, 14, BLACK);

        float xScale = (float)graphWidth / (MAX_N - START_N);
        float yScale = (float)graphHeight / MAX_N;

        for (int n = START_N; n <= MAX_N; n += STEP) {
            int x = originX + (int)((n - START_N) * xScale);

            int y_unsorted = originY - (int)(unsorted_arr_comp[n] * yScale);
            int y_sorted   = originY - (int)(sorted_arr_comp[n] * yScale);

            DrawCircle(x, y_unsorted, 4, RED);
            DrawCircle(x, y_sorted, 4, BLUE);

            if (n > START_N) {
                int prev_n = n - STEP;
                int prev_x = originX + (int)((prev_n - START_N) * xScale);

                int prev_y_unsorted = originY - (int)(unsorted_arr_comp[prev_n] * yScale);
                int prev_y_sorted   = originY - (int)(sorted_arr_comp[prev_n] * yScale);

                DrawLine(prev_x, prev_y_unsorted, x, y_unsorted, RED);
                DrawLine(prev_x, prev_y_sorted, x, y_sorted, BLUE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}