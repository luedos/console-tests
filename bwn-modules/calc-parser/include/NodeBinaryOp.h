#pragma once

#include "Node.h"
#include "Variable.h"
#include "Exceptions.h"

#include <functional>
#include <memory>

namespace bwn
{
namespace calc_parser
{

template<typename T, T ptr>
class NodeBinaryOp
{
	static_assert(sizeof(T) != sizeof(T), "Incorrect function is passed for BinaryOp Node");
};

template<Value(*Function)(const Value&, const Value&)>
class NodeBinaryOp<Value(*)(const Value&, const Value&), Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeBinaryOp(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

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
	//! Left node for operation.
	std::shared_ptr<Node> left_;
	//! Right node for operation.
	std::shared_ptr<Node> right_;
};

template<Value(*Function)(const Value&, const Value&)>
NodeBinaryOp<Value(*)(const Value&, const Value&), Function>::NodeBinaryOp(std::shared_ptr<Node> left, std::shared_ptr<Node> right)
	: left_{ left }
	, right_{ right }
{
	if (!left_) {
		throw BadExecutionTree{ "Invalid left operand for binary operation node was passed." };
	}
	if (!right_) {
		throw BadExecutionTree{ "Invalid right operand for binary operation node was passed." };
	}

}

template<Value(*Function)(const Value&, const Value&)>
Variable NodeBinaryOp<Value(*)(const Value&, const Value&), Function>::GetValue(Repository& rep) const
{
	Value left_value;
	Value right_value;

	{
		Variable var = left_->GetValue(rep);
		if (var.IsLvalue()) {
			left_value = rep.GetVariable(var.AsName());
		}
		else {
			left_value = var.AsValue();
		}
		var = right_->GetValue(rep);
		if (var.IsLvalue()) {
			right_value = rep.GetVariable(var.AsName());
		}
		else {
			right_value = var.AsValue();
		}
	}

	return Function(left_value, right_value);
}


template<Value&(Value::*Function)(const Value&)>
class NodeBinaryOp<Value&(Value::*)(const Value&), Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeBinaryOp(std::shared_ptr<Node> left, std::shared_ptr<Node> right);

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
	//! Left node for operation.
	std::shared_ptr<Node> left_;
	//! Right node for operation.
	std::shared_ptr<Node> right_;
};

template<Value&(Value::*Function)(const Value&)>
NodeBinaryOp<Value&(Value::*)(const Value&), Function>::NodeBinaryOp(std::shared_ptr<Node> left, std::shared_ptr<Node> right)
	: left_{ left }
	, right_{ right }
{
	if (!left_) {
		throw BadExecutionTree{ "Invalid left operand for binary operation node was passed." };
	}
	if (!right_) {
		throw BadExecutionTree{ "Invalid right operand for binary operation node was passed." };
	}

}
template<Value&(Value::*Function)(const Value&)>
Variable NodeBinaryOp<Value&(Value::*)(const Value&), Function>::GetValue(Repository& rep) const
{
	Variable left_variable;
	Value right_value;

	{
		left_variable = left_->GetValue(rep);
		if (!left_variable.IsLvalue()) {
			throw BadExecutionTree{ "Expected an lvalue." };
		}

		Variable var = right_->GetValue(rep);
		if (var.IsLvalue()) {
			right_value = rep.GetVariable(var.AsName());
		}
		else {
			right_value = var.AsValue();
		}
	}

	{
		Value temp;

		{
			std::string temp_str = left_variable.AsName();

			if (rep.IsVariableExist(temp_str)) {
				temp = rep.GetVariable(temp_str);
			}
		}

		//std::invoke(Function, temp, right_value);
		(temp.*Function)(right_value);
		rep.SetVariable(left_variable.AsName(), temp);
	}
	
	return left_variable;
}

} // namespace calc_parser
} // namespace bwn