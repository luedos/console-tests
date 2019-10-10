#pragma once

#include <string>
#include <vector>

#include "Value.h"

namespace bwn
{
namespace calc_parser
{

class Token
{
	//
	// Public classes.
	//
public:
	enum TokenType
	{
		LVALUE				= 0x0001,
		PRVALUE				= 0x0002,

		OPENING_BRACKET		= 0x0004,
		CLOSING_BRACKET		= 0x0008,

		OP_EQUAL			= 0x0010,
		OP_ADD_EQUAL		= 0x0020,
		OP_SUB_EQUAL		= 0x0030,
		OP_MUL_EQUAL		= 0x0040,
		OP_DIV_EQUAL		= 0x0050,
		OP_MOD_EQUAL		= 0x0060,
		OP_AND_EQUAL		= 0x0070,
		OP_OR_EQUAL			= 0x0080,
		OP_XOR_EQUAL		= 0x0090,
		OP_LSH_EQUAL 		= 0x00a0,
		OP_RSH_EQUAL 		= 0x00b0,
		U_OP_LVALUE = OP_EQUAL | OP_ADD_EQUAL | OP_SUB_EQUAL | OP_MUL_EQUAL | OP_DIV_EQUAL | OP_MOD_EQUAL | OP_AND_EQUAL | OP_OR_EQUAL | OP_XOR_EQUAL | OP_LSH_EQUAL | OP_RSH_EQUAL,

		OP_MUL				= 0x0100,
		OP_DIV				= 0x0200,
		OP_MOD				= 0x0300,
		OP_LSH				= 0x0400,
		OP_RSH				= 0x0500,
		U_OP_HIGH_RVALUE = OP_MUL | OP_DIV | OP_MOD,

		OP_ADD				= 0x1000,
		OP_SUB				= 0x2000,
		OP_AND				= 0x4000,
		OP_OR				= 0x8000,
		OP_XOR				= 0xb000,
		U_OP_LOW_RVALUE = OP_ADD | OP_SUB | OP_AND | OP_OR | OP_XOR,

		OP_LOGIC_E			= 0x00010000,
		OP_LOGIC_NE			= 0x00020000,
		OP_LOGIC_L			= 0x00030000,
		OP_LOGIC_G			= 0x00040000,
		OP_LOGIC_LE			= 0x00050000,
		OP_LOGIC_GE			= 0x00060000,
		U_OP_HIGH_LOGIC = OP_LOGIC_E | OP_LOGIC_NE | OP_LOGIC_L | OP_LOGIC_G | OP_LOGIC_LE | OP_LOGIC_GE,

		OP_LOGIC_AND		= 0x00100000,
		OP_LOGIC_OR			= 0x00200000,
		U_OP_LOW_LOGIC = OP_LOGIC_AND | OP_LOGIC_OR,

		OP_NOT				= 0x00400000,
		U_OP_UNARY = OP_NOT | OP_ADD | OP_SUB,

		OP_PLUSPLUS			= 0x00800000,
		OP_MINUSMINUS		= 0x01000000,
		U_OP_ITERATORS = OP_PLUSPLUS | OP_MINUSMINUS,

		OP_IF				= 0x02000000,
		OP_ELSE				= 0x04000000,
		U_OP_TERNARY = OP_IF | OP_ELSE,

		OP_COMA				= 0x08000000,


		U_ANY_OPERATOR			= U_OP_LVALUE | U_OP_ITERATORS | U_OP_HIGH_RVALUE | U_OP_LOW_RVALUE | U_OP_UNARY | U_OP_HIGH_LOGIC | U_OP_LOW_LOGIC | U_OP_TERNARY | OP_COMA,
		U_ANY_VALUE			= LVALUE | PRVALUE,
		U_ANY_BRACKET		= OPENING_BRACKET | CLOSING_BRACKET
	};

	//
	// Construction and destruction.
	//
private:
	//! Constructor.
	Token(TokenType type, const Value& val);

	//
	// Public interface.
	//
public:
	//! Creates token from the string.
	static std::vector<Token> ParseTokens(const std::string& code);
	//! Returns token type.
	TokenType GetType() const;
	//! Returns value if token type is PRVALUE.
	Value GetValue() const;
	//! Returns name if token type is LVALUE.
	std::string GetName() const;

	//
	// Private methods.
	//
private:
	//! Iterates iterator till ending of value name.
	static void ParseAsName(Token& token, std::string::const_iterator& it, std::string::const_iterator end);
	//! If bracket iterates iterator once.
	static void ParseAsLiteral(Token& token, std::string::const_iterator& it, std::string::const_iterator end);
	//! Iterates iterator till ending of operator.
	static void ParseAsOperator(Token& token, std::string::const_iterator& it, std::string::const_iterator end);
	//! If bracket iterates iterator once.
	static void ParseAsSpecSymbol(Token& token, std::string::const_iterator& it, std::string::const_iterator end);


	//
	// Private members.
	//
private:
	//! Token value.
	Value value_;
	//! Type of tocken.
	TokenType type_;
};

} // namespace calc_parser
} // namespace bwn