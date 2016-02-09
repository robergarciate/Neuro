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

all: mcCulloch-Pits
	@echo "Se compilo todo el codigo y se gneraron los ejecutables"


mcCulloch-Pits:  obj/neurona.o src/mcCulloch-Pits.c
	@echo "mcCulloch-Pits"
	$(CC) $(CCF) $(CCE) mcCulloch-Pits src/mcCulloch-Pits.c obj/neurona.o
	@echo "mcCulloch-Pits generado ejecutable"

obj/neurona.o: src/neurona.c includes/neurona.h
	@echo "neurona"
	@$(CC) $(CCF) $(CCC) obj/neurona.o src/neurona.c
	@echo "neurona compilado"



lector: $(FLTRM) $(FLTRX) $(FLTRL) datos
	flex -o obj/lex.yy.c $(FLTRX)
	gcc -c obj/lex.yy.c -o obj/lex.yy.o
	gcc -o lector $(FLTRM) obj/lex.yy.o $(DTSO)
	rm obj/*.c
	echo lector compilado
datos: $(DTSC) $(DTSL)
	@$(CC) $(CCC) $(DTSO) $(DTSC)
	@echo datos compilado

mrProper:
	@rm -vf obj/* mcCulloch-Pits