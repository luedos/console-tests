#include "Value.h"

#include "Node.h"
#include "NodeVariable.h"
#include "NodeFunction.h"
#include "NodeSequence.h"
#include "NodeUnaryOp.h"
#include "NodeBinaryOp.h"
#include "NodeTernaryOp.h"

#include <memory>
#include <list>

using namespace bwn::calc_parser;

std::shared_ptr<Node> Node::MakeValueNode(const Token& token)
{
	Variable temp;

	if (token.GetType() == Token::PRVALUE) {
		temp = token.GetValue();
	}
	else if (token.GetType() == Token::LVALUE) {
		temp = token.GetName();
	}
	else {
		throw BadExecutionTree{ "Incorrect token type was passed for value node." };
	}

	return std::make_shared<NodeVariable>(temp);
}

std::shared_ptr<Node> Node::MakePrefixUnaryOpNode(
	std::shared_ptr<Node> value,
	const Token& token)
{
	if (!(token.GetType() & Token::U_ANY_OPERATOR)) {
		throw BadExecutionTree{ "Incorrect token was passed for prefix unary operator node creation (Token is not an operator)." };
	}

	switch (token.GetType())
	{
	case Token::OP_ADD:
		return std::make_shared<NodeUnaryOp<Value(Value::*)() const, (&Value::operator+)>>(value);
	case Token::OP_SUB:
		return std::make_shared<NodeUnaryOp<Value(Value::*)() const, (&Value::operator-)>>(value);
	case Token::OP_NOT:
		return std::make_shared<NodeUnaryOp<Value(Value::*)() const, (&Value::operator!)>>(value);
	case Token::OP_PLUSPLUS:
		return std::make_shared<NodeUnaryOp<Value&(*)(Value&), (&bwn::calc_parser::operator++)>>(value);
	case Token::OP_MINUSMINUS:
		return std::make_shared<NodeUnaryOp<Value&(*)(Value&), (&bwn::calc_parser::operator++)>>(value);
	default:
		throw BadExecutionTree{ "Unknown token was passed for prefix unary operator node creation." };
	}
}

std::shared_ptr<Node> Node::MakePostfixUnaryOpNode(
	std::shared_ptr<Node> value,
	const Token & token)
{
	if (!(token.GetType() & Token::U_ANY_OPERATOR)) {
		throw BadExecutionTree{ "Incorrect token was passed for postfix unary operator node creation (Token is not an operator)." };
	}

	switch (token.GetType())
	{
	case Token::OP_PLUSPLUS:
		return std::make_shared<NodeUnaryOp<Value(*)(Value&, int), (&bwn::calc_parser::operator++)>>(value);
	case Token::OP_MINUSMINUS:
		return std::make_shared<NodeUnaryOp<Value(*)(Value&, int), (&bwn::calc_parser::operator--)>>(value);
	default:
		throw BadExecutionTree{ "Unknown token was passed for postfix unary operator node creation." };
	}
}

std::shared_ptr<Node> Node::MakeBinaryOpNode(
	std::shared_ptr<Node> left,
	std::shared_ptr<Node> right,
	const Token & token)
{
	if (!(token.GetType() & Token::U_ANY_OPERATOR)) {
		throw BadExecutionTree{ "Incorrect token was passed for binary operator creation (Token is not an operator)." };
	}

	switch (token.GetType())
	{
	case Token::OP_ADD:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator+)>>(left, right);
	case Token::OP_SUB:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator-)>>(left, right);
	case Token::OP_MUL:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator*)>>(left, right);
	case Token::OP_DIV:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator/)>>(left, right);
	case Token::OP_MOD:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator%)>>(left, right);
	case Token::OP_AND:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator&)>>(left, right);
	case Token::OP_OR:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator|)>>(left, right);
	case Token::OP_XOR:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator^)>>(left, right);
	case Token::OP_LSH:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator<<)>>(left, right);
	case Token::OP_RSH:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator>>)>>(left, right);
	case Token::OP_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator=)>>(left, right);
	case Token::OP_ADD_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator+=)>>(left, right);
	case Token::OP_SUB_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator-=)>>(left, right);
	case Token::OP_MUL_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator*=)>>(left, right);
	case Token::OP_DIV_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator/=)>>(left, right);
	case Token::OP_MOD_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator%=)>>(left, right);
	case Token::OP_AND_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator&=)>>(left, right);
	case Token::OP_OR_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator|=)>>(left, right);
	case Token::OP_XOR_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator^=)>>(left, right);
	case Token::OP_LSH_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator<<=)>>(left, right);
	case Token::OP_RSH_EQUAL:
		return std::make_shared<NodeBinaryOp<Value&(Value::*)(const Value&), (&Value::operator>>=)>>(left, right);
	case Token::OP_LOGIC_E:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator==)>>(left, right);
	case Token::OP_LOGIC_NE:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator!=)>>(left, right);
	case Token::OP_LOGIC_L:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator<)>>(left, right);
	case Token::OP_LOGIC_G:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator>)>>(left, right);
	case Token::OP_LOGIC_LE:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator<=)>>(left, right);
	case Token::OP_LOGIC_GE:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator>=)>>(left, right);
	case Token::OP_LOGIC_AND:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator&&)>>(left, right);
	case Token::OP_LOGIC_OR:
		return std::make_shared<NodeBinaryOp<Value(*)(const Value&, const Value&), (&bwn::calc_parser::operator||)>>(left, right);

	default:
		throw BadExecutionTree{ "Unknown token was passed for binary operator node creation." };
	}
}

namespace bwn
{
namespace calc_parser
{

Variable TernaryChooser(const Value& chooser, const Variable& first, const Variable& second)
{
	if (chooser.AsBool()) {
		return first;
	}
	else {
		return second;
	}
}

}
}

std::shared_ptr<Node> Node::MakeTernaryOpNode(
	std::shared_ptr<Node> first,
	std::shared_ptr<Node> second,
	std::shared_ptr<Node> third,
	const Token& first_token,
	const Token& second_token)
{
	if (first_token.GetType() != Token::OP_IF)
	{
		throw BadExecutionTree{ "Incorrect token was passed as IF statement for ternary operator node creation."};

	}
	if (second_token.GetType() != Token::OP_ELSE)
	{
		throw BadExecutionTree{ "Incorrect token was passed as ELSE statement for ternary operator node creation." };
	}

	return std::make_shared<NodeTernaryOp<TernaryChooser>>(first, second, third);
}

std::shared_ptr<Node> Node::MakeFunctionNode(
	const Token& invoke,
	const std::vector<std::shared_ptr<Node>>& arguments)
{
	if (invoke.GetType() != Token::LVALUE) {
		throw BadExecutionTree{ "Expected an lvalue for function identifier." };
	}

	return std::make_shared<NodeFunction>(invoke.GetName(), arguments);
}

std::shared_ptr<Node> bwn::calc_parser::Node::MakeSequenceNode(const std::vector<std::shared_ptr<Node>>& arguments)
{
	if (arguments.empty()) {
		throw BadExecutionTree{ "No arguments were passed for sequence node creation." };
	}
		 
	return std::make_shared<NodeSequence>(arguments);
}

