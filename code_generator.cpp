#include <vector>
#include <iostream>
#include "code_generator.h"

using namespace std;

void print_tabs(int tabs) {
	int tab_len = 3;
	for(int i = 0; i < tabs; i++) {
		for(int k = 0; k < tab_len; k++) {
			cout << " ";
		}
	}
}

void print_params(ast_node* pnode) {
	if(pnode == NULL) {
		return;
	}
	ast_node* ch;
	int len = pnode->childs.size();
	for(int i = 0; i < len; i++) {
		ch = pnode->childs[i];
		print_exp(ch);

		if(i < len - 1) {
			cout << ", ";
		}
	}
}

void print_indexes(ast_node* inode) {
	ast_node* ch;
	int len = inode->childs.size();
	for(int i = 0; i < len; i++) {
		ch = inode->childs[i];
		cout << "[";
		if(ch != NULL) {
			print_exp(ch);
		}
		cout << "]";
	}

}

void print_exp(ast_node* enode) {
	if(enode->type == node_type_int) {
		cout << enode->value;
		return;
	}
	if(enode->type == node_type_id) {
		cout << enode->id;
		return;
	}
	if(enode->type == node_type_array) {
		cout << enode->childs[0]->id;
		print_indexes(enode->childs[1]);
		return;
	}

	if(enode->type == node_type_string) {
		cout << "\"" << enode->str << "\"";
		return;
	}

	if(enode->type == node_type_exp) {
		string op = "";
		cout << "(";
		switch(enode->tag) {
			case op_equal:			print_exp(enode->childs[0]); cout << " == "; print_exp(enode->childs[1]); break;
			case op_not_equal:		print_exp(enode->childs[0]); cout << " != "; print_exp(enode->childs[1]); break;
			case op_less:			print_exp(enode->childs[0]); cout << " < "; print_exp(enode->childs[1]); break;
			case op_more:			print_exp(enode->childs[0]); cout << " > "; print_exp(enode->childs[1]); break;
			case op_plus:			print_exp(enode->childs[0]); cout << " + "; print_exp(enode->childs[1]); break;
			case op_minus:			print_exp(enode->childs[0]); cout << " - "; print_exp(enode->childs[1]); break;
			case op_divide:			print_exp(enode->childs[0]); cout << " / "; print_exp(enode->childs[1]); break;
			case op_star:			print_exp(enode->childs[0]); cout << " * "; print_exp(enode->childs[1]); break;
			case op_and:			print_exp(enode->childs[0]); cout << " && "; print_exp(enode->childs[1]); break;
			case op_or:				print_exp(enode->childs[0]); cout << " || "; print_exp(enode->childs[1]); break;
			case op_not:			cout << "!"; print_exp(enode->childs[0]); break;
			case op_address:		cout << "&"; print_exp(enode->childs[0]); break;
			case op_plus_plus:		print_exp(enode->childs[0]); cout << "++"; break;
			case op_minus_minus:	print_exp(enode->childs[0]); cout << "--"; break;
			case op_mod:			print_exp(enode->childs[0]); cout << " % "; print_exp(enode->childs[1]); break;
			case op_more_or_equal:	print_exp(enode->childs[0]); cout << " >= "; print_exp(enode->childs[1]); break;
			case op_less_or_equal:	print_exp(enode->childs[0]); cout << " <= "; print_exp(enode->childs[1]); break;

		}
		cout << ")";
		return;
	}

	if(enode->type == node_type_call) {
		cout << enode->childs[0]->id << "(";
		print_params(enode->childs[1]);
		cout << ")";
		return;
	}
}

void print_arr_init(ast_node* ainode) {
	ast_node* ch;
	int len = ainode->childs.size();
	cout << "{";
	for(int i = 0; i < len; i++) {
		ch = ainode->childs[i];
			print_exp(ch);
			if(i < len - 1) {
				cout << ", ";
			}
	}
	cout << "}";
}

