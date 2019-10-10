#pragma once

#include "Variable.h"
#include "Token.h"
#include "Repository.h"

#include <memory>
#include <vector>

namespace bwn
{
namespace calc_parser
{

class Node
{
	//
	// Construction and destruction.
	//
public:
	//! Destructor.
	virtual ~Node() = default;
	
	//
	// Public interface.
	//
public:
	//! Returns representative value. 
	virtual Variable GetValue(Repository& rep) const = 0;
	//! Returns node as value.
	static std::shared_ptr<Node> MakeValueNode(const Token& token);
	//! Returns node as prefix unary operator.
	static std::shared_ptr<Node> MakePrefixUnaryOpNode(std::shared_ptr<Node> value, const Token& token);
	//! Returns node as postfix unary operator.
	static std::shared_ptr<Node> MakePostfixUnaryOpNode(std::shared_ptr<Node> value, const Token& token);
	//! Returns node as binary operator.
	static std::shared_ptr<Node> MakeBinaryOpNode(std::shared_ptr<Node> left, std::shared_ptr<Node> right, const Token& token);
	//! Returns node as ternary operator.
	static std::shared_ptr<Node> MakeTernaryOpNode(std::shared_ptr<Node> first, std::shared_ptr<Node> second, std::shared_ptr<Node> third, const Token& first_token, const Token& second_token);
	//! Returns node as function.
	static std::shared_ptr<Node> MakeFunctionNode(const Token& invoke, const std::vector<std::shared_ptr<Node>>& arguments);
	//! Returns node as sequence.
	static std::shared_ptr<Node> MakeSequenceNode(const std::vector<std::shared_ptr<Node>>& arguments);
};

} // namespace calc_parser
} // namespace bwn