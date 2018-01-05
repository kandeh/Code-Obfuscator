#ifndef __obfuscator_H__

#define __obfuscator_H__

#include "ast.h"
ast_node* do_CFA(ast_node* tree);
ast_node* do_CFA_on_function(ast_node* fnode);
void flat_case(ast_node* st_id, int& st, ast_node* node, ast_node* control_while_lines);

#endif