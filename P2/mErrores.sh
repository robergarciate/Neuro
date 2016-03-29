#!/usr/bin/env bash

file="base-de-datos-p1/problema-real4.txt" 

for i in `seq 1 10`;
do
	for j in `seq 1 5`;
	do
		aux= $(($(i)*2))
		echo ./main -bp -fin $file -ocultas $aux
		./main -bp -fin $file -ocultas $aux

	done
done    