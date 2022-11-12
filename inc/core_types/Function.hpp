#ifndef __FUNCTION__H__
#define __FUNCTION__H__
#include "Base.hpp"
#include <vector>

class Function : public BaseAssignmentType
{
    private:
        std::vector<BaseAssignmentType *> tokens;
        BaseAssignmentType *object;

    public:
        std::string toString();

        // operator shell functions
        BaseAssignmentType * add (BaseAssignmentType *rhs);
        BaseAssignmentType * sub (BaseAssignmentType *rhs);
        BaseAssignmentType * mult (BaseAssignmentType *rhs);
        BaseAssignmentType * div (BaseAssignmentType *rhs);
        BaseAssignmentType * mod (BaseAssignmentType *rhs);
        BaseAssignmentType * pow (BaseAssignmentType *rhs);

        std::vector<BaseAssignmentType *> get_tokens();
        void set_tokens(std::vector<BaseAssignmentType *> new_tokens);

        BaseAssignmentType *get_object();
        void set_object(BaseAssignmentType *new_object);

        BaseAssignmentType *evaluate_image();

        ~Function();
        Function(std::vector<BaseAssignmentType *> tokens);
        Function(std::vector<BaseAssignmentType *> tokens, BaseAssignmentType *object);
        Function(const Function &other);

        Function &operator=(const Function &other);

};

#endif  //!__FUNCTION__H__ 