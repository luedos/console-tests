#pragma once

#include "Node.h"

namespace bwn
{
namespace calc_parser
{

class NodeSequence
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeSequence(const std::vector<std::shared_ptr<Node>>& nodes);

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
	//! Nodes to run.
	std::vector<std::shared_ptr<Node>> nodes_;
};

} // namespace calc_parser
} // namespace bwn