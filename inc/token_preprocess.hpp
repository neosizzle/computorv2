#ifndef __TOKEN_PREPROCESS__H__
#define __TOKEN_PREPROCESS__H__

#include <vector>
#include <algorithm>

#include "Base.hpp"
#include "constants.hpp"
#include "Parenthesis.hpp"

// utils
bool is_operator(BaseAssignmentType* token);
std::vector<BaseAssignmentType *>::iterator determine_start_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);
std::vector<BaseAssignmentType *>::iterator determine_end_iter (std::vector<BaseAssignmentType *> &tokens, bool is_compute_action);

#endif  //!__TOKEN_PREPROCESS__H__