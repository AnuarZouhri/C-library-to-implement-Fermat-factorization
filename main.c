#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include <time.h>   // <-- aggiungi questo

int main() {
    clock_t start, end;
    double tempo;
    double prova;
    int x = 49;
    start = clock();

    //FPA(3, 300, 1000);
    //FPA(7, 120, 1198);
    printf("%d\n",MR_test(103,10));
    //test_all();
    printf("\n%d\n",is_Square(16));
    
    printf("\n%d\n",is_Square(789));
    
    printf("\n%d\n",is_Square(1999878400));

    end = clock();

    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo impiegato: %f secondi\n", tempo);

    return 0;
}