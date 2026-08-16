#include <stdio.h>
#include <stdlib.h>

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
        }
    }
}

void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void print_matrix(const char* name, int** mat, int n) {
    printf("%s (%dx%d):\n", name, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int** A11 = allocate_matrix(k);
    int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k);
    int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k);
    int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k);
    int** B22 = allocate_matrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    int** P1 = allocate_matrix(k);
    int** P2 = allocate_matrix(k);
    int** P3 = allocate_matrix(k);
    int** P4 = allocate_matrix(k);
    int** P5 = allocate_matrix(k);
    int** P6 = allocate_matrix(k);
    int** P7 = allocate_matrix(k);

    int** T1 = allocate_matrix(k);
    int** T2 = allocate_matrix(k);

    add_matrix(A11, A22, T1, k);
    add_matrix(B11, B22, T2, k);
    strassen(T1, T2, P1, k);

    add_matrix(A21, A22, T1, k);
    strassen(T1, B11, P2, k);

    sub_matrix(B12, B22, T2, k);
    strassen(A11, T2, P3, k);

    sub_matrix(B21, B11, T2, k);
    strassen(A22, T2, P4, k);

    add_matrix(A11, A12, T1, k);
    strassen(T1, B22, P5, k);

    sub_matrix(A21, A11, T1, k);
    add_matrix(B11, B12, T2, k);
    strassen(T1, T2, P6, k);

    sub_matrix(A12, A22, T1, k);
    add_matrix(B21, B22, T2, k);
    strassen(T1, T2, P7, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C[i][j + k]     = P3[i][j] + P5[i][j];
            C[i + k][j]     = P2[i][j] + P4[i][j];
            C[i + k][j + k] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(P1, k);  free_matrix(P2, k);  free_matrix(P3, k);  free_matrix(P4, k);
    free_matrix(P5, k);  free_matrix(P6, k);  free_matrix(P7, k);
    free_matrix(T1, k);  free_matrix(T2, k);
}

void run_test(const char* test_name, int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    strassen(A, B, C, n);

    printf("%s\n", test_name);
    print_matrix("Matrix A", A, n);
    print_matrix("Matrix B", B, n);
    print_matrix("Result Matrix C (Strassen)", C, n);
    printf("------------------------------------------------\n\n");

    free_matrix(C, n);
}

int main() {
    int n1 = 2;
    int** A1 = allocate_matrix(n1);
    int** B1 = allocate_matrix(n1);

    A1[0][0] = 1; A1[0][1] = 2;
    A1[1][0] = 3; A1[1][1] = 4;

    B1[0][0] = 5; B1[0][1] = 6;
    B1[1][0] = 7; B1[1][1] = 8;

    run_test("Test 1 (2x2 Matrix Multiplication)", A1, B1, n1);
    free_matrix(A1, n1);
    free_matrix(B1, n1);

    int n2 = 4;
    int** A2 = allocate_matrix(n2);
    int** B2 = allocate_matrix(n2);

    int valA = 1, valB = 16;
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            A2[i][j] = valA++;
            B2[i][j] = (i == j) ? 1 : 0;
        }
    }

    run_test("Test 2 (4x4 Matrix Multiplication with Identity Matrix)", A2, B2, n2);
    free_matrix(A2, n2);
    free_matrix(B2, n2);

    return 0;
}