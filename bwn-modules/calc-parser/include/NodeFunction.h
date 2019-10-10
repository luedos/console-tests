#pragma once

#include "Node.h"

namespace bwn
{
namespace calc_parser
{

class NodeFunction
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeFunction(const std::string& name, const std::vector<std::shared_ptr<Node>>& arguments = {});

	//
	// Public interface.
	//
public:
	//! Returns representative value. 
	Variable GetValue(Repository& rep) const override;

	//
	// Private members.
	//
private:
	//! Name of the function from repository.
	std::string name_;
	//! Arguments needed to pass to the function.
	std::vector<std::shared_ptr<Node>> arguments_;
};

} // namespace calc_parser
} // namespace bwn