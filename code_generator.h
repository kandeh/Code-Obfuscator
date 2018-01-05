#ifndef __code_generator_H__

#define __code_generator_H__

#include "ast.h"

void print_program(ast_node* tree);
void print_func(ast_node* fnode);
void print_lines(int tabs, ast_node* lnode);
void print_line(int tabs, ast_node* lnode);
void print_arr_init(ast_node* ainode);
void print_exp(ast_node* enode);
void print_indexes(ast_node* inode);
void print_params(ast_node* pnode);
void print_tabs(int tabs);

#endif