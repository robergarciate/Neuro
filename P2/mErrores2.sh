#!/usr/bin/env bash

file="bases-de-datos-p1/problema_real2.txt" 

mkdir errores
rm errores/errorMedioP2-div.data

for i in `seq 2 1 30`;
do
	err=0.0
	for j in `seq 1 10`;
	do
 
		echo ./main -bp -fin $file -ocultas $i -norm -tasa 0.01 -tolerancia 0.0000001
		./main -bp -fin $file -ocultas $i -norm -tasa 0.01 -tolerancia 0.0000001 > dump2.txt
		cp err.data err2.data
		val=$(<err2.data)
		./main2 $err  $val > err2.data
		err=$(<err2.data)
	done
	echo $err $i $j>> errores/errorMedioP2-resta.data
done    
