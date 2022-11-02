#ifndef __FT_ERROR__H__
#define __FT_ERROR__H__
# include <iostream>
# include "constants.hpp"

class Ft_error {
	private:
		std::string message;
		int			code;

	public:

		int getCode(){return this->code;}
		std::string getMessage(){return this->message;}

		// constructor
		Ft_error(){
			this->message = "OK";
			this->code = FT_ERR_OK;
		}
		Ft_error(std::string msg, int code){
			this->message = msg;
			this->code = code;
		}
		Ft_error(std::string msg){
			this->message = msg;
			this->code = FT_ERR_MISC;
		}

		Ft_error(const Ft_error &e)
		{
			this->code = e.code;
			this->message = e.message;
		}

		// operator overloads
		friend std::ostream &operator<<(std::ostream &output, const Ft_error &err)
		{
			output << err.message;
			return output;
		}
};
#endif  //!__FT_ERROR__H__
