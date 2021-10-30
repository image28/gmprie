#!/bin/bash
let START=1
let END=2000
let THREADS=1

./gmp_prime $START $END > output
primesieve $END -p > output-system

echo
echo "Verify against primesieve to $END"
diff -ya --suppress-common-lines output output-system > /dev/null
if test $? -eq 0; then echo "PASS"; else exit; fi
echo

echo "Benchmarking $END numbers"
echo "System"
date +%Y.%j.%R.%S.%N && primesieve $END -p > /dev/null; date +%Y.%j.%R.%S.%N
echo

echo "Updated"
date +%Y.%j.%R.%S.%N && ./gmp_prime $START $END > /dev/null; date +%Y.%j.%R.%S.%N
echo

echo "Threaded"
date +%Y.%j.%R.%S.%N && ./bench-threaded.sh $START $END $THREADS; date +%Y.%j.%R.%S.%N
echo

