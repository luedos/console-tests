#include "Token.h"
#include "Exceptions.h"
#include "Utilits.h"

#include <algorithm>
#include <cstring>
#include <cctype>

using namespace bwn::calc_parser;

bwn::calc_parser::Token::Token(TokenType type, const Value& val)
	: value_{ val }
	, type_{ type }
{
}

std::vector<Token> Token::ParseTokens(const std::string& code)
{
	std::vector<Token> out;
	out.reserve(10);

	using CheckerFunction = void(*)(Token&, std::string::const_iterator& it, std::string::const_iterator end);

	const CheckerFunction functions[] = {
		&Token::ParseAsLiteral,
		&Token::ParseAsName,
		&Token::ParseAsOperator,
		&Token::ParseAsSpecSymbol };

	constexpr size_t functions_size = sizeof(functions) / sizeof(decltype(functions[0]));

	Token temp_token(TokenType(0), Value());

	for (auto it = code.begin(); it != code.end();)
	{
		if (std::isspace(*it))
		{
			++it;
			continue;
		}

		auto test = it;

		for (size_t i = 0; i < functions_size && it == test; ++i) {
			functions[i](temp_token, it, code.end());
		}

		if (it == test) 
		{
			while (test != code.end() && !std::isspace(*test)) {
				++test;
			}
			throw BadToken{ ("Unknown token \"" + std::string(it, test) + "\"").data(), 0 };
		}

		out.push_back(std::move(temp_token));
	}

	return out;
}

bwn::calc_parser::Token::TokenType Token::GetType() const
{
	return type_;
}

bwn::calc_parser::Value Token::GetValue() const
{
	if (type_ != PRVALUE) {
		throw BadToken{ "Failed returning value from token.", size_t(type_) };
	}
	return value_;
}

std::string Token::GetName() const
{
	if (type_ != LVALUE) {
		throw BadToken{ "Failed returning name from token.", size_t(type_) };
	}
	return value_.AsString();
}

void Token::ParseAsName(Token& token, std::string::const_iterator& it, std::string::const_iterator end)
{
	if (it == end || !(std::isalpha(*it) || *it == '_')) {
		return;
	}

	auto start_it = it;

	while (it != end && (std::isalnum(*it) || *it == '_')) {
		++it;
	}

	token = Token(Token::LVALUE, std::string(start_it, it));
}

void Token::ParseAsLiteral(Token& token, std::string::const_iterator& it, std::string::const_iterator end)
{
	if (it == end) {
		return;
	}

	const size_t max_length = std::distance(it, end);

	// Check for BOOL/NULL
	if (std::isalpha(*it))
	{
		const char* string_test;
		switch (*it)
		{
		case 'f':
			string_test = "false";
			break;
		case 't':
			string_test = "true";
			break;
		case 'N':
			string_test = "NULL";
			break;
		default:
			return;
		}

		if (max_length < std::strlen(string_test)) {
			return;
		}

		auto temp_it = it;

		while (*string_test) 
		{
			if (*temp_it != *string_test) {
				return;
			}
			++temp_it;
			++string_test;
		}

		if (temp_it != end && (std::isalnum(*temp_it) || *temp_it == '_')) {
			return;
		}

		switch (*it)
		{
		case 'f':
			string_test = "false";
			token = Token(Token::PRVALUE, Value(false));
			break;
		case 't':
			string_test = "true";
			token = Token(Token::PRVALUE, Value(true));
			break;
		case 'N':
			string_test = "NULL";
			token = Token(Token::PRVALUE, Value());
			break;
		}

		it = temp_it;
		return;
	} // Check for BOOL/NULL

	// Check for string
	if (*it == '\"')
	{
		auto temp_it = it + 1;
		for (; temp_it != end; ++temp_it)
		{
			if (*temp_it == '\"' && *(temp_it - 1) != '\\') {
				break;
			}
		}

		if (temp_it == end) {
			return;
		}

		token = Token(Token::PRVALUE, std::string(it + 1, temp_it));
		it = temp_it + 1;
		return;
	} // Check for string

	// Check for number
	if (std::isdigit(*it))
	{
		auto temp_it = it + 1;

		if (max_length > 2 && *it == '0' && *temp_it != '.')
		{
			long long int int_number = 0;

			if (*temp_it == 'x')
			{
				++temp_it;
				
				while (temp_it != end && std::isxdigit(*temp_it)) {
					++temp_it;
				}

				if (std::distance(it, temp_it) > 18) {
					throw BadToken("Number of digits in hex value is too big, try use double", TokenType::PRVALUE);
				}

				try
				{
					int_number = std::stoll(std::string(it, temp_it), nullptr, 16);
				}
				catch (const std::exception&) 
				{
					return;
				}
			}
			else if (std::isdigit(*temp_it))
			{
				while (temp_it != end && std::isdigit(*temp_it)) {
					++temp_it;
				}

				if (std::distance(it, temp_it) > 33) {
					throw BadToken("Number of digits in oct value is too big, try use double", TokenType::PRVALUE);
				}
				
				try
				{
					int_number = std::stoll(std::string(it, temp_it), nullptr, 8);
				}
				catch (const std::exception&) 
				{
					return;
				}
			}

			token = Token(Token::PRVALUE, Value(int_number));
			it = temp_it;
			return;
		}

		bool as_double = false;

		for (; temp_it != end; ++temp_it)
		{
			if (*temp_it == '.') 
			{
				if (as_double) {
					return;
				}
				else {
					as_double = true;
				}
			}
			else if (!std::isdigit(*temp_it)) {
				break;
			}
		}
		
		if (std::distance(temp_it, end) > 1 && (*temp_it == 'e' || *temp_it == 'E'))
		{
			auto test_it = temp_it + 1;

			if (*test_it == '-' || *test_it == '+') {
				++test_it;
			}

			if (test_it != end && std::isdigit(*test_it))
			{
				temp_it = test_it + 1;
				while (temp_it != end && std::isdigit(*temp_it)) {
					++temp_it;
				}

				as_double = true;
			}
		}

		if (!as_double)
		{
			const size_t num_count = std::distance(it, temp_it);

			if (num_count > (sizeof("18446744073709551615") - 1)) {
				as_double = true;
			}
			else if (num_count == (sizeof("18446744073709551615") - 1))
			{
				const char* max_uint = "18446744073709551615";

				for (auto test_it = it; test_it != temp_it && max_uint; ++test_it, ++max_uint)
				{
					if (*max_uint > *test_it) {
						break;
					}

					if (*max_uint < *test_it) 
					{
						as_double = true;
						break;
					}
				}
			}
		}

		if (as_double)
		{
			double number;

			try
			{
				number = std::stod(std::string(it, temp_it));
			}
			catch (const std::exception&) 
			{
				return;
			}

			token = Token(Token::PRVALUE, Value(number));
			it = temp_it;
			return;
		}

		long long int int_number;

		try
		{
			int_number = std::stoull(std::string(it, temp_it));
		}
		catch (const std::exception&)
		{
			return;
		}

		token = Token(Token::PRVALUE, Value(int_number));
		it = temp_it;
		return;
	} // Check for number
}

