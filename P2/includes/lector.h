/******************************************************
Nombre: tokens.h
Descripci�n: Definici�n de tokens para el lenguaje ALFA
******************************************************/
#ifndef _TOKENS_H
#define _TOKENS_H

#include "../includes/datos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Palabras reservadas */ 
#define TOK_DOUBLE				100
#define TOK_INTEGER				101
#define TOK_CARACTER			102

/**/
datos* leerDatos(FILE* fin);
int lectorChusco(FILE * f);
#endif
