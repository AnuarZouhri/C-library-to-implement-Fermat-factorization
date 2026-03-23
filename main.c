#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>   // <-- aggiungi questo

int main() {
//154282
    int s;
    int  i = 0;
    int n = 15282;
    Num_Mul * v;
    long long unsigned int u;

    printf("%llu\n", ULLONG_MAX); 

    s = sizeof(Num_Mul)*log(n);
    v = malloc(s);

    /*Fermat_Fact(n, v, s, &i);


    for(int j=0; j<i;j++){
        printf("mult= %d,prime= %d\n",v[j].mult,v[j].prime);
    }
    */
    return 0;
}