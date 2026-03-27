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

void test_power2(int a, int mod, int expected) {
    int risultato = 0;
    risultato = power2(a, mod);

    if (risultato == expected)
        printf("TEST power2(%d, %d): PASSED ✓\n", a, mod);
    else
        printf("TEST power2(%d, %d): FAILED ✗ (atteso %d, ottenuto %d)\n", a, mod, expected, risultato);
}


void test_factorization(){
//interesting number: 123456785
    int s;
    int i = 0;
    Num_Mul * v;
    clock_t start = clock();  // <-- inizio
    for(LLU  n=123456787; n<123456789; n++){

        s = sizeof(Num_Mul)*log(n);
        v = malloc(s);


        factorize(n, v, s, &i);
        LLU result = phi(v, i);

 
        printf("---------Number = %d--------\n",n);
        for(int j=0; j<i; j++){
            printf("mult = %d, prime = %llu\n", v[j].mult, v[j].prime);
        }
        printf("-------------------------------\n");
        i = 0;
        free(v);
    }
    clock_t end = clock();    // <-- fine

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Tempo: %.6f secondi\n", elapsed);


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
    test_power2(3, 5, 4);   // 3² mod 5 = 9 mod 5 = 4
    test_power2(4, 7, 2);   // 4² mod 7 = 16 mod 7 = 2
    test_power2(6, 5, 1);   // 6 > 5, quindi 6%5=1, 1² mod 5 = 1
    test_power2(1234, 5678, 1052);

}

