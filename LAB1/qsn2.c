#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int toss_fair_coin() {
    return rand() % 2; 
}

int toss_biased_coin(double bias) {
    double r = (double)rand() / RAND_MAX;
    return (r < bias) ? 1 : 0;
}

int main() {
    srand(time(NULL));

    int total_tosses = 100000;
    int fair_heads = 0;
    int biased_heads = 0;
    double target_bias = 0.70; 

    for (int i = 0; i < total_tosses; i++) {
        if (toss_fair_coin() == 1) fair_heads++;
        if (toss_biased_coin(target_bias) == 1) biased_heads++;
    }

    double fair_prob = (double)fair_heads / total_tosses;
    double biased_prob = (double)biased_heads / total_tosses;

    printf("===================================================\n");
    printf("         DAA LAB 01 - COIN TOSS SIMULATION         \n");
    printf("===================================================\n");
    printf("Total Tosses: %d\n\n", total_tosses);

    printf("1. FAIR COIN:\n");
    printf("   - Total Heads: %d\n", fair_heads);
    printf("   - Simulated P(HEAD): %.4f (Expected: 0.5000)\n\n", fair_prob);

    printf("2. BIASED COIN (Target Bias: %.2f):\n", target_bias);
    printf("   - Total Heads: %d\n", biased_heads);
    printf("   - Simulated P(HEAD): %.4f (Expected: %.4f)\n", biased_prob, target_bias);
    printf("===================================================\n");

    return 0;
}