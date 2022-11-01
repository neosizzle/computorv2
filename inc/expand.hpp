#ifndef __EXPAND__H__
#define __EXPAND__H__

#include <algorithm>

#include "tokens.hpp"
#include "Base.hpp"
#include "constants.hpp"
#include "ft_error.hpp"
#include "Variable.hpp"

// utils
std::string ft_tolower(std::string str);
BaseAssignmentType *clone_token(BaseAssignmentType * token);

// memory
void free_token(BaseAssignmentType * token);

#endif  //!__EXPAND__H__