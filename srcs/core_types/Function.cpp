#include "Function.hpp"
#include "constants.hpp"
#include "ParseTreeNode.hpp"
#include "QMark.hpp"
#include "Parenthesis.hpp"
#include "ft_error.hpp"
#include <algorithm>

std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end);
std::vector<BaseAssignmentType *> clone_tokens(std::vector<BaseAssignmentType *> tokens);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void free_token(BaseAssignmentType * token);
void	free_tree(ParseTreeNode * curr);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head);
void	ft_perror(Ft_error e);

void print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);

std::string Function::toString()
{
    return tokens_to_str(this->tokens.begin(), this->tokens.end());
}

BaseAssignmentType * Function::add(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Function::sub(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Function::mult(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Function::div(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Function::mod(BaseAssignmentType *rhs){return nullptr;}
BaseAssignmentType * Function::pow(BaseAssignmentType *rhs){return nullptr;}

std::vector<BaseAssignmentType *> Function::get_tokens()
{
    return this->tokens;
}

void Function::set_tokens(std::vector<BaseAssignmentType *>tokens)
{
    free_tokens(this->tokens);
    this->tokens = clone_tokens(tokens);
}

BaseAssignmentType * Function::get_object()
{
    return this->object;
}

void    Function::set_object(BaseAssignmentType *object)
{
    if (this->object != nullptr)
        free_token(this->object);
    this->object = clone_token(object);
}

BaseAssignmentType * Function::evaluate_image()
{
    std::vector<BaseAssignmentType *> tokens_cloned;
    std::vector<BaseAssignmentType *>::iterator tokens_iter;
    BaseAssignmentType *res;
    ParseTreeNode *root;

    // check for null object or variable object;
    if (this->object == nullptr || this->object->getType() == VAR)
        return nullptr;

    // clone tokens
    tokens_cloned = clone_tokens(tokens);

    // add qmark to cloned tokens to simulate compute action
    tokens_cloned.push_back(new QMark());

    // replace all variables with object
    tokens_iter = tokens_cloned.begin();
    for (;tokens_iter != tokens_cloned.end();++tokens_iter)
    {
        BaseAssignmentType * curr_token = *tokens_iter;

        // if curr token is a variable
        if (curr_token->getType() == VAR)
        {
            // clone new token
            BaseAssignmentType *new_token = clone_token(this->object);

            // replace var with cloned token
            std::replace(tokens_cloned.begin(), tokens_cloned.end(), curr_token, new_token);

            // free old token and break loop
            free_token(curr_token);

            break ;
        }   
    }


    try
    {
        // preprocess tokens 
        token_preprocess(tokens_cloned, 1);

        // generate parse tree
        root = generate_parse_tree(tokens_cloned, 1);

        // evaulate parse tree
        res = clone_token(evaluate_parse_tree(&root));

        // free
        free_tree(root);
        free_tokens(tokens_cloned);

        // return result
        return res;
    }
    catch(Ft_error &e)
    {
        ft_perror(e.getMessage());
        return nullptr;
    }
}


Function::~Function() {
    free_token(this->object);
    free_tokens(this->tokens);
}

Function::Function(std::vector<BaseAssignmentType *> tokens)
{
    this->set_tokens(tokens);
    this->object = nullptr;
}

Function::Function(std::vector<BaseAssignmentType *> tokens, BaseAssignmentType *object)
{
    this->set_tokens(tokens);
    this->object = clone_token(object);
}

Function::Function(const Function &other)
{
    this->set_tokens(other.tokens);
    this->object = clone_token(other.object);
}

Function &Function::operator=(const Function &other)
{
    this->tokens = other.tokens;
    this->object = other.object;
    return *this;
}
