#include <stdlib.h>

#ifndef FUN
#define FUN


typedef long long unsigned int LLU;

typedef struct {
    LLU prime;
    int mult;
} Num_Mul;


void convert_binary(LLU n, int * v);
LLU power2(LLU a, LLU mod);
LLU FPA(LLU a, LLU q, LLU mod);
int MR_test_a(LLU n, LLU a);
int MR_test(LLU n, int k);
LLU gcd(LLU a, LLU b);
LLU is_Square(LLU N);
void factorize(LLU n, Num_Mul* v, int s, int * i);
LLU fermat_factorization(LLU n);
int find_element(LLU n, Num_Mul* v, int i);
LLU phi(Num_Mul *v, int size);
LLU phi_n(LLU n);


#endif
