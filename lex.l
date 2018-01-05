%option noyywrap
%option always-interactive
%{
#include <stdlib.h>
#include "y.tab.h"
#include <cstring>
void set_value();
void set_str_value();
using namespace std;
%}

LETTER   [a-zA-Z_]
DIGIT    [0-9]
INT		 {DIGIT}+
NEWLINE  [\n]
WSPACE   [ \t\r\n]+
IDENT    {LETTER}({LETTER}|{DIGIT})*
STR      \"[^\"]*\"

%%
{STR}		{set_str_value(); return STRING_CONST;}
"int"		{return INT_VAR_TYPE;}
"break"		{return BREAK;}
"continue"	{return CONTINUE;}
"while"		{return WHILE;}
"if"		{return IF;}
"else"		{return ELSE;}
"for"		{return FOR;}
"!"			{return NOT;}
"&&"		{return AND;}
"&"			{return ADDRESS_AND;}
"||"		{return OR;}
"%"			{return MOD;}
"return"	{return RETURN;}
"="			{return ASSIGN;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIVIDE;}
"("			{return OPEN_PAR;}
")"			{return CLOSE_PAR;}
"["			{return BEGIN_BR;}
"]"			{return END_BR;}
"{"			{return BEGIN_CU;}
"}"			{return END_CU;}
","			{return COMMA;}
";"			{return SEMICOLON;}
"<"			{return LESS;}
">"			{return MORE;}
"<="		{return LESS_OR_EQUAL;}
">="		{return MORE_OR_EQUAL;}
"++"		{return PLUS_PLUS;}
"--"		{return MINUS_MINUS;}
"=="		{return EQUAL;}
"!="		{return NOTEQUAL;}
{INT}		{set_value(); return INTEGER;}
{IDENT}		{set_value(); return ID;}
{NEWLINE}	{}
{WSPACE}	{}
<<EOF>> { return EOF_;}
%%

void set_value() {
	int i = strlen(yytext) + 1;
	yylval.str = new char[i];
	strcpy(yylval.str, yytext);
}

void set_str_value() {
	int i = strlen(yytext) + 1 - 2;
	yylval.str = new char[i];
	yytext[strlen(yytext)-1] = '\0';
	strcpy(yylval.str, yytext + 1);
}
