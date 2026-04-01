#include <stdlib.h>

#ifndef FUN
#define FUN


typedef long long unsigned int LLU;

typedef struct {
    LLU prime;
    int mult;
} Num_Mul;

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
void convert_binary(LLU n, int * v);


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
LLU FPA(LLU a, LLU q, LLU mod);


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
int MR_test_a(LLU n, LLU a);

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
int MR_test(LLU n, int k);

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
LLU gcd(LLU a, LLU b);


/**
 * @brief Recursively factorizes n and stores its prime factors with multiplicities.
 *
 * Uses a hybrid approach:
 * - First checks divisibility by a fixed set of small primes (fast path).
 * - Then uses the Miller-Rabin primality test to check if the remaining factor is prime.
 * - If composite, finds a non-trivial factor via fermat_factorization() and recurses
 *   on both factors.
 *
 * @note The small primes lookup table is declared static const to avoid
 *       repeated stack allocation across recursive calls.
 * @note The Miller-Rabin test is run with 20 witnesses, giving a false positive
 *       probability of at most 4^(-20) ≈ 10^(-12).
 * @note The array v must be pre-allocated by the caller with at least s elements.
 *
 * @param n  The number to factorize (must be >= 1).
 * @param v  Array of Num_Mul structures where the factors are stored.
 * @param s  Current allocated size of v.
 * @param i  Pointer to the index of the next free slot in v; updated by the function.
 */
void factorize(LLU n, Num_Mul* v, int s, int * i);

/**
 * @brief Factors n using a variant of Fermat's factorization method (k-Fermat / SQUFOF).
 *
 * For each multiplier k >= 1 (k != 2), searches for b such that b^2 + k*n is a
 * perfect square a^2; if gcd(n, a+b) is a non-trivial factor of n, it is returned.
 * If n is even, returns 2 immediately.
 *
 * @note The function loops indefinitely until a factor is found;
 *       termination is not guaranteed for all inputs.
 * @note Contains an active debug printf.
 *
 * @param n  The number to factorize (must be > 1 and composite).
 * @return   A non-trivial factor of n.
 */
LLU fermat_factorization(LLU n);


/**
 * @brief Finds a factor of n using trial division.
 *
 * Tests all odd divisors from 3 up to floor(sqrt(n)).
 *
 * @warning If n has no factors in the range [3, sqrt(n)], the function
 *          returns without an explicit value (undefined behavior).
 * @warning The loop starts at 3 but does not skip even numbers; incrementing
 *          i by 2 would improve efficiency.
 *
 * @param n  The number to factor.
 * @return   The first factor of n found in the explored range, if any.
 */
LLU trial_division(LLU n);

/**
 * @brief Searches for a prime number in the array of already-found factors.
 *
 * Scans the array v up to index i (inclusive) and returns the position
 * of the first element whose prime field equals n.
 *
 * @param n  The prime number to search for.
 * @param v  Array of Num_Mul structures to search in.
 * @param i  Index of the last valid element in the array.
 * @return   The index of the matching element, or -1 if not found.
 */
int find_element(LLU n, Num_Mul* v, int i);

/**
 * @brief Computes Euler's totient function phi(n) from the factorization of n.
 *
 * Uses the formula: phi(n) = prod( (p_i - 1) * p_i^(e_i - 1) )
 * where p_i are the prime factors and e_i their respective multiplicities.
 *
 * @param v     Array of Num_Mul structures containing the prime factors and their multiplicities.
 * @param size  Number of elements in the array v.
 * @return      The value of phi(n).
 */
LLU phi(Num_Mul *v, int size);

/**
 * @brief Computes Euler's totient function phi(n) without prior factorization.
 *
 * Finds the prime factors of n via trial division up to sqrt(n) and applies
 * the formula: phi(n) = n * prod(1 - 1/p) for each distinct prime factor p.
 *
 * @note Time complexity: O(sqrt(n)), which makes it suitable for large inputs
 *       where the full factorization is not already available.
 *       If the factorization of n is already known, use phi() instead.
 *
 * @param n  The integer whose totient is to be computed (must be > 0).
 * @return   The value of phi(n).
 */
LLU phi_n(LLU n);

/**
 * @brief Dynamically resizes an array of Num_Mul using realloc.
 *
 * @warning The pointer v is updated locally but the change does not propagate
 *          to the caller (the parameter is passed by value).
 *          Consider passing a Num_Mul** or returning the new pointer instead.
 *
 * @param v     Pointer to the array to resize.
 * @param i     Desired new size (must be > 0).
 * @param size  Current size of the array (unused inside the function).
 * @return      The new size i on success; terminates the program on error.
 */
int resize(Num_Mul *v, int i, int size);


#endif
