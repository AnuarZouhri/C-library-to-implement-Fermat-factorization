#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>   // <-- aggiungi questo

int main() {
//154282
    int s;
    int i = 0;
    LLU n = 15282;
    Num_Mul * v;

    s = sizeof(Num_Mul)*log(n);
    v = malloc(s);

    /*Fermat_Fact(n, v, s, &i);


    for(int j=0; j<i;j++){
        printf("mult= %d,prime= %d\n",v[j].mult,v[j].prime);
    }
    */
    return 0;
}