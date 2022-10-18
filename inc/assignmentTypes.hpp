#include "libraries.hpp"

class BaseAssignmentType {
	public :
		virtual std::string toString() = 0;
};

class RationalNumber : public BaseAssignmentType {
	public :
		
		bool	is_float;
		int		int_value;
		float 	float_value;

		std::string toString() {
			return is_float ? std::to_string(float_value) : std::to_string(int_value);
		}

		// operators
		// RationalNumber + RationalNumber
		RationalNumber operator + (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value + rhs.int_value;
			res.float_value = this->float_value + rhs.float_value;
			return res;
		}

		// RationalNumber - RationalNumber
		RationalNumber operator - (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value - rhs.int_value;
			res.float_value = this->float_value - rhs.float_value;
			return res;
		}

		// RationalNumber * RationalNumber
		RationalNumber operator * (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value * rhs.int_value;
			res.float_value = this->float_value *  rhs.float_value;
			return res;
		}

		// RationalNumber / RationalNumber
		RationalNumber operator / (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value / rhs.int_value;
			res.float_value = this->float_value / rhs.float_value;
			return res;
		}

		// RationalNumber % RationalNumber
		RationalNumber operator % (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value % rhs.int_value;
			res.float_value = this->int_value;
			return res;
		}

		// RationalNumber ^ RationalNumber
		RationalNumber operator ^ (RationalNumber rhs)
		{
			RationalNumber res;

			res.is_float = this->is_float || rhs.is_float;
			res.int_value = this->int_value % rhs.int_value;
			res.float_value = this->int_value;
			return res;
		}

		// comparison operators
		

		// constructors
		RationalNumber(){
			this->is_float = false;
			this->int_value = 0;
			this->float_value = 0;
		}

		RationalNumber(int x)
		{
			this->is_float = false;
			this->int_value = x;
			this->float_value = x;
		}

		RationalNumber(float x)
		{
			this->is_float = false;
			this->int_value = x;
			this->float_value = x;
		}
};

class ImaginaryNumber : public BaseAssignmentType {
	public :
		std::string toString() {
			return "imagine";
		}
};