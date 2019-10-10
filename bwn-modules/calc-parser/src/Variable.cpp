#include "Exceptions.h"
#include "Variable.h"

using namespace bwn::calc_parser;

Variable::Variable(const std::string& name)
	: name_{ name }
{
}

Variable::Variable(const Value& value)
	: value_{ value }
{
}

bool Variable::IsLvalue() const
{
	return !name_.empty();
}

std::string Variable::AsName() const
{
	if (!IsLvalue()) {
		throw BadValue{ "Variable has no name" };
	}

	return name_;
}

Value Variable::AsValue() const
{
	if (IsLvalue()) {
		throw BadValue{ "Variable is not just a value" };
	}

	return value_;
}
