#include "main.hpp"

/**
 * @brief Generates a parse tree using the list of tokens provided
 * 
 * @param tokens 
 * @param is_compute_action 
 * @return ParseTreeNode* 
 */
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
	// print_tree(head);
	return head;
}

// ADD TYPE
/**
 * @brief Commences the operation betweem two tokens and returns new result in allocated memory
 * 
 * @param lhs 
 * @param rhs 
 * @param operation 
 * @return BaseAssignmentType* 
 */
BaseAssignmentType * do_op(BaseAssignmentType *lhs, BaseAssignmentType *rhs, int operation)
{
	BaseAssignmentType *res;

	res = nullptr;
	if (operation == OPERATOR_PLUS)
		res = lhs->add(rhs);
	else if (operation == OPERATOR_MINUS)
		res = lhs->sub(rhs);
	else if (operation == OPERATOR_MULT)
		res = lhs->mult(rhs);
	else if (operation == OPERATOR_DIV)
		res = lhs->div(rhs);
	else if (operation == OPERATOR_MOD)
		res = lhs->mod(rhs);
	else if (operation == OPERATOR_POW)
		res = lhs->pow(rhs);

	return res;
}

void	replace_node(ParseTreeNode **curr, BaseAssignmentType *token)
{
	// create new parse tree node 
	ParseTreeNode *new_tree_node;
	ParseTreeNode *temp;

	// set new tree node links
	new_tree_node = new ParseTreeNode(token);
	new_tree_node->parent = (*curr)->parent;
	if ((*curr)->parent != nullptr)
	{
		if ((*curr) == (*curr)->parent->left)
		{
			temp = ((*curr)->parent->left);
			(*curr)->parent->left = new_tree_node;
			free_tree(temp);
		}
		else if ((*curr) == (*curr)->parent->right)
		{
			temp = ((*curr)->parent->right);
			(*curr)->parent->right = new_tree_node;
			free_tree(temp);
		}

		// set curr to newly replaced node
		*curr = new_tree_node;
	}
	else
	{
		// free original current subtree
		temp = *curr;

		// set head to new node
		*curr = new_tree_node;
		free_tree(temp);
	}
}

void	evaluate_parse_tree_helper(ParseTreeNode **curr)
{
	// if curr node is null or curr node is leaf, return
	if (*curr == nullptr || is_leaf_node(*curr))
		return ;

	// traverse left
	evaluate_parse_tree_helper(&((*curr)->left));

	// traverse right
	evaluate_parse_tree_helper(&((*curr)->right));

	// if curr node have only 1 children, replace curr node wiht only child (L_PARENTHESIS)
	if ((*curr)->left != nullptr && (*curr)->right == nullptr)
	{
		replace_node(curr, clone_token((*curr)->left->value));
	}
	else if ((*curr)->left == nullptr && (*curr)->right != nullptr)
		replace_node(curr, clone_token((*curr)->right->value));

	// if both children are leaf, evaluate and subsitute curr node
	else if ((*curr)->left != nullptr && (*curr)->right != nullptr && is_leaf_node((*curr)->left) && is_leaf_node((*curr)->right))
	{
		// obtain new result
		BaseAssignmentType *res_token = do_op((*curr)->left->value, (*curr)->right->value, (*curr)->value->getType());

		// throw error if operation is not valid
		if (res_token == nullptr) throw Ft_error("Operation not valid");

		//reaplce node
		// ft_pinfo((*curr)->parent->left->toString());
		replace_node(curr, res_token);
		// ft_pinfo((*curr)->parent->left->toString());
	}

	// return 
}

BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head)
{
	print_tree(*head);
	evaluate_parse_tree_helper(head);

	// print_tree(*head);
	ft_pinfo((*head)->toString());
}