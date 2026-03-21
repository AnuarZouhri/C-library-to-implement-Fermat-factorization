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


    end = clock();

    tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo impiegato: %f secondi\n", tempo);

    return 0;
}