#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <time.h>


void convert_binary(LLU n, int *v){

    int i = 0;
    LLU remainder = 0;

    while(n>=1){

        remainder = n % 2;
        
        v[i] = remainder;
        i++;
        n = n / 2; 
        
    }

    return;

}

LLU FPA(LLU a, LLU q, LLU mod){

    int n_bit = (int)log2(q) + 1;
    int *binary = malloc(n_bit * sizeof(int));
    LLU old = 0;
    LLU new = 0;
    int i = 0;
    LLU risultato = 1;

    if(binary == NULL){
        printf("\nAllocamento fallito, calcolo FPA di %d.\n", a);
        
        printf("\nn_bit= , q= \n", n_bit, q);
        exit(1);
    }

    convert_binary(q, binary);
    old = (a % mod);
    if (binary[i] == 1){
        risultato = (risultato * old) % mod;
    }

    for(i=1;i<n_bit;i++){
        
        new = (old*old) % mod;

        if (binary[i] == 1){
            risultato = (risultato * new) % mod;
        }

        old = new;
    }

    free(binary);

    return risultato;
}


LLU gcd(LLU a, LLU b) {

    LLU temp;

    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int MR_test_a(LLU n, LLU a){

    int k = 0;
    LLU q = n-1;

    while(q % 2 == 0){
        k++;
        q = q / 2;
    }
    //printf("k= %d\n",k);

    if (n % 2 == 0 || (gcd(a,n)<n && gcd(a,n)>1))
        return 0;

    a = FPA(a,q,n);
    //printf("a ^ (%llu) mod %llu = %llu\n",q,n,a);

    if (a % n == 1)
        return 1;

    for(int i = 0; i<k; i++){

        if (a % n == (n-1))
            return 1;
        a = (a*a) % n;
        
        //printf("a_(%d) = %llu\n",i,a%n);
    }

    return 0;
 
}


int MR_test(LLU n, int k){

    srand(time(NULL) ^ clock());
    int test = 1; //test = 0 -> n is composite
                  //test = 1 -> n may be prime
    
    if(n == 2 || n == 3) return 1;

    for(int i=0; i<k; i++){
   
        LLU witness = 2 + ((LLU)rand() << 32 | (LLU)rand()) % (n - 3); //create a random 64 bit number
        //printf("witness = %llu\n", witness);
        test = MR_test_a(n, witness);
        if (test == 0){
            //printf("MR, witness = %llu\n", witness);
            return 0;
        }

    }

    return test;

}

void resize(Num_Mul **v, int new_size) {

    if (new_size == 0) {
        printf("Error! Size cannot be zero.\n");
        exit(1);
    }

    Num_Mul *temp = realloc(*v, new_size * sizeof(Num_Mul));

    if (temp == NULL) {
        printf("Error! Realloc failed.\n");
        free(*v);
        exit(1);
    }

    *v = temp;  
}

void factorize(LLU n, Num_Mul* v, int* s, int* i){
    
    int p;
 
    if(n == 1) return;

    int mr_test = MR_test(n,20);
     
    if(mr_test == 1){
        
        p = find_element(n,v,*i);
        if(p != -1){
            v[p].mult++;
        } 
        else{

            if(*i == *s) { //realloc if the vector is too small.
                
                int new_size = *i + *i / 2 + 1;  
                resize(&v, new_size);
                *s = new_size;
            }

            v[*i].prime = n;
            v[*i].mult = 1;
            (*i)++;
        }
        return;
    }

    LLU a = fermat_factorization(n);
    factorize(a,v,s,i);
    factorize(n/a,v,s,i);
    return;

}

LLU phi_n(LLU n) {
    LLU result = n;
    LLU temp = n;

    for (LLU p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            while (temp % p == 0)
                temp /= p;
            result -= result / p;
        }
    }
    if (temp > 1)
        result -= result / temp;

    return result;
}

LLU phi(Num_Mul *v, int size){
    
    LLU phi = 1;

    for(int i = 0; i<size; i++){
        phi = phi * (v[i].prime - 1)*pow(v[i].prime,v[i].mult-1);
    }

    return phi;
}


int find_element(LLU n, Num_Mul *v, int i){

    for(int j=0; j<=i; j++){

        if(v[j].prime == n){
            return j;
        }
    }

    return -1;

}

LLU fermat_factorization(LLU n){

    if (n % 2 == 0) return 2;

    // Phase 1: trial division up to a bound
    LLU bound = 1000000;
    for (LLU i = 3; i <= bound && i * i <= n; i += 2) {
        if (n % i == 0)
            return i;
    }

    // Phase 2: Fermat only if no small factor was found
    LLU a = (LLU)ceil(sqrt((double)n));
    LLU b2, b;
    while (1) {
        b2 = a * a - n;
        b = (LLU)sqrt((double)b2);  //check if the numeber is a perfect square
        if (b * b == b2)
            return a - b;
        a++;
    }
}


LLU trial_division(LLU n) {
    if (n % 2 == 0) return 2;
    LLU bound = (LLU)sqrt((double)n);
    for (LLU i = 3; i <= bound; i += 2) {
        if (n % i == 0)
            return i; //return the first found factor
    }
    return n; // n is prime
}
