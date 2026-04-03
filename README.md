# Totient-Function-in-C

I want to write a C program to compute the Euler function on a integer number N. For this I need to factorize the number N in his prime and then apply the formula. This factorization is done by means of the Fermat factorization by gcd.


# fermat-factorization

A small C library implementing integer factorization and number theory utilities, centered around a hybrid Fermat factorization algorithm. Built for educational purposes and experimentation with primality testing and factorization methods.

---

## Overview

This library provides tools to factorize 64-bit unsigned integers using a combination of:
- **Trial division** for small factors
- **Miller-Rabin primality test** for fast primality checking
- **Fermat's factorization method** for large composite factors
- **Euler's totient function** via both brute-force and formula-based approaches

---

## Compilation

The library uses `math.h`, so make sure to link with `-lm`.

```bash
gcc -o main *.c -lm
```

Or with debug symbols:

```bash
gcc -g -o main *.c -lm
```

---

## Function Reference

### Factorization

#### `void factorize(LLU n, Num_Mul *v, int s, int *i)`
Recursively factorizes `n` and stores its prime factors with their multiplicities in `v`.
Uses Miller-Rabin to check primality, and Fermat's method to split composite factors.
- `n` — number to factorize (must be ≥ 1)
- `v` — pre-allocated array of `Num_Mul` structures
- `s` — allocated size of `v`
- `i` — pointer to the next free index in `v`, updated by the function

#### `LLU fermat_factorization(LLU n)`
Finds a non-trivial factor of `n` using a hybrid approach:
1. Returns `2` immediately if `n` is even.
2. Tries trial division up to a fixed bound for small factors.
3. Falls back to classical Fermat's method (`a² - n = b²`) for large factors.
- Returns a non-trivial factor of `n`.
- **Note:** loops indefinitely until a factor is found; termination is not guaranteed for all inputs.

#### `LLU trial_division(LLU n)`
Finds the smallest factor of `n` by testing odd divisors from 3 up to `√n`.
- Returns the first factor found, or `n` itself if prime.

---

### Primality Testing

#### `int MR_test(LLU n, int k)`
Runs `k` rounds of the Miller-Rabin probabilistic primality test on `n` with random witnesses.
- Returns `1` if `n` is probably prime, `0` if composite.
- False positive probability: at most `4^(-k)` (with `k=20`, roughly `10^(-12)`).

#### `int MR_test_a(LLU n, LLU a)`
Runs a single round of Miller-Rabin with witness `a`.
- Returns `1` if `n` passes the test for witness `a`, `0` otherwise.

---

### Euler's Totient Function

#### `LLU phi(Num_Mul *v, int size)`
Computes φ(n) from the prime factorization of `n` using the formula:

φ(n) = ∏ (pᵢ - 1) · pᵢ^(eᵢ - 1)

- Requires the factorization to be already computed via `factorize()`.
- Time complexity: O(number of distinct prime factors).

#### `LLU phi_n(LLU n)`
Computes φ(n) directly without prior factorization, using trial division up to `√n`.
- Time complexity: O(√n).
- Suitable for large inputs where the factorization is not already available.

---

### Utilities

#### `LLU FPA(LLU a, LLU q, LLU mod)`
Computes `a^q mod n` using fast modular exponentiation (binary method).

#### `LLU power2(LLU a, LLU mod)`
Computes `a² mod n`.

#### `LLU gcd(LLU a, LLU b)`
Computes the greatest common divisor of `a` and `b` using the Euclidean algorithm.

#### `LLU is_Square(LLU N)`
Checks whether `N` is a perfect square.
- Returns its integer square root if so, `0` otherwise.

#### `int find_element(LLU n, Num_Mul *v, int i)`
Searches for prime `n` in the factor array `v` up to index `i`.
- Returns the index if found, `-1` otherwise.

#### `void convert_binary(LLU n, int *v)`
Converts `n` to its binary representation stored in array `v` (LSB first).

#### `Num_Mul* resize(Num_Mul *v, int new_size, int old_size)`
Resizes the factor array `v` via `realloc`. Returns the new pointer.

---

## Data Types

```c
typedef unsigned long long LLU;

typedef struct {
    LLU prime;   // prime factor
    int mult;    // its multiplicity
} Num_Mul;
```

---

## Known Limitations

- **Overflow:** all arithmetic is done on 64-bit unsigned integers (`unsigned long long`). Products of two large primes close to `2^32` may overflow intermediate calculations.
- **`fermat_factorization` convergence:** the function may loop for a very long time on numbers of the form `n = p · q` where `p` is small and `q` is large (e.g. `n = 7 · 1428185749`), since Fermat's method is slow when factors are far apart.
- **`resize` propagation:** the realloc'd pointer is now correctly returned, but `factorize` does not update `s` after resizing, so the resize condition `*i == s` may trigger incorrectly on subsequent calls.
- **`trial_division` even numbers:** the loop starts at 3 and does not handle even factors other than 2. Always call it after checking divisibility by 2.
- **`MR_test` randomness:** uses `rand()` seeded with `time(NULL) ^ clock()`. Not suitable for cryptographic use.

---

## Limitations of Fermat's Method

Fermat factorization is efficient only when the two factors of `n` are close to each other (i.e. `n = p · q` with `p ≈ q`). For unbalanced factors, trial division or Pollard's rho algorithm is significantly faster.

| Case | Recommended method |
|---|---|
| Small factor | Trial division |
| p ≈ q (both large) | Fermat's method |
| p, q large and arbitrary | Pollard's rho (not yet implemented) |


