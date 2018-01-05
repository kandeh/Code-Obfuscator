#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include "ast.h"

using namespace std;

ast_node *tree;

void ast_node::add_child(ast_node* node) {
	childs.push_back(node);
}

ast_node* set_st_(ast_node* st_id, int st) {
	ast_node* tmp;
	tmp = new_node(node_type_assign, 0);
	tmp->add_child(st_id);
	tmp->add_child(new_node(node_type_int, st));
	return tmp;
}

void ast_node::set_obf_next_st(ast_node* st_id, int next_st) {
	obf_change_st = set_st_(st_id, next_st);
}

void ast_node::set_obf_break_continue_st(int break_st, int continue_st) {
	continue_next_st = continue_st;
	break_next_st = break_st;
}

void ast_node::set_obf_next_st(ast_node* line) {
	obf_change_st = line;
}

ast_node* new_node(int type, long long int tag) {
	ast_node* res;
	res = new ast_node;
	res->type = type;
	res->tag = tag;
	if(type == node_type_int)
	{
		res->value = tag;
	}
	if(type == node_type_exp)
	{
		res->op = tag;
	}
	res->obf_change_st = NULL;
	res->break_next_st = -1;
	res->continue_next_st = -1;
	return res;
}

