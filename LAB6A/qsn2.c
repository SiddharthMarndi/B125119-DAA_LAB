#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*

(i) Matrix Addition:[cite: 1]
    - Worst-case Time Complexity: O(n^2)[cite: 1]
    - Theoretical derivation: Two n x n matrices have n * n = n^2 total entries. 
      Addition requires computing C[i][j] = A[i][j] + B[i][j] for each entry.
      This takes exactly n^2 scalar additions, yielding Theta(n^2).
    - Space Complexity: O(n^2) to store the resulting matrix C, or O(1) auxiliary if done in place.

(ii) Matrix Multiplication:[cite: 1]
    - Worst-case Time Complexity:
        * Standard algorithm: O(n^3)[cite: 1]
        * Strassen's Divide and Conquer: O(n^2.807)
        * Theoretical Coppersmith-Winograd / modern variants: ~O(n^2.37)
    - Theoretical derivation: Standard matrix multiplication computes each entry C[i][j] as the dot 
      product of row i of A and column j of B: sum_{k=0}^{n-1} A[i][k] * B[k][j].
      Each entry requires n multiplications and (n - 1) additions. Across all n^2 entries,
      total scalar operations = n^2 * n = n^3, giving Theta(n^3).
    - Space Complexity: O(n^2) for the result matrix.

(iii) Finding if the given matrix is a zero matrix:[cite: 1]
    - Worst-case Time Complexity: O(n^2)[cite: 1]
    - Theoretical derivation: To confirm a matrix is entirely zero, an algorithm must inspect every 
      element in the worst case (e.g., when the matrix is truly zero or the non-zero element is at the 
      very last index (n-1, n-1)). Best case is O(1) if A[0][0] != 0.
    - Space Complexity: O(1) auxiliary space.

(iv) Finding if the given matrix is a symmetric matrix:[cite: 1]
    - Worst-case Time Complexity: O(n^2)[cite: 1]
    - Theoretical derivation: A matrix is symmetric if A[i][j] == A[j][i] for all 0 <= i < j < n.
      The number of pairs to inspect is n(n - 1)/2. In the worst case (the matrix is symmetric or 
      asymmetry occurs at the last checked pair), it performs n(n - 1)/2 comparisons, which is Theta(n^2).
    - Space Complexity: O(1) auxiliary space.

(v) Computing the determinant of the given matrix:[cite: 1]
    - Worst-case Time Complexity: 
        * O(n^3) using Gaussian Elimination / LU Decomposition.[cite: 1]
        * O(n!) if using recursive cofactor expansion (Laplace expansion).
    - Theoretical derivation: By performing Gaussian elimination with row operations to reduce the matrix 
      to upper triangular form, row i performs O(n - i) work for (n - i) rows below it, which takes 
      sum_{i=1}^{n} (n - i)^2 = O(n^3) arithmetic operations. The determinant is then the product of 
      the diagonal elements in O(n) time. Total time is O(n^3).
    - Space Complexity: O(n^2) to make a working copy so the original matrix is not altered.

(vi) Transposing the matrix in situ (in place):[cite: 1]
    - Worst-case Time Complexity: O(n^2)[cite: 1]
    - Theoretical derivation: In-place transposition requires swapping A[i][j] with A[j][i] for all 
      indices where i < j. The number of strictly upper-triangular elements swapped is n(n - 1)/2. 
      Each swap takes O(1) time and O(1) auxiliary space, yielding Theta(n^2) time and O(1) space.
    - Space Complexity: O(1) auxiliary space.

(vii) Finding the eigenvalue and eigenvector of the matrix:[cite: 1]
    - Worst-case Time Complexity:
        * Dominant Eigenvalue/Eigenvector (Power Iteration): O(k * n^2), where k is iterations to converge.
        * All Eigenvalues/Eigenvectors (QR Algorithm / Jacobi method): O(n^3) per iteration, total O(n^3).
    - Theoretical derivation: In the general case, computing roots of the characteristic polynomial 
      analytically is impossible for n >= 5 (Abel-Ruffini theorem). Standard numerical methods like the 
      QR iteration perform similarity transformations (O(n^3) per step via Householder reflections or 
      Givens rotations) taking O(n^3) overall time. For a single dominant pair, Power Iteration does 
      matrix-vector multiplication taking O(n^2) per step.
    - Space Complexity: O(n^2) auxiliary space for transformation matrices or O(n) for iteration vectors.
