#!/usr/bin/env bash

file="bases-de-datos-p1/problema_real1.txt" 

mkdir errores
rm errores/errorMedioP1-tasa.data

ruido="35"
neuronas="16"
err=0.0
for i in `seq 1 20`;
do
 
	#echo ./main -bp -fin bases-de-datos-p1/alfabeto_dat.txt -alf -train 1.0 -test 1.0 -etapas 1000 -bip -ocultas $neuronas -ruidoTestP $ruido -ruidoTestN 10.0
	./main -bp -fin bases-de-datos-p1/alfabeto_dat.txt -alf -train 1.0 -test 1.0 -etapas 1000 -bip -ocultas $neuronas -ruidoTestP  $ruido -ruidoTestN 10.0 > dump1.txt
	
	val=$(<err.data)
	./main2 $err  $val > err1.data
	err=$(<err1.data)
	echo $err $val
done    
