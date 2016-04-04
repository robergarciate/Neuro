#!/usr/bin/env bash

file="bases-de-datos-p1/problema_real1.txt" 

mkdir errores
rm errores/errorMedioP1-tasa.data

for i in `seq 0.001 0.05 0.5`;
do
	err=0.0
	for j in `seq 1 10`;
	do
 
		echo ./main -bp -fin $file -ocultas 12 -norm -tasa $i -tolerancia 0.0000001 -etapas 1000
		./main -bp -fin $file -ocultas 12 -norm -tasa $i -tolerancia 0.0000001 -etapas 1000 > dump1.txt
		cp err.data err1.data
		val=$(<err1.data)
		./main2 $err  $val > err1.data
		err=$(<err1.data)
	done
	echo $err $i $j>> errores/errorMedioP1-tasa.data
done    
