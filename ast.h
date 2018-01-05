#ifndef __ast_H__

#define __ast_H__

#include <vector>

#define node_type_exp						1
#define node_type_int						2
#define node_type_blocks					4
#define node_type_func_def					5
#define node_type_global_var_def			6
#define node_type_parameter					7
#define node_type_parameters				8
#define node_type_lines						9
#define node_type_line_return				10
#define node_type_call						11
#define node_type_params_set				12
#define node_type_param						13
#define node_type_id						14
#define node_type_end_line					15
#define node_type_var_def					16
#define node_type_return					17
#define node_type_assign					18
#define node_type_assign_array				19
#define node_type_array						20
#define node_type_string					21
#define node_type_for_block					22
#define node_type_if_block					23
#define node_type_indexes_set				24
#define node_type_index						25
#define node_type_while_block				26
#define node_type_inits_set					27
#define node_type_switch_block				28
#define node_type_break_line				29
#define node_type_continue_line				30

#define op_plus			1
#define op_minus		2
#define op_star			3
#define op_divide		4
#define op_equal		5
#define op_not_equal	6
#define op_less			7
#define op_more			8

#define op_less_or_equal		9
#define op_more_or_equal		10

#define op_or			11
#define op_and			12
#define op_mod			13
#define op_not			14

#define op_plus_plus	15
#define op_minus_minus	16

#define op_address		17

#define line_type_return 	600
#define line_type_assign	700
#define line_type_def		800
#define line_type_exp		900


struct ast_node {
	std::vector<ast_node*> childs;

	int type;
	int op;
	long long int value;
	char *str;
	char *id;
	long long int tag;
	void add_child(ast_node* node);
	void print();
	void print_obfuscated();
	void set_obf_next_st(ast_node* st_id, int next_st);
	void set_obf_next_st(ast_node* line);
	void set_obf_break_continue_st(int break_st, int continue_st);

	ast_node* obf_change_st;
	int continue_next_st;
	int break_next_st;
};

extern ast_node *tree;

ast_node* new_node(int type, long long int tag);

#endif