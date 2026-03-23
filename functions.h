#include <stdlib.h>

#ifndef FUN
#define FUN


typedef struct {
    int prime;
    int mult;
} Num_Mul;


void convert_binary(int n, int * v);
int power2(int a, int mod);
int FPA(int a, int q, int mod);
int MR_test_a(int n, int a);
int MR_test(int n, int k);
int gcd(int a, int b);
int is_Square(int N);
void Fermat_Fact(int n, Num_Mul* v, int s, int * i);
int factorize(int n);
int find_element(int n, Num_Mul* v, int i);
int phi_n(int n);



#endif
