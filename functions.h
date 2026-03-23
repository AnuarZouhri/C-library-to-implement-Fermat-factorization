#include <stdlib.h>

#ifndef FUN
#define FUN


typedef struct {
    unsigned int prime;
    int mult;
} Num_Mul;

typedef long long unsigned int LLU;


void convert_binary(LLU n, int * v);
int power2(LLU a, int mod);
int FPA(LLU a, int q, int mod);
int MR_test_a(LLU n, int a);
int MR_test(LLU n, int k);
int gcd(LLU a, LLU b);
int is_Square(LLU N);
void Fermat_Fact(LLU n, Num_Mul* v, int s, int * i);
int factorize(LLU n);
int find_element(LLU n, Num_Mul* v, int i);
int phi_n(LLU n);



#endif
