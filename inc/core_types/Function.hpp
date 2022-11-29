#ifndef __FUNCTION__H__
#define __FUNCTION__H__
#include "Base.hpp"
#include <vector>

class Function : public BaseAssignmentType
{
    private:
        std::vector<BaseAssignmentType *> tokens;
        BaseAssignmentType *object;
        std::string name;

        // extract func name from string
        std::string _extract_name(std::string str);

        // extract Object BaseAss type from string
        BaseAssignmentType *_extract_object(std::string str);

    public:
        std::string toString();

        // operator shell functions
        BaseAssignmentType * add (BaseAssignmentType *rhs);
        BaseAssignmentType * sub (BaseAssignmentType *rhs);
        BaseAssignmentType * mult (BaseAssignmentType *rhs);
        BaseAssignmentType * div (BaseAssignmentType *rhs);
        BaseAssignmentType * mod (BaseAssignmentType *rhs);
        BaseAssignmentType * pow (BaseAssignmentType *rhs);

		// getter and setter
        std::vector<BaseAssignmentType *> get_tokens();
        void set_tokens(std::vector<BaseAssignmentType *> new_tokens);

        BaseAssignmentType *get_object();
        void set_object(BaseAssignmentType *new_object);

        std::string get_name();
        void set_name(std::string new_name);

        BaseAssignmentType *evaluate_image();

        // constructos
        ~Function();
        Function(std::vector<BaseAssignmentType *> tokens, std::string name);
        Function(std::vector<BaseAssignmentType *> tokens, BaseAssignmentType *object, std::string name);
        Function(std::string str);
        Function(const Function &other);

        Function &operator=(const Function &other);

};

#endif  //!__FUNCTION__H__ 