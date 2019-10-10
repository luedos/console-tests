#include "NodeVariable.h"

using namespace bwn::calc_parser;

NodeVariable::NodeVariable(const Variable& value)
	: variable_{ value }
{
}

Variable NodeVariable::GetValue(Repository&) const
{
	return variable_;
}
