#include "Exceptions.h"

using namespace bwn::calc_parser;

ParserException::ParserException(const std::string& message, size_t statement) noexcept
	: std::runtime_error{ message }
	, statement_{ statement }
{
}

size_t ParserException::GetStatementNumber() const noexcept
{
	return statement_;
}

BadToken::BadToken(const std::string& message, size_t token_type, size_t statement) noexcept
	: ParserException{ message, statement }
	, token_type_{ token_type }
{
}

size_t BadToken::GetTokenType() const noexcept
{
	return token_type_;
}

