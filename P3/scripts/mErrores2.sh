#!/usr/bin/env bash

file="bases-de-datos-p1/problema_real2.txt" 

mkdir errores
rm errores/errorMedioP2-tasa.data

for i in `seq 0.001 0.05 0.5`;
do
	err=0.0
	for j in `seq 1 10`;
	do
 
		echo ./main -bp -fin $file -ocultas 2 -norm -tasa $i -tolerancia 0.0000001 -etapas 1000
		./main -bp -fin $file -ocultas 2 -norm -tasa $i -tolerancia 0.0000001 -etapas 1000 > dump2.txt
		cp err.data err2.data
		val=$(<err2.data)
		./main2 $err  $val > err2.data
		err=$(<err2.data)
	done
	echo $err $i $j>> errores/errorMedioP2-tasa.data
done    
