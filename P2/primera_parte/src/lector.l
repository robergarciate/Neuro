%{
#include <stdio.h> 
#include "../includes/lector.h"
%}

%option noyywrap

%%
[-]?[0-9][0-9]*[.][0-9][0-9]* 	{return TOK_DOUBLE;}
[-]?[0-9][0-9]* 				{return TOK_INTEGER;}
.|[/n/r]							{return TOK_CARACTER;}


%%