#ifndef _ENGINERROR_H
#define _ENGINERROR_H
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <exception>

namespace engineErrorNS
{
	const int ENGINE_FATAL_ERROR = 400;
	const int ENGINE_INTERFACE_ERROR = 401;
	const int ENGINE_CORE_ERROR = 403;
	const int ENGINE_SYSTEM_MENU_ERROR = 404;
}

class EngineError : public std::exception
{
private:
	int			errorCode;
	std::string message;

public:
	// default constructor
	EngineError() throw() :errorCode(engineErrorNS::ENGINE_FATAL_ERROR), message("Undefined Error in EngineSystem.") {}

	// copy constructor
	EngineError(const EngineError& e) throw() : std::exception(e), errorCode(e.errorCode), message(e.message) {}

	// constructor with args
	EngineError(int code, const std::string &s) throw() :errorCode(code), message(s) {}

	// assignment operator
	EngineError& operator= (const EngineError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}
	// destructor
	virtual ~EngineError() throw() {};

	// override what from base class
	virtual const char* what() const throw() { return this->getMessage(); }

	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }
};

#endif // !_ENGINEERROR_H
