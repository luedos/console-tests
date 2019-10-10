#pragma once

#include <stdexcept>
#include <string>

namespace bwn
{
namespace calc_parser
{

class ParserException : public std::runtime_error
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	ParserException(const std::string& message, size_t statement = 0) noexcept;

	//
	// Public interface.
	//
public:
	//! Returns line on which exception ocured.
	size_t GetStatementNumber() const noexcept;

	//
	// Private members.
	//
private:
	//! Line of the exception.
	size_t statement_;
};

class BadToken : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadToken(const std::string& message, size_t token_type, size_t statement = 0) noexcept;

	//
	// Public interface.
	//
public:
	//! Returns token type.
	size_t GetTokenType() const noexcept;

	//
	// Private members.
	//
private:
	//! Type of the token.
	size_t token_type_;
};

class BadValue : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadValue(const std::string& message, size_t statement = 0)
		: ParserException{ message , statement }
	{
	}
};

class BadConversion : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadConversion(const std::string& message, size_t statement = 0)
		: ParserException{ message, statement }
	{
	}
};

class BadOperation : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadOperation(const std::string& message, size_t statement = 0)
		: ParserException{ message, statement }
	{
	}
};

class BadFunction : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadFunction(const std::string& message, size_t statement = 0)
		: ParserException{ message, statement }
	{
	}
};

class BadExecutionTree : public ParserException
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	BadExecutionTree(const std::string& message, size_t statement = 0)
		: ParserException{ message, statement }
	{
	}
};
}
}