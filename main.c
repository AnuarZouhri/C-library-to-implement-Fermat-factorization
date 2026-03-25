#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>

int main() {
    //2580621751
    int s;
    int i = 0;
    LLU n = 2580621351;
    Num_Mul * v;
    s = sizeof(Num_Mul)*log(n);
    v = malloc(s);

    clock_t start = clock();  // <-- inizio

    factorize(n, v, s, &i);
    LLU result = phi(v, i);

    clock_t end = clock();    // <-- fine

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    for(int j=0; j<i; j++){
        printf("mult= %d, prime= %llu\n", v[j].mult, v[j].prime);
    }

    printf("phi(%llu) = %llu\n", n, result);
    printf("Tempo: %.6f secondi\n", elapsed);  // <-- stampa
    printf("%llu",130000000000);
    free(v);

    return 0;
}