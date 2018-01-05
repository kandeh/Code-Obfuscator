#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include "ast.h"

void flat_case(ast_node* control_variable_id, int& state_couner, ast_node* node, ast_node* control_while_lines) {
	ast_node* case_then_lines;
	ast_node* first_line;
	ast_node* if_;
	ast_node* if_lines;
	ast_node* if_condition;

	again:

	case_then_lines = node->childs[1];
	first_line = case_then_lines->childs[0];

	if(first_line->type == node_type_break_line) {
		if(case_then_lines->childs.size() > 1) {
			ast_node* if_ = new_node(node_type_if_block, 0);
			ast_node* if_condition = new_node(node_type_exp, op_equal);
			ast_node* if_lines = new_node(node_type_lines, 0);
			if_condition->add_child(control_variable_id);
			if_condition->add_child(new_node(node_type_int, state_couner));
			if_->add_child(if_condition);
			state_couner++;
			control_while_lines->add_child(if_);
			if_->add_child(if_lines);
			if_->add_child(NULL);
			for(int i = 1; i < case_then_lines->childs.size(); i++) {
				if_lines->add_child(case_then_lines->childs[i]);
			}
			
			if_lines->set_obf_next_st(case_then_lines->obf_change_st);
			case_then_lines->set_obf_next_st(control_variable_id, state_couner - 1);
		}
		case_then_lines->childs.erase(case_then_lines->childs.begin() + 0, case_then_lines->childs.end());
		case_then_lines->set_obf_next_st(control_variable_id, case_then_lines->break_next_st);


	} else if(first_line->type == node_type_continue_line) {
		if(case_then_lines->childs.size() > 1) {
			ast_node* if_ = new_node(node_type_if_block, 0);
			ast_node* if_condition = new_node(node_type_exp, op_equal);
			ast_node* if_lines = new_node(node_type_lines, 0);
			if_condition->add_child(control_variable_id);
			if_condition->add_child(new_node(node_type_int, state_couner));
			if_->add_child(if_condition);
			state_couner++;
			control_while_lines->add_child(if_);
			if_->add_child(if_lines);
			if_->add_child(NULL);
			for(int i = 1; i < case_then_lines->childs.size(); i++) {
				if_lines->add_child(case_then_lines->childs[i]);
			}
			if_lines->set_obf_next_st(case_then_lines->obf_change_st);
			case_then_lines->set_obf_next_st(control_variable_id, state_couner - 1);
		}
		case_then_lines->childs.erase(case_then_lines->childs.begin() + 0, case_then_lines->childs.end());
		case_then_lines->set_obf_next_st(control_variable_id, case_then_lines->continue_next_st);


	} else if(first_line->type == node_type_if_block && first_line->childs[1] != NULL) {
		if(case_then_lines->childs.size() > 1) {
			ast_node* if_ = new_node(node_type_if_block, 0);
			ast_node* if_condition = new_node(node_type_exp, op_equal);
			ast_node* if_lines = new_node(node_type_lines, 0);
			if_condition->add_child(control_variable_id);
			if_condition->add_child(new_node(node_type_int, state_couner));
			if_->add_child(if_condition);
			state_couner++;
			control_while_lines->add_child(if_);
			if_->add_child(if_lines);
			if_->add_child(NULL);
			for(int i = 1; i < case_then_lines->childs.size(); i++) {
				if_lines->add_child(case_then_lines->childs[i]);
			}
			case_then_lines->childs.erase(case_then_lines->childs.begin() + 1, case_then_lines->childs.end());
			if_lines->set_obf_next_st(case_then_lines->obf_change_st);
			if_lines->set_obf_break_continue_st(case_then_lines->break_next_st, case_then_lines->continue_next_st);

			case_then_lines->set_obf_next_st(control_variable_id, state_couner - 1);
		}

		ast_node* if_ = new_node(node_type_if_block, 0);
		ast_node* if_condition = new_node(node_type_exp, op_equal);
		ast_node* if_lines = new_node(node_type_lines, 0);
		if_condition->add_child(control_variable_id);
		if_condition->add_child(new_node(node_type_int, state_couner));
		if_->add_child(if_condition);
		state_couner++;
		control_while_lines->add_child(if_);
		if_->add_child(if_lines);
		if_->add_child(NULL);
		for(int i = 0; i < first_line->childs[1]->childs.size(); i++) {
			if_lines->add_child(first_line->childs[1]->childs[i]);
		}
		if_lines->set_obf_next_st(case_then_lines->obf_change_st);
		if_lines->set_obf_break_continue_st(case_then_lines->break_next_st, case_then_lines->continue_next_st);

		first_line->childs[1]->childs.clear();
		first_line->childs[1]->set_obf_next_st(control_variable_id, state_couner - 1);


		if(first_line->childs[2] != NULL) {
			ast_node* if_ = new_node(node_type_if_block, 0);
			ast_node* if_condition = new_node(node_type_exp, op_equal);
			ast_node* if_lines = new_node(node_type_lines, 0);
			if_condition->add_child(control_variable_id);
			if_condition->add_child(new_node(node_type_int, state_couner));
			if_->add_child(if_condition);
			state_couner++;
			control_while_lines->add_child(if_);
			if_->add_child(if_lines);
			if_->add_child(NULL);

			for(int i = 0; i < first_line->childs[2]->childs.size(); i++) {
				if_lines->add_child(first_line->childs[2]->childs[i]);
			}
			if_lines->set_obf_next_st(case_then_lines->obf_change_st);
			if_lines->set_obf_break_continue_st(case_then_lines->break_next_st, case_then_lines->continue_next_st);

			first_line->childs[2]->childs.clear();
			first_line->childs[2]->set_obf_next_st(control_variable_id, state_couner - 1);

		}

	} else if(first_line->type == node_type_while_block && first_line->childs[1] != NULL) {
		if(case_then_lines->childs.size() > 1) {
			ast_node* if_ = new_node(node_type_if_block, 0);
			ast_node* if_condition = new_node(node_type_exp, op_equal);
			ast_node* if_lines = new_node(node_type_lines, 0);
			if_condition->add_child(control_variable_id);
			if_condition->add_child(new_node(node_type_int, state_couner));
			if_->add_child(if_condition);
			state_couner++;
			control_while_lines->add_child(if_);
			if_->add_child(if_lines);
			if_->add_child(NULL);
			for(int i = 1; i < case_then_lines->childs.size(); i++) {
				if_lines->add_child(case_then_lines->childs[i]);
			}
			case_then_lines->childs.erase(case_then_lines->childs.begin() + 1, case_then_lines->childs.end());
			if_lines->set_obf_next_st(case_then_lines->obf_change_st);
			if_lines->set_obf_break_continue_st(case_then_lines->break_next_st, case_then_lines->continue_next_st);

			case_then_lines->set_obf_next_st(control_variable_id, state_couner - 1);
		}

		ast_node* if_ = new_node(node_type_if_block, 0);
		ast_node* if_condition = new_node(node_type_exp, op_equal);
		ast_node* if_lines = new_node(node_type_lines, 0);
		if_condition->add_child(control_variable_id);
		if_condition->add_child(new_node(node_type_int, state_couner));
		if_->add_child(if_condition);
		state_couner++;
		control_while_lines->add_child(if_);
		if_->add_child(if_lines);
		if_->add_child(NULL);
		for(int i = 0; i < first_line->childs[1]->childs.size(); i++) {
			if_lines->add_child(first_line->childs[1]->childs[i]);
		}
		if_lines->set_obf_next_st(control_variable_id, node->childs[0]->childs[1]->value);
		
		if_lines->set_obf_break_continue_st(case_then_lines->obf_change_st->childs[1]->value, node->childs[0]->childs[1]->value);

		first_line->childs[1]->childs.clear();
		first_line->childs[1]->set_obf_next_st(control_variable_id, state_couner - 1);
		first_line->type = node_type_if_block;
		first_line->add_child(NULL); // else

	} else if(first_line->type == node_type_for_block && first_line->childs[1] != NULL) {
		ast_node* assign;
		ast_node* lines;
		assign = new_node(node_type_assign, 0);
		assign->add_child(first_line->childs[0]);
		assign->add_child(first_line->childs[1]);
		case_then_lines->childs.insert(case_then_lines->childs.begin(), assign);
		first_line->type = node_type_while_block;
		lines = first_line->childs[4];
		lines->add_child(first_line->childs[3]);
		first_line->childs.erase(first_line->childs.begin(), first_line->childs.begin() + 2);
		first_line->childs.erase(first_line->childs.begin() + 1);
		first_line->add_child(NULL);
		goto again;

	} else {
		for(int i = 0; i < case_then_lines->childs.size(); i++) {
			if(((case_then_lines->childs[i]->type == node_type_for_block
					|| case_then_lines->childs[i]->type == node_type_if_block
					|| case_then_lines->childs[i]->type == node_type_while_block)
					&& case_then_lines->childs[i]->childs[1] != NULL)
					|| (case_then_lines->childs[i]->type == node_type_break_line
					|| case_then_lines->childs[i]->type == node_type_continue_line)) {
				ast_node* if_ = new_node(node_type_if_block, 0);
				ast_node* if_condition = new_node(node_type_exp, op_equal);
				ast_node* if_lines = new_node(node_type_lines, 0);
				if_condition->add_child(control_variable_id);
				if_condition->add_child(new_node(node_type_int, state_couner++));
				if_->add_child(if_condition);
				control_while_lines->add_child(if_);
				if_->add_child(if_lines);
				if_->add_child(NULL);
				for(int j = i; j < case_then_lines->childs.size(); j++) {
					if_lines->add_child(case_then_lines->childs[j]);
				}
				case_then_lines->childs.erase(case_then_lines->childs.begin() + i, case_then_lines->childs.end());
				if_lines->set_obf_next_st(case_then_lines->obf_change_st);
				case_then_lines->set_obf_next_st(control_variable_id, state_couner - 1);
				if_lines->set_obf_break_continue_st(case_then_lines->break_next_st, case_then_lines->continue_next_st);
				break;
			}
		}
	}
}

