CC=gcc
CCF= -Wall -ansi -pedantic
CCC= -c -o
CCE= -o
FLTRM= src/lector.c
FLTRX= src/lector.l
FLTRL= includes/lector.h
DTSC= src/datos.c
DTSL= includes/datos.h
DTSO= obj/datos.o

all: mcCulloch-Pits lector redNeuronal perceptron-adaline
	@echo "Se compilo todo el codigo y se gneraron los ejecutables"


mcCulloch-Pits:  obj/neurona.o src/mcCulloch-Pits.c
	@echo "mcCulloch-Pits"
	@$(CC) $(CCF) $(CCE) mcCulloch-Pits src/mcCulloch-Pits.c obj/neurona.o
	@echo "mcCulloch-Pits generado ejecutable"

obj/neurona.o: src/neurona.c includes/neurona.h
	@echo "neurona"
	@$(CC) $(CCF) $(CCC) obj/neurona.o src/neurona.c
	@echo "neurona compilado"


perceptron-adaline: lector datos redNeuronal src/perceptron-adaline.c
	@$(CC) $(CCE) perceptron-adaline src/perceptron-adaline.c obj/*.o
	@echo creado ejecutable de perceptron y adaline

lector: $(FLTRM) $(FLTRX) $(FLTRL) datos
	@flex -o obj/lex.yy.c $(FLTRX)
	@gcc  -c obj/lex.yy.c -o obj/lex.yy.o
	@gcc $(CCF) $(CCC) obj/lector.o $(FLTRM)
	@echo lector compilado
datos: $(DTSC) $(DTSL)
	@$(CC) $(CCF) $(CCC) $(DTSO) $(DTSC)
	@echo datos compilado

redNeuronal: src/redNeuronal.c includes/redNeuronal.h
	@$(CC) $(CCF) $(CCC) obj/redNeuronal.o src/redNeuronal.c
	@echo redNeuronal compilado

commit: mrProper
	git add .
	git commit -m "commit makefile"
	git push
pull:
	git pull

mrProper:
	@rm -vf obj/*.o mcCulloch-Pits perceptron-adaline