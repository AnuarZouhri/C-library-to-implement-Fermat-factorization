#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>   // <-- aggiungi questo

int main() {
//154282
//23537031073 = 104729 × 224737
//15*33*49*14*16*19
    int s;
    int i = 0;
    LLU n = 9699690*29;
    Num_Mul * v;

    s = sizeof(Num_Mul)*log(n);
    v = malloc(s);

    Fermat_Fact(n, v, s, &i);


    for(int j=0; j<i;j++){
        printf("mult= %d,prime= %d\n",v[j].mult,v[j].prime);
    }

    free(v);
    
    return 0;
}