ast_node* do_CFA_on_function(ast_node* fnode) {
	int state_couner = 1;
	ast_node* ch;
	ast_node* otree = new_node(node_type_func_def, 0);
	ast_node* olines = new_node(node_type_lines, 0);

	otree->add_child(fnode->childs[0]); // id
	otree->add_child(fnode->childs[1]); // parameters_def
	otree->add_child(olines); // lines

	int len = fnode->childs[2]->childs.size();
	for(int i = 0; i < len; i++) {
		ch = fnode->childs[2]->childs[i];
		if(ch->type == node_type_var_def) {
			olines->add_child(ch);
		}
	}
	ast_node* control_variable_id = new_node(node_type_id, 0);
	control_variable_id->id = new char[10];
	
	strcpy(control_variable_id->id, "__st__");

	ast_node* control_while = new_node(node_type_while_block, 0);
	ast_node* control_while_lines = new_node(node_type_lines, 0);

	control_while->add_child(control_variable_id);
	control_while->add_child(control_while_lines);

	ast_node* tmp;
	tmp = new_node(node_type_var_def, 0);
	tmp->add_child(control_variable_id);
	tmp->add_child(new_node(node_type_int, state_couner));
	tmp->add_child(NULL);
	olines->add_child(tmp);
	olines->add_child(control_while);

	
	ast_node* if_ = new_node(node_type_if_block, 0);
	ast_node* if_condition = new_node(node_type_exp, op_equal);
	ast_node* if_lines = new_node(node_type_lines, 0);
	if_condition->add_child(control_variable_id);
	if_condition->add_child(new_node(node_type_int, state_couner));
	if_->add_child(if_condition);
	state_couner++;
	control_while_lines->add_child(if_);
	if_->add_child(if_lines);
	if_->add_child(NULL);
	for(int i = 0; i < len; i++) {
		ch = fnode->childs[2]->childs[i];
		if(ch->type == node_type_var_def) {
			continue;
		}
		if_lines->add_child(ch);
	}
	
	if_lines->set_obf_next_st(control_variable_id, 0);

	for(int i = 0; i < control_while_lines->childs.size(); i++) {
		ch = control_while_lines->childs[i];
		if(ch->type == node_type_if_block) {
			flat_case(control_variable_id, state_couner, ch, control_while_lines);
		}
		
	}
	return otree;
}

ast_node* do_CFA(ast_node* tree) {
	for(int i = 0; i < tree->childs.size(); i++) {
		if(tree->childs[i]->type == node_type_func_def) {
			tree->childs[i] = do_CFA_on_function(tree->childs[i]);
		}
	}
}