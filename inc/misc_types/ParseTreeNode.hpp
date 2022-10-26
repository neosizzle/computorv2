#ifndef __PARSETREENODE__H__
#define __PARSETREENODE__H__

#include "Base.hpp"

class ParseTreeNode {
	public :
		ParseTreeNode *left;
		ParseTreeNode *right;
		ParseTreeNode *parent;
		BaseAssignmentType *value;

		std::string toString()
		{
			if (this->value != nullptr)
				return this->value->toString();
			else
				return "null";
		}

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