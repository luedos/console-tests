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
template<typename T, T Function>
class NodeUnaryOp
{
	static_assert(sizeof(T) != sizeof(T), "Incorrect function is passed for UnaryOp Node");
};

template<Value(*Function)(const Value&)>
class NodeUnaryOp<Value(*)(const Value&), Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeUnaryOp(std::shared_ptr<Node> node);

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
	//! Node for operation.
	std::shared_ptr<Node> node_;

};

template<Value(*Function)(const Value&)>
NodeUnaryOp<Value(*)(const Value&), Function>::NodeUnaryOp(std::shared_ptr<Node> node)
	: node_{ node }
{
}

template<Value(*Function)(const Value&)>
Variable NodeUnaryOp<Value(*)(const Value&), Function>::GetValue(Repository& rep) const
{
	Value value;

	{
		Variable var = node_->GetValue(rep);
		if (var.IsLvalue()) {
			value = rep.GetVariable(var.AsName());
		}
		else {
			value = var.AsValue();
		}
	}
	
	return Function(value);
}

template<Value(Value::*Function)() const>
class NodeUnaryOp<Value(Value::*)() const, Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeUnaryOp(std::shared_ptr<Node> node);

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
	//! Node for operation.
	std::shared_ptr<Node> node_;

};

template<Value(Value::*Function)() const>
NodeUnaryOp<Value(Value::*)() const, Function>::NodeUnaryOp(std::shared_ptr<Node> node)
	: node_{ node }
{
}

template<Value(Value::*Function)() const>
Variable NodeUnaryOp<Value(Value::*)() const, Function>::GetValue(Repository& rep) const
{
	Value value;

	{
		Variable var = node_->GetValue(rep);
		if (var.IsLvalue()) {
			value = rep.GetVariable(var.AsName());
		}
		else {
			value = var.AsValue();
		}
	}

	return (value.*Function)();
		//bwn::invoke(Function, value);
}

template<Value(*Function)(Value&, int)>
class NodeUnaryOp<Value(*)(Value&, int), Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeUnaryOp(std::shared_ptr<Node> node);

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
	//! Node for operation.
	std::shared_ptr<Node> node_;

};

template<Value(*Function)(Value&, int)>
NodeUnaryOp<Value(*)(Value&, int), Function>::NodeUnaryOp(std::shared_ptr<Node> node)
	: node_{ node }
{
}

template<Value(*Function)(Value&, int)>
Variable NodeUnaryOp<Value(*)(Value&, int), Function>::GetValue(Repository& rep) const
{
	Value value;

	Variable var = node_->GetValue(rep);
	if (var.IsLvalue()) {
		value = rep.GetVariable(var.AsName());
	}
	else {
		throw BadExecutionTree{ "Expected an lvalue." };
	}

	Value ret = Function(value, 0);

	rep.SetVariable(var.AsName(), value);

	return ret;
}

template<Value&(*Function)(Value&)>
class NodeUnaryOp<Value&(*)(Value&), Function>
	: public Node
{
	//
	// Construction and destrction.
	//
public:
	//! Constructor.
	NodeUnaryOp(std::shared_ptr<Node> node);

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
	//! Node for operation.
	std::shared_ptr<Node> node_;

};

template<Value&(*Function)(Value&)>
NodeUnaryOp<Value&(*)(Value&), Function>::NodeUnaryOp(std::shared_ptr<Node> node)
	: node_{ node }
{
}

template<Value&(*Function)(Value&)>
Variable NodeUnaryOp<Value&(*)(Value&), Function>::GetValue(Repository& rep) const
{
	Value value;

	Variable var = node_->GetValue(rep);
	if (var.IsLvalue()) {
		value = rep.GetVariable(var.AsName());
	}
	else {
		throw BadExecutionTree{ "Expected an lvalue" };
	}

	Function(value);

	rep.SetVariable(var.AsName(), value);

	return var;
}
} // namespace calc_parser
} // namespace bwn