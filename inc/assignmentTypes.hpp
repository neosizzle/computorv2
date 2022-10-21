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
			float divResult;

			res.int_value = this->int_value / rhs.int_value;
			res.float_value = this->float_value / rhs.float_value;
			if (rhs.int_value % this->int_value == 0 && !rhs.is_float && !this->is_float)
				res.is_float = this->is_float || rhs.is_float;
			else
				res.is_float = true;
			
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
		bool operator > (RationalNumber rhs){return this->float_value > rhs.float_value;}
		bool operator < (RationalNumber rhs){return this->float_value < rhs.float_value;}
		bool operator >= (RationalNumber rhs){return this->float_value >= rhs.float_value;}
		bool operator == (RationalNumber rhs){return this->float_value == rhs.float_value;}
		bool operator != (RationalNumber rhs){return this->float_value != rhs.float_value;}

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
			this->is_float = true;
			this->int_value = x;
			this->float_value = x;
		}

		// assignment operators
		void	operator = (RationalNumber other)
		{
			this->is_float = other.is_float;
			this->int_value = other.int_value;
			this->float_value = other.float_value;
		}
		
};

class ImaginaryNumber : public BaseAssignmentType {
	public :
		RationalNumber imaginary_part;
		int			   power;

	public :
		std::string toString() {
			std::string res = imaginary_part.toString() + "i";

			if (power > 1) res += (std::string("^") + std::to_string(power)); 
			return res;
		}

		// operators
		// ImaginaryNumber +ImaginaryNumber 
		ImaginaryNumber operator + (ImaginaryNumber rhs)
		{
			ImaginaryNumber res;

			res.imaginary_part = rhs.imaginary_part + this->imaginary_part;

			return res;
		}

		// ImaginaryNumber -ImaginaryNumber 
		ImaginaryNumber operator - (ImaginaryNumber rhs)
		{
			ImaginaryNumber res;

			res.imaginary_part = this->imaginary_part - rhs.imaginary_part;
			return res;
		}

		// ImaginaryNumber *ImaginaryNumber 
		ImaginaryNumber operator * (ImaginaryNumber rhs)
		{
			ImaginaryNumber res;

			res.imaginary_part = rhs.imaginary_part * this->imaginary_part;
			res.power = this->power + rhs.power;
			return res;
		}

		// ImaginaryNumber /ImaginaryNumber 
		ImaginaryNumber operator / (ImaginaryNumber rhs)
		{
			ImaginaryNumber res;

			res.imaginary_part = this->imaginary_part / rhs.imaginary_part;
			res.power = this->power - rhs.power;
			
			return res;
		}

		// ImaginaryNumber ^ImaginaryNumber 
		ImaginaryNumber operator ^ (ImaginaryNumber rhs)
		{
			ImaginaryNumber res;

			res.imaginary_part = this->imaginary_part ^ rhs.imaginary_part;
			res.power = this->power + rhs.power;
			return res;
		}

		// comparison operators
		bool operator > (ImaginaryNumber rhs){return this->imaginary_part > rhs.imaginary_part;}
		bool operator < (ImaginaryNumber rhs){return this->imaginary_part < rhs.imaginary_part;}
		bool operator >= (ImaginaryNumber rhs){return this->imaginary_part >= rhs.imaginary_part;}
		bool operator == (ImaginaryNumber rhs){return this->imaginary_part == rhs.imaginary_part;}
		bool operator != (ImaginaryNumber rhs){return this->imaginary_part != rhs.imaginary_part;}

		// constructors
		ImaginaryNumber(){
			this->imaginary_part = RationalNumber(1);
			this->power = 1;
		}

		ImaginaryNumber(float x)
		{
			this->imaginary_part = RationalNumber(x);
			this->power = 1;
		}

		// assignment operators
		void	operator = (ImaginaryNumber other)
		{
			this->imaginary_part = other.imaginary_part;
			this->power = other.power;
		}
};

class Variable : public BaseAssignmentType {
	public:
		std::string	name;

		std::string toString(){return this->name;}

		//constructors
		Variable(){this->name = "";}

		Variable(std::string name){this->name = name;}
};