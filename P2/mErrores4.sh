#!/usr/bin/env bash

file="bases-de-datos-p1/problema-real4.txt" 

mkdir errores
rm errores/errorMedioP4-div.data

for i in `seq 3 1 20`;
do
	err=0.0
	for j in `seq 1 10`;
	do
 
		echo ./main -bp -fin $file -ocultas $i -tasa 0.01 -tolerancia 0.00000001 -etapas 1000
		./main -bp -fin $file -ocultas $i -tasa 0.01 -tolerancia 0.00000001 -etapas 1000 > dump4.txt
		cp err.data err4.data
		val=$(<err4.data)
		./main2 $err  $val > err4.data
		err=$(<err4.data)
	done
	echo $err $i $j>> errores/errorMedioP4-div.data
done    
