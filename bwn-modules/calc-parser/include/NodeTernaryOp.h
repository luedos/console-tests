#pragma once

#include "Node.h"
#include "Variable.h"
#include "Exceptions.h"
#include "Utilits.h"

#include <functional>
#include <memory>

namespace bwn
{
namespace calc_parser
{

template<Variable(*Function)(const Value&, const Variable&, const Variable&)>
class NodeTernaryOp
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeTernaryOp(std::shared_ptr<Node> first, std::shared_ptr<Node> second, std::shared_ptr<Node> third);

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
	//! First node for operation.
	std::shared_ptr<Node> first_;
	//! Second node for operation.
	std::shared_ptr<Node> second_;
	//! Third node for operation.
	std::shared_ptr<Node> third_;
};


template<Variable(*Function)(const Value&, const Variable&, const Variable&)>
inline NodeTernaryOp<Function>::NodeTernaryOp(
	std::shared_ptr<Node> first, 
	std::shared_ptr<Node> second, 
	std::shared_ptr<Node> third)
	: first_{ first }
	, second_{ second }
	, third_{ third }
{
	if (!first_) {
		throw BadExecutionTree{ "Invalid CONDITION operand for ternary operation node was passed." };
	}
	if (!second_) {
		throw BadExecutionTree{ "Invalid IF operand for ternary operation node was passed." };
	}
	if (!third_) {
		throw BadExecutionTree{ "Invalid ELSE operand for ternary operation node was passed." };
	}

}

template<Variable(*Function)(const Value&, const Variable&, const Variable&)>
inline Variable NodeTernaryOp<Function>::GetValue(Repository& rep) const
{
	Value first_value;
	Variable second_variable = second_->GetValue(rep);
	Variable third_variable = third_->GetValue(rep);

	{
		Variable var = first_->GetValue(rep);
		if (var.IsLvalue()) {
			first_value = rep.GetVariable(var.AsName());
		}
		else {
			first_value = var.AsValue();
		}
	}

	return bwn::invoke(Function, first_value, second_variable, third_variable);
}

} // namespace calc_parser
} // namespace bw