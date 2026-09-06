#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*

1. Problem Definition:
   Given vectors A of size m and B of size n (where n >= m), the discrete convolution
   vector C has length L = m + n - 1, defined by:
   C[k] = sum_{j=0}^{m-1} A[j] * B[k - j]  for 0 <= k < m + n - 1
   (assuming out-of-bounds indices evaluate to 0).

2. Divide and Conquer via Fast Fourier Transform (Cooley-Tukey FFT):
   - Direct standard convolution computes every term in O(m * n) = O(n^2) operations.
   - Using the Convolution Theorem, convolution in the time domain is equivalent to
     pointwise multiplication in the frequency domain:
     C = IFFT( FFT(A) .* FFT(B) )
   - The FFT computes the Discrete Fourier Transform (DFT) using a divide-and-conquer strategy:
     A(x) = A_even(x^2) + x * A_odd(x^2)
     Evaluating at the complex n-th roots of unity w_N^k reduces a problem of size N
     to two subproblems of size N/2:
     T(N) = 2 * T(N/2) + O(N)
     By the Master Theorem (Case 2), T(N) = O(N log N).

3. Algorithm Procedure:
   - Determine padding size N: smallest power of 2 such that N >= m + n - 1.
     Since n >= m, N < 4n, so N = O(n).
   - Zero-pad arrays A and B to length N as complex sequences.
   - Compute forward FFT of padded A and B in O(N log N) = O(n log n) time.
   - Compute pointwise product: for each k from 0 to N-1, C_freq[k] = A_freq[k] * B_freq[k] in O(N) time.
   - Compute Inverse FFT (IFFT) of C_freq in O(N log N) = O(n log n) time.
   - Extract the real parts of the first (m + n - 1) terms as the resulting vector C.

4. Complexity Analysis:
   - Time Complexity:
       * Zero-padding: O(N) = O(n)
       * Forward FFT of A: O(N log N) = O(n log n)
       * Forward FFT of B: O(N log N) = O(n log n)
       * Pointwise vector multiplication: O(N) = O(n)
       * Inverse FFT: O(N log N) = O(n log n)
       * Overall Worst-case Time Complexity: O(n log n)
   - Space Complexity:
       * O(N) = O(n) auxiliary space for padded complex buffers.
*/

#define PI 3.141

typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_add(Complex a, Complex b) {
    Complex res = {a.real + b.real, a.imag + b.imag};
    return res;
}

Complex complex_sub(Complex a, Complex b) {
    Complex res = {a.real - b.real, a.imag - b.imag};
    return res;
}

Complex complex_mul(Complex a, Complex b) {
    Complex res = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return res;
}

void fft(Complex *a, int n, int invert) {
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            Complex temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen = {cos(angle), sin(angle)};

        for (int i = 0; i < n; i += len) {
            Complex w = {1.0, 0.0};
            for (int j = 0; j < len / 2; j++) {
                Complex u = a[i + j];
                Complex v = complex_mul(a[i + j + len / 2], w);
                a[i + j] = complex_add(u, v);
                a[i + j + len / 2] = complex_sub(u, v);
                w = complex_mul(w, wlen);
            }
        }
    }

    if (invert) {
        for (int i = 0; i < n; i++) {
            a[i].real /= n;
            a[i].imag /= n;
        }
    }
}

int next_power_of_two(int x) {
    int power = 1;
    while (power < x) {
        power <<= 1;
    }
    return power;
}

double* convolve(const double *A, int m, const double *B, int n, int *out_len) {
    *out_len = m + n - 1;
    int N = next_power_of_two(*out_len);

    Complex *fa = (Complex *)calloc(N, sizeof(Complex));
    Complex *fb = (Complex *)calloc(N, sizeof(Complex));

    for (int i = 0; i < m; i++) {
        fa[i].real = A[i];
    }
    for (int i = 0; i < n; i++) {
        fb[i].real = B[i];
    }

    fft(fa, N, 0);
    fft(fb, N, 0);

    for (int i = 0; i < N; i++) {
        fa[i] = complex_mul(fa[i], fb[i]);
    }

    fft(fa, N, 1);

    double *C = (double *)malloc((*out_len) * sizeof(double));
    for (int i = 0; i < *out_len; i++) {
        C[i] = fa[i].real;
    }

    free(fa);
    free(fb);
    return C;
}

int main() {
    int m, n;
    printf("Enter size of vector A (m): ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        return 1;
    }

    printf("Enter size of vector B (n, with n >= m): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    if (m > n) {
        printf("Note: As per specification n >= m, swapping m and n.\n");
        int temp = m;
        m = n;
        n = temp;
    }

    double *A = (double *)malloc(m * sizeof(double));
    double *B = (double *)malloc(n * sizeof(double));

    printf("Enter %d elements of vector A:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%lf", &A[i]);
    }

    printf("Enter %d elements of vector B:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &B[i]);
    }

    int out_len = 0;
    double *C = convolve(A, m, B, n, &out_len);

    printf("\nConvolution Result C (length %d):\n[ ", out_len);
    for (int i = 0; i < out_len; i++) {
        printf("%.4lf%s", C[i], (i == out_len - 1) ? "" : ", ");
    }
    printf(" ]\n");

    free(A);
    free(B);
    free(C);
    return 0;
}