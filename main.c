#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>   // <-- aggiungi questo

int main() {

    Num_Mul v[]={
        {3,2},
        {2,5},
        {7,1}
    };

    printf("trovato = %d",find_element(1,v,3));

    return 0;
}