void Token::ParseAsOperator(Token& token, std::string::const_iterator& it, std::string::const_iterator end)
{
	if (it == end || !std::strchr("+-*/%=&|^!<>?:,", *it)) {
		return;
	}

	const size_t max_length = std::distance(it, end);
	TokenType type = TokenType(0);
	size_t it_adder = 0;

	if (max_length > 1)
	{
		if (*(it + 1) == '=' && std::strchr("+-*/%=&|^!<>", *it))
		{
			switch (*it)
			{
			case '+':
				type = OP_ADD_EQUAL;
				break;
			case '-':
				type = OP_SUB_EQUAL;
				break;
			case '*':
				type = OP_MUL_EQUAL;
				break;
			case '/':
				type = OP_DIV_EQUAL;
				break;
			case '%':
				type = OP_MOD_EQUAL;
				break;
			case '=':
				type = OP_LOGIC_E;
				break;
			case '&':
				type = OP_AND_EQUAL;
				break;
			case '|':
				type = OP_OR_EQUAL;
				break;
			case '^':
				type = OP_XOR_EQUAL;
				break;
			case '!':
				type = OP_LOGIC_NE;
				break;
			case '<':
				type = OP_LOGIC_LE;
				break;
			case '>':
				type = OP_LOGIC_GE;
				break;

			default:
				return;
			}

			it_adder += 2;
		}
		else if (*it == *(it + 1) && std::strchr("+-&|<>", *it))
		{
			switch (*it)
			{
			case '+':
				type = OP_PLUSPLUS;
				break;
			case '-':
				type = OP_MINUSMINUS;
				break;
			case '&':
				type = OP_LOGIC_AND;
				break;
			case '|':
				type = OP_LOGIC_OR;
				break;
			case '<':
				if (max_length > 2 && *(it + 2) == '=') 
				{
					type = OP_LSH_EQUAL;
					it_adder += 1;
				}
				else
				{
					type = OP_LSH;
				}
				break;
			case '>':
				if (max_length > 2 && *(it + 2) == '=')
				{
					type = OP_RSH_EQUAL;
					it_adder += 1;
				}
				else
				{
					type = OP_RSH;
				}
				break;
			default:
				return;
			}

			it_adder += 2;
		}
	}

	if (it_adder)
	{
		token = Token(type, Value());
		it += it_adder;
		return;
	}

	switch (*it)
	{
	case '+':
		type = OP_ADD;
		break;
	case '-':
		type = OP_SUB;
		break;
	case '*':
		type = OP_MUL;
		break;
	case '/':
		type = OP_DIV;
		break;
	case '%':
		type = OP_MOD;
		break;
	case '=':
		type = OP_EQUAL;
		break;
	case '&':
		type = OP_AND;
		break;
	case '|':
		type = OP_OR;
		break;
	case '^':
		type = OP_XOR;
		break;
	case '!':
		type = OP_NOT;
		break;
	case '<':
		type = OP_LOGIC_L;
		break;
	case '>':
		type = OP_LOGIC_G;
		break;
	case '?':
		type = OP_IF;
		break;
	case ':':
		type = OP_ELSE;
		break;
	case ',':
		type = OP_COMA;
		break;
	default:
		return;
	}

	token = Token(type, Value());
	++it;	
}

void Token::ParseAsSpecSymbol(Token& token, std::string::const_iterator& it, std::string::const_iterator end)
{
	if (it == end) {
		return;
	}

	switch (*it)
	{
	case '(':
		token = Token(Token::OPENING_BRACKET, Value());
		break;
	case ')':
		token = Token(Token::CLOSING_BRACKET, Value());
		break;
	default:
		return;
	}

	++it;
}
