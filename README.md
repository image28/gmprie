# gmprie - unfinished libgmp riecoin client

Compile with 

#`gcc gmp_prime.c -O3 -lgmp -lm -o gmp_prime`

Test with 

#`./gmp_prime 1`

Currently hardcoded to 8+1 threads,
checking for 7 tuple patterns [[0,2,4,2,4,6,2],[0,2,6,4,2,4,2]] in parallel.
