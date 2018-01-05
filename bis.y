%token ID COMMA OPEN_PAR CLOSE_PAR IF FOR INTEGER ELSE EQUAL STAR PLUS MINUS DIVIDE END_BR BEGIN_BR RETURN ASSIGN BREAK AND
%token ADDRESS_AND CONTINUE MINUS_MINUS PLUS_PLUS MOD NOT OR SEMICOLON STRING_CONST NOTEQUAL LESS MORE LESS_OR_EQUAL MORE_OR_EQUAL WHILE INT_VAR_TYPE BEGIN_CU END_CU EOF_
%{

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void yyerror(char *msg);

extern int yylex();
extern int yyparse();
extern FILE* yyin;

%}

%union{
	char *str;
	struct ast_node *node;
	int d;
}

%type <str> INTEGER ID STRING_CONST
%type <node> for_block continue_line break_line inits_ inits init lines_ parameters parameter parameters_def while_block integer exp line lines program id block blocks var_def func_def end_line params param call return_line exp_line assign_line array string_const  if_block indexes index


%left OR
%left AND

%left EQUAL
%left NOTEQUAL

%left LESS
%left MORE
%left LESS_OR_EQUAL
%left MORE_OR_EQUAL




%left PLUS
%left MINUS
%left STAR
%left DIVIDE
%left MOD


%right NOT
%right ADDRESS_AND

%left PLUS_PLUS
%left MINUS_MINUS

%%

program: blocks { tree = $1; return NULL; };

blocks:   blocks block
		{

			$1->add_child($2);
			$$ = $1;
		}

		| block
		{

			$$ = new_node(node_type_blocks, 0);
			$$->add_child($1);
		};

block:	  var_def
		{
			$$ = $1;
		}

		| func_def
		{
			$$ = $1;
		};


var_def:  INT_VAR_TYPE id SEMICOLON
		{
			$$ = new_node(node_type_var_def, 0);
			$$->add_child($2);
			$$->add_child(NULL);
			$$->add_child(NULL);
		}
		| INT_VAR_TYPE id  ASSIGN exp SEMICOLON
		{
			$$ = new_node(node_type_var_def, 0);
			$$->add_child($2);
			$$->add_child($4);
			$$->add_child(NULL);
		}
		| INT_VAR_TYPE id indexes SEMICOLON
		{
			$$ = new_node(node_type_var_def, 0);
			$$->add_child($2);
			$$->add_child(NULL);
			$$->add_child($3);
		}
		| INT_VAR_TYPE id indexes ASSIGN inits SEMICOLON
		{
			$$ = new_node(node_type_var_def, 0);
			$$->add_child($2);
			$$->add_child($5);
			$$->add_child($3);
		};

func_def:
		  INT_VAR_TYPE id OPEN_PAR parameters_def CLOSE_PAR lines
		{

			$$ = new_node(node_type_func_def, 0);
			$$->add_child($2); // id
			$$->add_child($4); // parameters_def
			$$->add_child($6); // lines
		}
		| INT_VAR_TYPE id OPEN_PAR parameters_def CLOSE_PAR end_line
		{

			$$ = new_node(node_type_func_def, 0);
			$$->add_child($2); // id
			$$->add_child($4); // parameters_def
			$$->add_child(NULL); // lines
		};

parameters_def: parameters
		{
			$$ = $1;
		}
		|
		{
			$$ = NULL;
		};

parameters:	  parameters COMMA parameter
		{
			$$ = $1;
			$$->add_child($3);
		}
		| parameter
		{
			$$ = new_node(node_type_parameters, 0);
			$$->add_child($1);
		};




parameter:      INT_VAR_TYPE id
		{
			$$ = new_node(node_type_parameter, 0);
			$$->add_child($2);
		};

lines: BEGIN_CU lines_ END_CU
		{
			$$ = $2;
		}
		| BEGIN_CU END_CU
		{
			$$ = NULL;
	 	};

lines_: 	  lines_ line
		{
			$$ = $1;
			$$->add_child($2);
		}
		| line
		{
			$$ = new_node(node_type_lines, 0);
			$$->add_child($1);
		};

if_block: IF OPEN_PAR exp CLOSE_PAR lines
		{
			$$ = new_node(node_type_if_block, 0);
			$$->add_child($3); // exp
			$$->add_child($5); // lines
			$$->add_child(NULL); // else_lines
		}
		| IF OPEN_PAR exp CLOSE_PAR lines ELSE lines
		{
			$$ = new_node(node_type_if_block, 0);
			$$->add_child($3); // exp
			$$->add_child($5); // lines
			$$->add_child($7); // else_lines
		};
		
while_block: WHILE OPEN_PAR exp CLOSE_PAR lines
		{
			$$ = new_node(node_type_while_block, 0);
			$$->add_child($3); // exp
			$$->add_child($5); // lines
		};

for_block: FOR OPEN_PAR id ASSIGN exp SEMICOLON exp SEMICOLON exp CLOSE_PAR lines
		{
			$$ = new_node(node_type_for_block, 0);
			$$->add_child($3); // id
			$$->add_child($5); // exp
			$$->add_child($7); // exp
			$$->add_child($9); // exp
			$$->add_child($11); // lines
		};


line: 	  return_line {$$ = $1;}
		| break_line {$$ = $1;}
		| continue_line {$$ = $1;}
		| var_def {$$ = $1;}
		| exp_line {$$ = $1;}
		| assign_line {$$ = $1;}
		| if_block {$$ = $1;}
		| for_block {$$ = $1;}
		| while_block {$$ = $1;}
		| end_line {$$ == NULL; };


