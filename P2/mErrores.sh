#!/usr/bin/env bash

file="bases-de-datos-p1/problema-real4.txt" 
incr=2
for i in `seq 1 10`;
do
	for j in `seq 1 5`;
	do
 
		echo ./main -bp -fin $file -ocultas $(($i * $incr)) -norm
		./main -bp -fin $file -ocultas $(($i * $incr)) -norm

	done
done    
