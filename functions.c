#include "functions.h"
#include <math.h>
#include <stdio.h>

void convert_binary(int n, int *v){

    int i = 0;
    int remainder = 0;

    while(n>=1){

        remainder = n % 2;
        
        v[i] = remainder;
        i++;
        n = n / 2; 
        //printf("r= %d, n= %d, i= %d\n",remainder,n,i);

    }

    for(int j=i-1;j>=0;j--) {

        //printf("%d\n",v[j]);
    }

    return;

}

void FPA(int a, int q, int mod, int risultato){

    int n_bit = (int)log2(q) + 1;
    int *binary = malloc(n_bit * sizeof(int));
    int *parziali = malloc(n_bit * sizeof(int));

    if(binary == NULL || parziali == NULL){
        printf("\nAllocamento fallito%d.\n");
        exit(1);
    }




    convert_binary(q, binary);

    return;
}

int power2(int a, int mod){

    int risultato;

    if (a > mod){
        a = a % mod;
    }

    risultato = ( a * a ) % mod;

    return risultato;

}