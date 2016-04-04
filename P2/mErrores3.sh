#!/usr/bin/env bash

file="bases-de-datos-p1/problema-real-3clases.txt" 

mkdir errores
rm errores/errorMedioP3-div.data

for i in `seq 2 1 30`;
do
	err=0.0
	for j in `seq 1 10`;
	do
 
		echo $j ./main -bp -fin $file -ocultas $i -norm -tasa 0.01 -tolerancia 0.00000001 -etapas 30000
		./main -bp -fin $file -ocultas $i -norm -tasa 0.01 -tolerancia 0.00000001 -etapas 30000 > dump3.txt
		cp err.data err3.data
		val=$(<err3.data)
		./main2 $err  $val > err3.data
		err=$(<err3.data)
	done
	echo $err $i $j>> errores/errorMedioP3-div.data
done    
