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
VERDE='\033[0;32m'
AMARILLO='\033[1;33m'
NC='\033[0m' # No Color


all: compile

compile: mcCulloch-Pits perceptron-adaline prueba
	@printf "${VERDE}Se compilo todo el codigo y se gneraron los ejecutables${NC}\n"


mcCulloch-Pits:  obj/neurona.o src/mcCulloch-Pits.c
	@$(CC) $(CCF) $(CCE) mcCulloch-Pits src/mcCulloch-Pits.c obj/neurona.o
	@printf "${VERDE}mcCulloch-Pits generado ejecutable ${NC}\n"

obj/neurona.o: src/neurona.c includes/neurona.h
	@$(CC) $(CCF) $(CCC) obj/neurona.o src/neurona.c
	@printf "${AMARILLO}neurona compilado${NC}\n"


prueba: lector datos redNeuronal src/prueba.c
	@$(CC) $(CCE) prueba src/prueba.c obj/*.o


perceptron-adaline: lector datos redNeuronal src/perceptron-adaline.c
	@$(CC) $(CCF) $(CCE) perceptron-adaline src/perceptron-adaline.c obj/*.o
	@printf "${VERDE}creado ejecutable de perceptron y adaline${NC}\n"

lector: $(FLTRM) $(FLTRX) $(FLTRL) datos
	@gcc  -c obj/lex.yy.c -o obj/lex.yy.o
	@gcc $(CCF) $(CCC) obj/lector.o $(FLTRM)
	@printf "${AMARILLO}lector compilado${NC}\n"
flex: obj/lex.yy.c
	@flex -o obj/lex.yy.c $(FLTRX)

datos: $(DTSC) $(DTSL)
	@$(CC) $(CCF) $(CCC) $(DTSO) $(DTSC)
	@printf "${AMARILLO}datos compilado${NC}\n"

redNeuronal: src/redNeuronal.c includes/redNeuronal.h
	@$(CC) $(CCF) $(CCC) obj/redNeuronal.o src/redNeuronal.c
	@printf "${AMARILLO}redNeuronal compilado${NC}\n"

commit: mrProper
	git add .
	git commit -m "commit makefile"
	git push
pull:
	git pull

mrProper:
	@rm -vf obj/*.o mcCulloch-Pits perceptron-adaline prueba adaptacion.data
