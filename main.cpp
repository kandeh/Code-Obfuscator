#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "y.tab.h"
#include "ast.h"
#include "code_generator.h"
#include "obfuscator.h"

using namespace std;

extern FILE* yyin;
extern int yyparse (void);

int main()
{
	freopen("output.html", "w", stdout);
	
	yyin = fopen("input.txt","r");
	yyparse();
	
	
	cout << "<pre> <div style=\"padding: 10px; float:left;\">";
	cout << "<h1> input </h1>";
	print_program(tree);
	cout << "</div>";
	
	
	do_CFA(tree);
	
	
	cout << "<div style=\"border-left: thick double #141f1f; padding: 10px; float:left;\">";
	cout << "<h1> control flow obfuscated </h1>";
	print_program(tree);
	cout << "</div> </pre>";
	
	return 0;
}
