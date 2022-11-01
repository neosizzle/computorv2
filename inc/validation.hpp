#ifndef __VALIDATION__H__
#define __VALIDATION__H__

#include <algorithm>

#include "tokens.hpp"
#include "Base.hpp"
#include "constants.hpp"
#include "ft_error.hpp"

// utils
bool is_eq(BaseAssignmentType* token);
bool is_operator(BaseAssignmentType* token);


#endif  //!__VALIDATION__H__