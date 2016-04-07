%{
#include <stdio.h> 
#include "../includes/lector.h"
%}

%option noyywrap

%%
[-]?[0-9][0-9]*[.][0-9][0-9]* 	{return TOK_DOUBLE;}
[-]?[0-9][0-9]* 				{return TOK_INTEGER;}
\/\/.*							{return TOK_COMENTARIO;}
.|[/n/r]						{return TOK_CARACTER;}


%%