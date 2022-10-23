#ifndef __PARSETREENODE__H__
#define __PARSETREENODE__H__

#include "Base.hpp"

class ParseTreeNode {
	public :
		ParseTreeNode *left;
		ParseTreeNode *right;
		ParseTreeNode *parent;
		BaseAssignmentType *value;

		ParseTreeNode()
		{
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			this->value = nullptr;
		}

		ParseTreeNode(BaseAssignmentType *value)
		{
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			this->value = value;
		}
};

#endif  //!__PARSETREENODE__H__