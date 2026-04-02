#include <stdio.h>
#include "functions.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void test_convert_binary(int n) {
    int n_bit = (int)log2(n) + 1;
    int *binary = malloc(n_bit * sizeof(int));

    if(binary == NULL){
        printf("\nAllocamento fallito per n= %d.\n",n);
        exit(1);
    }

    convert_binary(n, binary);

    // ricalcola il numero dal binario
    int risultato = 0;
    for (int i = 0; i < n_bit; i++) {
        risultato += binary[i] * (int)pow(2, i);
    }

    if (risultato == n)
        printf("TEST %d: PASSED ✓\n", n);
    else
        printf("TEST %d: FAILED ✗ (ottenuto %d)\n", n, risultato);

    free(binary);
}


void test_factorization() {
    //1000000016000000063
    //111112222267835434
    //1111122222674
    LLU n = 10000016000000063;
    int s = (int)(log2(n) + 1);
    int i = 0;
    Num_Mul *v = malloc(s * sizeof(Num_Mul));
    clock_t start, end;
    double elapsed;
    
    printf("========== Testing n = %llu ==========\n\n", n);

    // --- factorize + phi ---
    start = clock();
    factorize(n, v, &s, &i);
    LLU result_phi = phi(v, i);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[factorize + phi]\n");
    printf("Factors: ");
    for (int j = 0; j < i; j++)
        printf("%llu^%d ", v[j].prime, v[j].mult);
    printf("\nphi(%llu) = %llu\n", n, result_phi);
    printf("Time: %.6f seconds\n\n", elapsed);
    
    // --- phi_n only ---
    start = clock();
    LLU result_phi_n = phi_n(n);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[phi_n only]\n");
    printf("phi(%llu) = %llu\n", n, result_phi_n);
    printf("Time: %.6f seconds\n\n", elapsed);

    // --- trial_division (full factorization) ---
    start = clock();
    LLU temp = n;
    printf("[trial_division]\n");
    printf("Factors: ");
    while (temp > 1) {
        LLU factor = trial_division(temp);
        int exp = 0;
        while (temp % factor == 0) {
            temp /= factor;
            exp++;
        }
        printf("%llu^%d ", factor, exp);
    }
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime: %.6f seconds\n\n", elapsed);
    /*
    // --- sanity check ---
    printf("phi results match: %s\n", result_phi == result_phi_n ? "YES" : "NO");
    printf("======================================\n");
    */
    free(v);
}

void test_all(){


    printf("\n---Test delle funzioni---\n");
    printf("\n---test_convert_to_binary---\n");
    test_convert_binary(12);
    test_convert_binary(5);
    test_convert_binary(8);
    test_convert_binary(1);
    test_convert_binary(255);
    printf("\n---test_power2---\n");
}