void print_line(int tabs, ast_node* lnode) {
	if(lnode->type == node_type_return) {
		print_tabs(tabs);
		cout << "return ";
		print_exp(lnode->childs[0]);
		cout << ";" << endl;
		return;
	}
	if(lnode->type == node_type_var_def) {
		print_tabs(tabs);
		cout << "int ";
		cout << (lnode->childs[0]->id);
		if(lnode->childs[2] != NULL) {
			print_indexes(lnode->childs[2]);
		}
		if(lnode->childs[1] != NULL) {
			cout << " = ";
			if(lnode->childs[1]->type == node_type_inits_set) {
				print_arr_init(lnode->childs[1]);
			} else {
				print_exp(lnode->childs[1]);
			}
		}
		cout << ";" << endl;
		return;
	}

	if(lnode->type == node_type_if_block) {
		print_tabs(tabs);
		cout << "if(";
		print_exp(lnode->childs[0]);
		cout << ") {" << endl;
		print_lines(tabs + 1, lnode->childs[1]);
		print_tabs(tabs);
		cout << "}";

		if(lnode->childs[2] != NULL) {
			cout << " else {" << endl;
			print_lines(tabs + 1, lnode->childs[2]);
			print_tabs(tabs);
			cout << "}";
		}
		cout << endl;
		return;
	}

	if(lnode->type == node_type_for_block) {
		print_tabs(tabs);
		cout << "for(";
		print_exp(lnode->childs[0]);
		cout << " = ";
		print_exp(lnode->childs[1]);
		cout << "; ";
		print_exp(lnode->childs[2]);
		cout << "; ";
		print_exp(lnode->childs[3]);
		cout << ") {" << endl;
		print_lines(tabs + 1, lnode->childs[4]);
		print_tabs(tabs);
		cout << "}";
		cout << endl;
		return;
	}

	if(lnode->type == node_type_while_block) {
		print_tabs(tabs);
		cout << "while(";
		print_exp(lnode->childs[0]);
		cout << ") {" << endl;
		print_lines(tabs + 1, lnode->childs[1]);
		print_tabs(tabs);
		cout << "}";
		cout << endl;
		return;
	}

	if(lnode->type == node_type_break_line) {
		print_tabs(tabs);
		cout << "break;" << endl;
		return;
	}
	if(lnode->type == node_type_continue_line) {
		print_tabs(tabs);
		cout << "continue;" << endl;
		return;
	}
	if(lnode->type == node_type_call || lnode->type == node_type_exp) {
		print_tabs(tabs);
		print_exp(lnode);
		cout << ";" << endl;
		return;
	}
	if(lnode->type == node_type_assign || lnode->type == node_type_assign_array) {
		print_tabs(tabs);
		print_exp(lnode->childs[0]);
		cout << " = ";
		print_exp(lnode->childs[1]);
		cout << ";" << endl;
		return;
	}
}

void print_lines(int tabs, ast_node* lnode) {
	if(lnode == NULL) {
		return;
	}
	int len = lnode->childs.size();
	ast_node* ch;
	for(int i = 0; i < len; i++) {
		ch = lnode->childs[i];
		print_line(tabs, ch);
	}
	if(lnode->obf_change_st != NULL) {
		print_line(tabs, lnode->obf_change_st);
		print_line(tabs, new_node(node_type_continue_line, 0));
	}
}

void print_func(ast_node* fnode) {
	cout << endl;
	cout << "int " << fnode->childs[0]->id << "(";
	ast_node* ch;
	if(fnode->childs[1] != NULL) {
		int len = fnode->childs[1]->childs.size();
		for(int i = 0; i < len; i++) {
			ch = fnode->childs[1]->childs[i];
			cout << "int " << ch->childs[0]->id;
			if(i < len - 1) {
				cout << ", ";
			}
		}
	}
	cout << ") {" << endl;

	if(fnode->childs[2] != NULL) {
		print_lines(1, fnode->childs[2]);
	}

	cout << "}" << endl;
	cout << endl;
}

void print_program(ast_node* tree) {
	if(tree->type == node_type_func_def) {
		print_func(tree);
		return;
	}
	if(tree->type == node_type_var_def) {
		print_line(0, tree);
		return;
	}
	for(int i = 0; i < tree->childs.size(); i++) {
		if(tree->childs[i] != NULL) {
			print_program(tree->childs[i]);
		}
	}
}