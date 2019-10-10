#pragma once

#include "Value.h"

namespace bwn
{
namespace calc_parser
{

class Variable
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Variable() = default;
	//! Constructor.
	Variable(const std::string& name);
	//! Constructor.
	Variable(const Value& value);

	//
	// Public interface.
	//
public:
	//! Returns true if variable has a name.
	bool IsLvalue() const;
	//! Returns variable name;
	std::string AsName() const;
	//! Returns variable value.
	Value AsValue() const;

	//
	// Private members.
	//
private:
	//! Name of the variable.
	std::string name_;
	//! Value of the variable.
	Value value_ = {};
};

} // namespace calc_parser
} // namespace bwn