*/

double** allocate_matrix(int n) {
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)malloc(n * sizeof(double));
    }
    return mat;
}

void free_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

void read_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }
}

void print_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2lf ", mat[i][j]);
        }
        printf("\n");
    }
}

void copy_matrix(double **src, double **dest, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void matrix_add(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_multiply(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

bool is_zero_matrix(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(A[i][j]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

bool is_symmetric(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[i][j] - A[j][i]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

double compute_determinant(double **A, int n) {
    double **temp = allocate_matrix(n);
    copy_matrix(A, temp, n);

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp[k][i]) > fabs(temp[pivot][i])) {
                pivot = k;
            }
        }

        if (fabs(temp[pivot][i]) < 1e-9) {
            free_matrix(temp, n);
            return 0.0;
        }

        if (pivot != i) {
            double *t = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = t;
            det = -det;
        }

        det *= temp[i][i];

        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i + 1; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }

    free_matrix(temp, n);
    return det;
}

void transpose_in_place(double **A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

void power_iteration(double **A, int n, double *eigenvalue, double *eigenvector, int max_iter) {
    for (int i = 0; i < n; i++) {
        eigenvector[i] = 1.0;
    }

    double lambda_old = 0.0;
    double *y = (double *)malloc(n * sizeof(double));

    for (int iter = 0; iter < max_iter; iter++) {
        for (int i = 0; i < n; i++) {
            y[i] = 0.0;
            for (int j = 0; j < n; j++) {
                y[i] += A[i][j] * eigenvector[j];
            }
        }

        double max_val = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(y[i]) > fabs(max_val)) {
                max_val = y[i];
            }
        }

        if (fabs(max_val) < 1e-9) {
            *eigenvalue = 0.0;
            free(y);
            return;
        }

        for (int i = 0; i < n; i++) {
            eigenvector[i] = y[i] / max_val;
        }

        *eigenvalue = max_val;
        if (fabs(*eigenvalue - lambda_old) < 1e-6) {
            break;
        }
        lambda_old = *eigenvalue;
    }

    free(y);
}

int main() {
    int n;
    printf("Enter matrix dimension n (for n x n matrices): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);
    double **C = allocate_matrix(n);

    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    read_matrix(A, n);

    printf("Enter elements of matrix B (%d x %d):\n", n, n);
    read_matrix(B, n);

    printf("\n(i) Matrix Addition (A + B):\n");
    matrix_add(A, B, C, n);
    print_matrix(C, n);

    printf("\n(ii) Matrix Multiplication (A * B):\n");
    matrix_multiply(A, B, C, n);
    print_matrix(C, n);

    printf("\n(iii) Check Zero Matrix:\n");
    printf("Is A a zero matrix? %s\n", is_zero_matrix(A, n) ? "YES" : "NO");

    printf("\n(iv) Check Symmetric Matrix:\n");
    printf("Is A symmetric? %s\n", is_symmetric(A, n) ? "YES" : "NO");

    printf("\n(v) Determinant of Matrix A:\n");
    printf("det(A) = %.4lf\n", compute_determinant(A, n));

    double **A_copy = allocate_matrix(n);
    copy_matrix(A, A_copy, n);
    transpose_in_place(A_copy, n);
    printf("\n(vi) In-Place Transpose of A:\n");
    print_matrix(A_copy, n);
    free_matrix(A_copy, n);

    double dominant_eigenvalue;
    double *dominant_eigenvector = (double *)malloc(n * sizeof(double));
    power_iteration(A, n, &dominant_eigenvalue, dominant_eigenvector, 1000);
    printf("\n(vii) Dominant Eigenvalue and Eigenvector of A:\n");
    printf("Eigenvalue: %.4lf\n", dominant_eigenvalue);
    printf("Eigenvector: [ ");
    for (int i = 0; i < n; i++) {
        printf("%.4lf%s", dominant_eigenvector[i], (i == n - 1) ? "" : ", ");
    }
    printf(" ]\n");

    free(dominant_eigenvector);
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}