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

all: mcCulloch-Pits lector redNeuronal
	@echo "Se compilo todo el codigo y se gneraron los ejecutables"


mcCulloch-Pits:  obj/neurona.o src/mcCulloch-Pits.c
	@echo "mcCulloch-Pits"
	@$(CC) $(CCF) $(CCE) mcCulloch-Pits src/mcCulloch-Pits.c obj/neurona.o
	@echo "mcCulloch-Pits generado ejecutable"

obj/neurona.o: src/neurona.c includes/neurona.h
	@echo "neurona"
	@$(CC) $(CCF) $(CCC) obj/neurona.o src/neurona.c
	@echo "neurona compilado"



lector: $(FLTRM) $(FLTRX) $(FLTRL) datos
	@flex -o obj/lex.yy.c $(FLTRX)
	@gcc  -c obj/lex.yy.c -o obj/lex.yy.o
	@gcc $(CCF) -o lector $(FLTRM) obj/lex.yy.o $(DTSO)
	@echo lector compilado
datos: $(DTSC) $(DTSL)
	@$(CC) $(CCF) $(CCC) $(DTSO) $(DTSC)
	@echo datos compilado

redNeuronal: src/actualizaSalida.c src/iniRed.c includes/redNeuronal.h
	@$(CC) $(CCF) $(CCC) obj/iniRed.o src/iniRed.c
	@$(CC) $(CCF) $(CCC) obj/actualizaSalida.o src/actualizaSalida.c
	@echo redNeuronal compilado

commit:
	git add .
	git commit -m "commit makefile"
	git push
pull:
	git pull

mrProper:
	@rm -vf obj/*.o mcCulloch-Pits lector