end_line: SEMICOLON
		{
			$$ = new_node(node_type_end_line, 0);
	 	};
		

return_line: RETURN exp end_line
		{
			$$ = new_node(node_type_return, 0);
			$$->add_child($2);
		};

exp_line: exp end_line
		{
			$$ = $1;
		};

break_line: BREAK end_line
		{
			$$ = new_node(node_type_break_line, 0);
		};

continue_line: CONTINUE end_line
		{
			$$ = new_node(node_type_continue_line, 0);
		};		
		

assign_line:
		  id ASSIGN exp end_line
		{
			$$ = new_node(node_type_assign, 0);
			$$->add_child($1);
			$$->add_child($3);
		}
		| array ASSIGN exp end_line
		{
			$$ = new_node(node_type_assign_array, 0);
			$$->add_child($1);
			$$->add_child($3);
		};



exp:   	   exp EQUAL   	exp {$$ = new_node(node_type_exp, op_equal); $$->add_child($1); $$->add_child($3);  }
		|  exp NOTEQUAL exp {$$ = new_node(node_type_exp, op_not_equal); $$->add_child($1); $$->add_child($3);  }
		|  exp LESS   	exp {$$ = new_node(node_type_exp, op_less); $$->add_child($1); $$->add_child($3);  }
		|  exp MORE     exp {$$ = new_node(node_type_exp, op_more); $$->add_child($1); $$->add_child($3);  }
		|  exp PLUS   exp {$$ = new_node(node_type_exp, op_plus); $$->add_child($1); $$->add_child($3);  }
		| exp MINUS  exp {$$ = new_node(node_type_exp, op_minus); $$->add_child($1); $$->add_child($3);  }
		| exp STAR   exp {$$ = new_node(node_type_exp, op_star); $$->add_child($1); $$->add_child($3);  }
		| exp DIVIDE exp {$$ = new_node(node_type_exp, op_divide); $$->add_child($1); $$->add_child($3);  }

		| exp OR exp {$$ = new_node(node_type_exp, op_or); $$->add_child($1); $$->add_child($3);  }
		| exp AND exp {$$ = new_node(node_type_exp, op_and); $$->add_child($1); $$->add_child($3);  }
		| exp MOD exp {$$ = new_node(node_type_exp, op_mod); $$->add_child($1); $$->add_child($3);  }

		| NOT exp {$$ = new_node(node_type_exp, op_not); $$->add_child($2); }

		| ADDRESS_AND exp {$$ = new_node(node_type_exp, op_address); $$->add_child($2); }

		| id PLUS_PLUS {$$ = new_node(node_type_exp, op_plus_plus); $$->add_child($1); }
		| id MINUS_MINUS {$$ = new_node(node_type_exp, op_minus_minus); $$->add_child($1); }

		| array PLUS_PLUS {$$ = new_node(node_type_exp, op_plus_plus); $$->add_child($1); }
		| array MINUS_MINUS {$$ = new_node(node_type_exp, op_minus_minus); $$->add_child($1); }

		| exp MORE_OR_EQUAL exp {$$ = new_node(node_type_exp, op_more_or_equal); $$->add_child($1); $$->add_child($3);  }
		| exp LESS_OR_EQUAL exp {$$ = new_node(node_type_exp, op_less_or_equal); $$->add_child($1); $$->add_child($3);  }

		| OPEN_PAR   exp CLOSE_PAR {$$ = $2;}
		| integer {$$ = $1;}
		| id {$$ = $1;}
		| call {$$ = $1;}
		| array {$$ = $1;}
		| string_const {$$ = $1;};

call: id OPEN_PAR params CLOSE_PAR
		{
			$$ = new_node(node_type_call, 0);
			$$->add_child($1);
			$$->add_child($3);
		};

array: id indexes
		{
			$$ = new_node(node_type_array, 0);
			$$->add_child($1);
			$$->add_child($2);
		};

indexes:  indexes index
		{
			$$ = $1;
			$$->add_child($2);
		}
		| index
		{
			$$ = new_node(node_type_indexes_set, 0);
			$$->add_child($1);
		};

index: BEGIN_BR exp END_BR
		{
			$$ = $2;
		}
		| BEGIN_BR END_BR
		{
			$$ = NULL;
		};

integer: INTEGER {
					$$ = new_node(node_type_int, atoi($1));
				 };


params:   params COMMA param
		{
			$$ = $1;
			$$->add_child($3);
		}
		| param
		{
			$$ = new_node(node_type_params_set, 0);
			$$->add_child($1);
		}
		| {$$ = NULL;};

param: exp
		{
			$$ = $1;
		};


inits:		BEGIN_CU inits_ END_CU
		{
			$$ = $2;
		}

inits_:   inits_ COMMA init
		{
			$$ = $1;
			$$->add_child($3);
		}
		| init
		{
			$$ = new_node(node_type_inits_set, 0);
			$$->add_child($1);
		};

init: exp
		{
			$$ = $1;
		};


id: ID
		{
			$$ = new_node(node_type_id, 0);
			$$->id = $1;
		};

string_const: STRING_CONST
		{
			$$ = new_node(node_type_string, 0);
			$$->str = $1;
		};

%%


void yyerror(char *msg) {
  printf("%s\n", msg);
  //system("pause");
  exit(1);
}
