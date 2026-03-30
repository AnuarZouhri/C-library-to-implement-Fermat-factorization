#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <time.h>



/**
 * @brief Converts a number to its binary representation.
 *
 * Stores the bits of `n` into the array `v` in LSB-first order
 * (least significant bit at index 0).
 *
 * @param n   The number to convert (unsigned long long).
 * @param v   Output array where bits are stored. Must be pre-allocated
 *            with at least floor(log2(n)) + 1 elements.
 *
 * @note  The array is filled LSB-first, so v[0] is the least significant bit.
 *        Example: n=6 (binary 110) → v = {0, 1, 1}
 *
 * @warning No bounds checking is performed on `v`.
 *          Ensure the array is large enough before calling.
 */
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

/**
 * @brief Computes a^q mod (mod) using Fast Power Algorithm (square-and-multiply).
 *
 * Uses the binary representation of the exponent `q` to compute
 * modular exponentiation efficiently in O(log q) multiplications.
 *
 * @param a    The base.
 * @param q    The exponent.
 * @param mod  The modulus.
 * @return     Result of a^q mod (mod).
 *
 * @note  Internally calls convert_binary() and power2().
 *        Exits the program if memory allocation fails.
 *
 * @example FPA(2, 10, 1000) → 1024 % 1000 = 24
 */

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

        new = power2(old,mod);
        if (binary[i] == 1){
            risultato = (risultato * new) % mod;
        }

        old = new;
    }

    free(binary);

    return risultato;
}

/**
 * @brief Compute the power of a number given the modulo
 *
 *
 * @param a    The base.
 * @param mod  The modulus.
 * @return     Result of a^a mod (mod).
 *
 */

LLU power2(LLU a, LLU mod){

    LLU risultato;

    if (a > mod){
        a = a % mod;
    }

    risultato = ( a * a ) % mod;

    return risultato;

}

/**
 * @brief Compute the gcd of two numbers
 *
 *  O(log a) operations
 * 
 *
 * @param a    The first number (llu).
 * @param b    The second number (llu).
 * @return     gcd(a,b).
 *
 */
LLU gcd(LLU a, LLU b) {

    LLU temp;

    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Performs a single Miller-Rabin primality test with witness `a`.
 *
 * Writes n-1 as 2^k * q with q odd, then checks if `a` is a witness
 * of compositeness for `n`.
 *
 * @param n  The number to test for primality (must be odd and > 3).
 * @param a  The witness candidate (1 < a < n-1).
 * @return   0 if `n` is definitely composite.
 *           1 if `n` is probably prime for this witness.
 *
 * @note  A return value of 1 does NOT guarantee primality.
 *        Call MR_test() with multiple witnesses for higher confidence.
 *
 * @example MR_test_a(221, 174) → 0  (221 = 13 × 17, composite)
 * @example MR_test_a(7, 3)     → 1  (7 is prime)
 */
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
        a = power2(a,n);
        
        //printf("a_(%d) = %llu\n",i,a%n);
    }

    return 0;
 
}

/**
 * @brief Performs the Miller-Rabin primality test with `k` random witnesses.
 *
 * Repeatedly calls MR_test_a() with random witnesses to determine
 * whether `n` is prime. The more witnesses used, the lower the
 * probability of a false positive (at most 4^-k per round).
 *
 * @param n  The number to test for primality.
 * @param k  Number of random witnesses to test (recommended: k >= 20).
 * @return   0 if `n` is definitely composite.
 *           1 if `n` is probably prime.
 *
 * @note  Special cases: returns 1 immediately for n=2 and n=3.
 *        The seed is randomized via srand(time(NULL) ^ clock()).
 *
 * @warning rand() % (n-3) may have bias for large `n` since
 *          `n` can exceed RAND_MAX. For cryptographic use,
 *          replace rand() with a CSPRNG.
 *
 * @example MR_test(104729, 20) → 1  (104729 is prime)
 * @example MR_test(104728, 20) → 0  (104728 is composite)
 */
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


void factorize(LLU n, Num_Mul* v, int s, int * i){
    int p;
 
    if(n == 1) return;

    int mr_test = MR_test(n,20);
     
    if(mr_test == 1){
        
        p = find_element(n,v,*i);
        if(p != -1){
            v[p].mult++;
        } 
        else{

            if(*i == s) resize(v, (*i)*0.2, s);
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

LLU phi_n(LLU n){

    int phi = 0;

    for(int i=1; i<n; i++){
        if(gcd(i,n)==1) phi++;
    }

    return phi;
}

LLU phi(Num_Mul *v, int size){
    
    LLU phi = 1;

    for(int i = 0; i<size; i++){
        phi = phi * (v[i].prime - 1)*pow(v[i].prime,v[i].mult-1);
    }

    return phi;
}

LLU is_Square(LLU N){

    LLU t = sqrt(N);

    for(int i=0; i<2; i++){

        if((t+i)*(t+i) == N)
            return t;
    }

    return 0;
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
    int k = 0;
    LLU b = 0;
    LLU a = 0; //default value
    LLU g = 1;  //default value
    if((n & 1) == 0) return 2; //check the last bit. If 0, then the number is even.
    while(1){
        k++;
        b = 0;
        if(k!=2){
            while(b <= sqrt(k*n)){
                b++;
                a = b*b + k*n;
                //printf("\na = %llu, overflow = %d\n", a, a == ULLONG_MAX);
                a = is_Square(a);
                if(a != 0){
                    g = gcd(n,a+b);
                    
                    printf("n= %llu, b= %llu, k= %llu, a= %llu, g= %llu\n",n,b,k,a,g);
                    if(g != 1 && g != n)
                        return g;
                }

            }
        }
    }

}


int resize(Num_Mul **v, int i, int size) {

    if (i == 0) {
        printf("Error! Size cannot be zero.\n");
        exit(1);
    }

    Num_Mul *temp = realloc(*v, i * sizeof(Num_Mul));

    if (temp == NULL) {
        printf("Error! Realloc failed.\n");
        free(*v);
        exit(1);
    }

    *v = temp;

    return i;
}

LLU trial_division(LLU n){

    LLU bound = sqrt(n);
    for(int i = 3; i < bound; i++){


        if(n % i == 0)
            return i;
    }
}
