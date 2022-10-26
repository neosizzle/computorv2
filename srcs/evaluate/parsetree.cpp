#include "main.hpp"

ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action)
{
	ParseTreeNode *head;
	ParseTreeNode *curr;
	std::vector<BaseAssignmentType *>::iterator start_iter;
	std::vector<BaseAssignmentType *>::iterator end_iter;

	// determine start and end iter
	start_iter = determine_start_iter(tokens, is_compute_action);
	end_iter = determine_end_iter(tokens, is_compute_action);
	
	// initializa tree
	head = new ParseTreeNode();
	curr = head;

	print_parsed_tokens_no_format(tokens);
	// loop through all tokens
	while (start_iter < end_iter)
	{
		if (start_iter == tokens.end()) break;

		BaseAssignmentType * curr_token;
		curr_token = *start_iter;
		// '(' - add left child and change curr node to left child
		if (curr_token->getType() == L_PARENTHESIS)
		{
			curr->left = new ParseTreeNode();
			curr->left->parent = curr;
			curr = curr->left;
		}

		// ')' - set curr node to parent
		else if (curr_token->getType() == R_PARENTHESIS)
			curr = curr->parent;

		// operator - set value of currnode and add right child and change currnode to right child
		else if (is_operator(curr_token))
		{
			curr->value = clone_token(curr_token);
			curr->right = new ParseTreeNode();
			curr->right->parent = curr;
			curr = curr->right;
		}
		// operand - set val of curr node and change currnode to parent
		else
		{
			curr->value = clone_token(curr_token);
			curr = curr->parent;
		}
		start_iter++;
	}
	// print_parsed_tokens_no_format(tokens);
	print_tree(head);
	// std::cout << head->toString() << "\n";
	// head->left = new ParseTreeNode(clone_token(*(start_iter + 1)));
	// std::cout << head->left->toString() << "\n";
	return head;
}