#!/usr/bin/env bash

file="bases-de-datos-p1/problema_real1.txt" 

mkdir errores
rm errores/errorAlf-16Te.data

neuronas="16"
for ruido in `seq 1 2 35`;
do
	err=0.0

	for i in `seq 1 10`;
	do
	 
		#echo /main -bp -fin bases-de-datos-p1/alfabeto_dat.txt -alf -train 1.0 -test 1.0 -bip -ocultas $neuronas -ruidoTestP $ruido -ruidoTestN 10.0  -tasa 0.1 -etapas 5000
		./main -bp -fin bases-de-datos-p1/alfabeto_dat.txt -alf -train 1.0 -test 1.0 -bip -ocultas $neuronas -ruidoTestP $ruido -ruidoTestN 10.0  -tasa 0.1 -etapas 1000 > dump1.txt
		
		val=$(<err.data)
		./main2 $err  $val > err1.data
		err=$(<err1.data)
		echo $ruido $i $err
	done    
	echo $err >> errores/errorAlf-16Te.data
done
