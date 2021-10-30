#!/bin/bash
let START="100000000000000000000000000000000000000000000000000000000000000000000000"
let INTERVAL="1000000000"
let THREADS=5
let CURRENT=$INTERVAL

let TOTAL=$((INTERVAL*THREADS))

echo -n "Starting search of $TOTAL numbers for primes on $THREADS threads, $INTERVAL numbers per thread at "
date +%Y.%j.%R.%S.%N
while test $START -lt $THREADS
do
	./gmp_prime "$START" $CURRENT | wc -l  #> primes-$CURRENT
	let START=$START+1;
	let CURRENT=$START*$INTERVAL
done

./gmp_prime $START $CURRENT | wc -l
echo -n "Finished at "
date +%Y.%j.%R.%S.%N
