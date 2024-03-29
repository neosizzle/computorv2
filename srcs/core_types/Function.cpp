#include "Function.hpp"
#include "constants.hpp"
#include "ParseTreeNode.hpp"
#include "QMark.hpp"
#include "Parenthesis.hpp"
#include "ft_error.hpp"
#include "RationalNum.hpp"
#include "ImaginaryNum.hpp"
#include "Matrix.hpp"
#include "Variable.hpp"
#include <algorithm>

std::string tokens_to_str(std::vector<BaseAssignmentType *>::iterator begin, std::vector<BaseAssignmentType *>::iterator end);
std::vector<BaseAssignmentType *> clone_tokens(std::vector<BaseAssignmentType *> tokens);
void	free_tokens(std::vector<BaseAssignmentType *> tokens);
void free_token(BaseAssignmentType * token);
void	free_tree(ParseTreeNode * curr);
BaseAssignmentType *clone_token(BaseAssignmentType * token);
void	token_preprocess(std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
ParseTreeNode *generate_parse_tree(std::vector<BaseAssignmentType *> tokens, bool is_compute_action);
BaseAssignmentType *evaluate_parse_tree(ParseTreeNode **head);
void	ft_perror(Ft_error e);
std::vector<std::string> ft_split(std::string str, std::vector<std::string> delims);
int derive_token_type(std::string str);

void print_parsed_tokens_no_format(std::vector<BaseAssignmentType *> tokens);

/**
 * Converts function class to string
*/
std::string Function::toString()
{
    if (tokens.size() < 1)
        return this->name + "(" + this->object->toString() + ")";
    return tokens_to_str(this->tokens.begin(), this->tokens.end());
}

BaseAssignmentType * Function::add(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Function::sub(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Function::mult(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Function::div(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Function::mod(BaseAssignmentType *rhs){(void) rhs; return nullptr;}
BaseAssignmentType * Function::pow(BaseAssignmentType *rhs){(void) rhs; return nullptr;}

/**
 * @brief extract func name from string
 * 
 * @param str 
 * @return std::string 
 */
std::string Function::_extract_name(std::string str)
{
    std::string res;
    std::size_t pos;

    // find the position of '('
    pos = str.find("(");

    // extract string from 0 to position '('
    res = str.substr(0, pos);
    return res;
}

/**
 * @brief extract Object BaseAss type from string
 * 
 * @param str 
 * @return BaseAssignmentType* 
 */
BaseAssignmentType * Function::_extract_object(std::string str)
{
    int         type;
    std::string token_str;
    std::size_t pos_lb;
    std::size_t pos_rb;

    // find the position of '(' and ')'
    pos_lb = str.find("(");
    pos_rb = str.find(")");
    token_str = str.substr(pos_lb + 1, pos_rb - pos_lb - 1);

    // derive the type of token
    type = derive_token_type(token_str);

    // create objects accordingly to type
    // for now, only accept rational and im numbers as objects
    if (type == N_RATIONAL)
        return new RationalNumber(float(atof(token_str.c_str())));
    if (type == N_IMAGINARY)
    {
        ImaginaryNumber *res_im;


        res_im = new ImaginaryNumber();
        // split the big string into 2 small strngs
        std::vector<std::string> tokens = ft_split(token_str, {"+", "-"});


        // only i
        if (tokens.size() == 1 && tokens[0] == "i")
        {
            res_im->imaginary_part = RationalNumber(1);
            res_im->real_part = RationalNumber(0);
        }        
        // determine which is the imaginary part [0] or [1]
        else if (tokens[0].find("i") != std::string::npos)
        {
            res_im->imaginary_part = RationalNumber(atoi(tokens[0].c_str()));
            if (tokens.size() != 1)
                res_im->real_part = RationalNumber(atoi(tokens[1].c_str()));
        }
        else
        {
            res_im->imaginary_part = RationalNumber(atoi(tokens[1].c_str()));
            res_im->real_part = RationalNumber(atoi(tokens[0].c_str()));
        }
        return res_im;
    }
    if (type == N_MATRIX)
        return new Matrix(token_str);
    if (type == VAR)
        return new Variable(token_str);
    return nullptr;
}
    

std::vector<BaseAssignmentType *> Function::get_tokens()
{
    std::vector<BaseAssignmentType *> res;

    // clone tokens and replace var with object token if needed
    for (size_t i = 0; i < this->tokens.size(); i++)
    {
        if (this->object->getType() == VAR && this->tokens[i]->getType() == VAR)
            res.push_back(clone_token(this->object));
        else
            res.push_back(clone_token(this->tokens[i]));
        
    }
    
    return res;
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

std::string  Function::get_name()
{
    return this->name;
}

void    Function::set_name(std::string new_name)
{
    this->name = new_name;
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

            // free old token
            free_token(curr_token);

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
        ft_perror(e);

        // free
        free_tree(root);
        free_tokens(tokens_cloned);
        return nullptr;
    }
}

Function::~Function() {
    free_token(this->object);
    free_tokens(this->tokens);
    this->type = FUNC;
}

Function::Function(std::vector<BaseAssignmentType *> tokens, std::string name)
{
    this->name = name;
    this->set_tokens(tokens);
    this->object = nullptr;
    this->type = FUNC;
}

Function::Function(std::vector<BaseAssignmentType *> tokens, BaseAssignmentType *object, std::string name)
{
    this->name = name;
    this->set_tokens(tokens);
    this->object = clone_token(object);
    this->type = FUNC;
}

Function::Function(std::string str)
{
    std::string name;
    BaseAssignmentType *object;

    // extract name
    name = this->_extract_name(str);
    this->name = name;

    // extract object
    object = this->_extract_object(str);
    this->object = object;

    this->type = FUNC;
}


Function::Function(const Function &other)
{
    this->set_tokens(other.tokens);
    this->object = clone_token(other.object);
    this->name = other.name;
    this->type = FUNC;
}

Function &Function::operator=(const Function &other)
{
    this->tokens = other.tokens;
    this->object = other.object;
    this->name = other.name;
    this->type = FUNC;
    return *this;
}
