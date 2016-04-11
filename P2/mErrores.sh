#!/usr/bin/env bash

file="bases-de-datos-p1/problema-real-3clases.txt" 

rm errorMedio.data

for i in `seq 1 1 30`;
do
	err=0.0
	#for j in `seq 1 20`;
	#do
 
		echo ./main -bp -fin $file -ocultas $i -norm
		./main -bp -fin $file -ocultas $i -norm > dump.txt
		val=$(<err.data)
		./main2 $err  $val > err.data
		err=$(<err.data)
	#done
	echo $err $i $j>> errorMedio.data
done    
