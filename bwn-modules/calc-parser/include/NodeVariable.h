#pragma once

#include "Node.h"
#include "Variable.h"

namespace bwn
{
namespace calc_parser
{

class NodeVariable
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeVariable(const Variable& value);

	//
	// Public interface.
	//
public:
	//! Returns representative value. 
	Variable GetValue(Repository&) const override;

	//
	// Private members.
	//
private:
	//! Variable.
	Variable variable_;
};

} // namespace calc_parser
} // namespace bwn