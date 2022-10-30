#ifndef __TOKENS__H__
#define __TOKENS__H__
#include "libraries.hpp"
#include "assignmentTypes.hpp"

class TokenBase {
	public :
		int 		type;
		std::string string;
};

template<class T>
class TokenParsed {

	// private attribs
	private :
		int	type;
		T	value;

	// public methods
	public:
		int		getType(){return this->type;}
		T		getValue(){return this->value;}
		void	setValue(T value){this->value = value;}
		void	setType(int type){this->type = type;}

		TokenParsed(T initValue, int type){
			this->value = initValue;
			this->type = type;
		}
};
#endif  //!__TOKENS__H__
