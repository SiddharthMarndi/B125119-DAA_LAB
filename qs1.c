#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char name[30];
    double (*func_ptr)(double);
    double value;
} Function;

double f1(double n)  { return log2(n); }
double f2(double n)  { return 12.0 * sqrt(n); }
double f3(double n)  { return 50.0 * pow(n, 0.5); }
double f4(double n)  { return pow(n, 0.51); }
double f5(double n)  { return pow(2, 32) * n; }
double f6(double n)  { return n * log2(n); }
double f7(double n)  { return pow(n, 2) - 324.0; }
double f8(double n)  { return 100.0 * pow(n, 2) + 6.0 * n; }
double f9(double n)  { return 2.0 * pow(n, 3); }
double f10(double n) { return pow(n, log2(n)); }
double f11(double n) { return pow(3.0, n); }

int compare(const void *a, const void *b) {
    Function *fA = (Function *)a;
    Function *fB = (Function *)b;
    if (fA->value < fB->value) return -1;
    if (fA->value > fB->value) return 1;
    return 0;
}

int main() {
    double n = 100.0;

    Function list[] = {
        {"n * log2(n)",       f6,  0},
        {"12 * sqrt(n)",      f2,  0},
        {"n^(log2(n))",       f10, 0},
        {"100*n^2 + 6*n",     f8,  0},
        {"n^0.51",            f4,  0},
        {"n^2 - 324",         f7,  0},
        {"50 * n^0.5",        f3,  0},
        {"2 * n^3",           f9,  0},
        {"3^n",               f11, 0},
        {"(2^32) * n",        f5,  0},
        {"log2(n)",           f1,  0}
    };
    int total_funcs = sizeof(list) / sizeof(list[0]);

    
    for (int i = 0; i < total_funcs; i++) {
        list[i].value = list[i].func_ptr(n);
    }

    
    qsort(list, total_funcs, sizeof(Function), compare);

    printf("=========================================================================\n");
    printf("  FUNCTIONS SORTED BY GROWTH RATE VALUE (evaluated at n = %.0f)\n", n);
    printf("=========================================================================\n\n");

    for (int i = 0; i < total_funcs; i++) {
        printf("%-2d. %-20s -> %e\n", i + 1, list[i].name, list[i].value);
    }

    printf("\n=========================================================================\n");

    return 0;
}