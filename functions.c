#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

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

int FPA(int a, int q, int mod){

    int n_bit = (int)log2(q) + 1;
    int *binary = malloc(n_bit * sizeof(int));
    int old = 0;
    int new = 0;
    int i = 0;
    int risultato = 1;

    if(binary == NULL){
        printf("\nAllocamento fallito%d.\n");
        exit(1);
    }

    convert_binary(q, binary);
    old = (a % mod);
    if (binary[i] == 1){
        risultato = (risultato * old) % mod;
    }

    for(i=1;i<n_bit;i++){

        new = power2(old,mod);
        if (binary[i] == 1){
            risultato = (risultato * new) % mod;
        }

        old = new;
    }


    free(binary);

    return risultato;
}

int power2(int a, int mod){

    int risultato;

    if (a > mod){
        a = a % mod;
    }

    risultato = ( a * a ) % mod;

    return risultato;

}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 0 -> composite.
// 1 -> probabily prime.
int MR_test_a(int n, int a){

    int k = 0;
    int q = n-1;

    while(q % 2 == 0){
        k++;
        q = q / 2;
    }

    if (n % 2 == 0 || (gcd(a,n)<n && gcd(a,n)>1))
        return 0;

    a = FPA(a,q,n);

    if (a % n == 1)
        return 1;

    for(int i = 0; i<k; i++){

        if (a % n == (n-1))
            return 1;
        
        a = power2(a,n);
    }

    return 0;
 

}

int MR_test(int n, int k){

    srand(time(NULL) ^ clock());
    int a;
    int test = 1; //test = 0 -> n is composite
                  //test = 1 -> n may be prime
    
    if(n == 2 || n == 3) return 1;

    for(int i=0; i<k; i++){
   
        a = 2 + rand() % (n - 3);
        //printf("a = %d\n", a);
        test = MR_test_a(n,a);
        if (test == 0){
            //printf("MR, witness = %d\n",a);
            return 0;
        }

    }

    return test;

}


void Fermat_Fact(int n, Num_Mul* v, int s, int * i){
    int p;
 
    if(n == 1) return;

    int mr_test = MR_test(n,20);
     
    if(mr_test == 1){
        
        p = find_element(n,v,*i);
        if(p != -1){
            v[p].mult++;
        } 
        else{
            v[*i].prime = n;
            v[*i].mult = 1;
            (*i)++;
        }
        return;
    }

    int a = factorize(n);
    Fermat_Fact(a,v,s,i);
    Fermat_Fact(n/a,v,s,i);
    return;


}

int phi_n(int n){

    Num_Mul *v;
    int size = log(n) + 1;
    int phi = 1;
    int s = size * sizeof(Num_Mul);

    v = malloc(s);

    if(v == NULL){
        exit(1);
    }

    Fermat_Fact(n,v,s,0);


    free(v);

    return phi;
}

int is_Square(int N){

    int t = sqrt(N);

    for(int i=0; i<2; i++){

        if((t+i)*(t+i) == N)
            return t;
    }

    return -1;
}


int find_element(int n, Num_Mul *v, int i){

    for(int j=0; j<=i; j++){

        if(v[j].prime == n){
            return j;
        }
    }

    return -1;

}

int factorize(int n){
    int k = 0;
    int b = 0;
    int a = -1; //default value
    int g = 1;  //default value
    while(1){
        k++;
        b = 0;
        if(k!=2){
            while(b <= sqrt(k*n)){
                b++;
                a = b*b + k*n;
                a = is_Square(a);
                if(a != -1){
                    g = gcd(n,a+b);
                    
                    printf("n= %d, b= %d, k= %d, a= %d, g= %d\n",n,b,k,a,g);
                    if(g != 1 && g != n)
                        return g;
                }

            }
        }
    }

}