#include "Exceptions.h"

#include "Token.h"
#include "Node.h"
#include "Parser.h"

#include <regex>
#include <cctype>

#if defined(__GNUC__)
#define BWN_REGEX_ANY_BYTE "[\\x80-\\x7F]"
#else
#define BWN_REGEX_ANY_BYTE "[\\x00-\\xFF]"
#endif

using namespace bwn::calc_parser;


Parser::NodeTokenUnion::NodeTokenUnion(std::shared_ptr<Node> node)
	: node_ { node }
	, token_{}
{
}

Parser::NodeTokenUnion::NodeTokenUnion(std::shared_ptr<Token> token)
	: node_{}
	, token_{ token }
{
}

bool Parser::NodeTokenUnion::IsNode() const
{
	return node_.operator bool();
}

std::shared_ptr<Node> Parser::NodeTokenUnion::GetNode() const
{
	if (!IsNode()) {
		throw BadConversion{ "Union is not a node" };
	}
	return node_;
}

std::shared_ptr<Token> Parser::NodeTokenUnion::GetToken() const
{
	if (IsNode()) {
		throw BadConversion{ "Union is not a token" };
	}
	return token_;
}


std::string Parser::ProcessData(const std::string& data)
{	
	int offset = 0;

	std::string nocomments_data = RemoveComments(data);

	std::regex stub(front_stub_.GetString() + BWN_REGEX_ANY_BYTE "+?(?=" + back_stub_.GetString() + ")" + back_stub_.GetString());

	if (!std::regex_search(nocomments_data, stub, std::regex_constants::match_any)) {
		return nocomments_data;
	}

	std::string out = nocomments_data;

	size_t statement_number = 1;

	for (auto it = std::sregex_iterator(nocomments_data.begin(), nocomments_data.end(), stub); it != std::sregex_iterator(); ++it, ++statement_number)
	{
		std::string statement = it->str();
		const size_t statement_size = statement.size();

		statement = std::string(statement.begin() + front_stub_.GetSize(), statement.end() - back_stub_.GetSize());
		
		try
		{
			ProcessStatementCommentsFree(statement);
		}
		catch (const BadToken& e) {
			throw BadToken(e.what(), e.GetTokenType(), statement_number);
		}
		catch (const BadValue& e) {
			throw BadValue(e.what(), statement_number);
		}
		catch (const BadOperation& e) {
			throw BadOperation(e.what(), statement_number);
		}
		catch (const BadFunction& e) {
			throw BadFunction(e.what(), statement_number);
		}
		catch (const BadConversion& e) {
			throw BadConversion(e.what(), statement_number);
		}
		catch (const BadExecutionTree& e) {
			throw BadExecutionTree(e.what(), statement_number);
		}
		catch (const ParserException& e) {
			throw ParserException(e.what(), statement_number);
		}

		if (IsVariableExist(output_kword_)) 
		{
			statement = GetVariable(output_kword_).ToString();
			RemoveVariable(output_kword_);
		}
		else {
			statement.clear();
		}

		out.replace(it->position() + offset, statement_size, statement);
		offset += statement.size() - statement_size;
	}

	return out;
}

void Parser::SetFrontStub(const std::string& stub)
{
	front_stub_ = stub;
}

void Parser::SetBackStub(const std::string& stub)
{
	back_stub_ = stub;
}

void Parser::SetCommentLineStub(const std::string& stub)
{
	comment_line_ = stub;
}

void Parser::SetCommentFrontStub(const std::string& stub)
{
	comment_block_front_ = stub;
}

void Parser::SetCommentBackStub(const std::string& stub)
{
	comment_block_back_ = stub;
}

void Parser::SetOutputKeyword(const std::string& keyword)
{
	output_kword_ = keyword;
}

void Parser::ProcessStatement(const std::string& statement)
{
	ProcessStatementCommentsFree(RemoveComments(statement));
}

void Parser::ProcessStatementCommentsFree(const std::string statement)
{
	std::vector<NodeTokenUnion> tree;

	{
		std::vector<Token> tokens = Token::ParseTokens(statement);

		if (tokens.empty()) {
			return;
		}

		tree.reserve(tokens.size());

		for (auto it = tokens.begin(); it != tokens.end(); ++it) {
			tree.emplace_back(std::make_shared<Token>(std::move(*it)));
		}
	}

	std::shared_ptr<Node> node = Parser::UniteTree(tree.begin(), tree.end());

	node->GetValue(*this);
}

std::string Parser::RemoveComments(const std::string& data)
{
	std::regex pattern("(" + comment_line_.GetString() + BWN_REGEX_ANY_BYTE "+?(?=($)|(\\n)))|(" + comment_block_front_.GetString() + BWN_REGEX_ANY_BYTE "+?(?=" + comment_block_back_.GetString() + ")" + comment_block_back_.GetString() + ")");

	if (std::regex_search(data, pattern, std::regex_constants::match_any)) {
		return std::regex_replace(data, pattern, std::string());
	}

	return data;
}

std::shared_ptr<Node> Parser::UniteTree(
	std::vector<NodeTokenUnion>::const_iterator beg, 
	std::vector<NodeTokenUnion>::const_iterator end)
{
	if (beg == end) {
		throw BadExecutionTree{ "Execution tree creating failed, no nodes were passed." };
	}

	if (end - beg == 1) 
	{
		if (beg->IsNode()) {
			return beg->GetNode();
		}
		
		if (beg->GetToken()->GetType() & Token::U_ANY_VALUE) {
			return Node::MakeValueNode(*beg->GetToken());
		}

		throw BadExecutionTree{ "Expected an lvalue." };
	}


	std::vector<NodeTokenUnion> temp;

	// Brackets/Functions/Values
	for (auto it = beg; it != end; ++it)
	{
		if (it->IsNode()) 
		{
			temp.push_back(*it);
			continue;
		}

		const Token::TokenType ttype = it->GetToken()->GetType();

		switch (ttype)
		{
		case Token::LVALUE:
		case Token::PRVALUE:
			temp.push_back(Node::MakeValueNode(*it->GetToken()));
			break;
		case Token::OPENING_BRACKET:
		{
			auto temp_it = FindRespectedClosingBracket(it + 1, end);

			if (temp_it == end) {
				throw BadExecutionTree{ "Wasn't found respected closing bracket." };
			}

			if (it != end
				&& !(it - 1)->IsNode()
				&& (it - 1)->GetToken()->GetType() == Token::LVALUE)
			{
				std::vector<std::shared_ptr<Node>> nodes = UniteBetweenComas(it + 1, temp_it);
				temp.back() = Node::MakeFunctionNode(*(it - 1)->GetToken(), nodes);
			}
			else
			{				
				temp.push_back(Parser::UniteTree(it + 1, temp_it));
			}

			it = temp_it;

			break;
		}
		case Token::CLOSING_BRACKET:
			throw BadExecutionTree{ "Wasn't found respected opening bracket." };
		default:
			temp.push_back(*it);
		}
	} // Brackets/Functions/Values


	// Coma operator
	if (std::find_if(
		temp.begin(),
		temp.end(),
		[](const NodeTokenUnion& token) { return !token.IsNode() && token.GetToken()->GetType() == Token::OP_COMA; })
		!= temp.end())
	{
		return Node::MakeSequenceNode(UniteBetweenComas(temp.begin(), temp.end()));
	} // Coma operator

	std::vector<NodeTokenUnion> main_vec;
	main_vec.reserve(temp.size());
	main_vec.swap(temp);

	// Lvalue unary operator
	{
		bool found = true;

		while (found)
		{
			found = false;
			temp.clear();
			
			for (auto it = main_vec.begin(); it != main_vec.end(); ++it)
			{
				if (it->IsNode())
				{
					if (main_vec.end() - it > 1
						&& !(it + 1)->IsNode()
						&& (it + 1)->GetToken()->GetType() & Token::U_OP_ITERATORS)
					{
						temp.push_back(Node::MakePostfixUnaryOpNode(it->GetNode(), *(it + 1)->GetToken()));
						++it;
						found = true;
						continue;
					}

					if (it != main_vec.begin()
						&& !temp.back().IsNode()
						&& temp.back().GetToken()->GetType() & Token::U_OP_ITERATORS)
					{
						temp.back() = Node::MakePrefixUnaryOpNode(it->GetNode(), *temp.back().GetToken());
						found = true;
						continue;
					}
				}
				temp.push_back(std::move(*it));
			}

			main_vec.swap(temp);
		}

		if (std::find_if(
			main_vec.begin(),
			main_vec.end(),
			[](const NodeTokenUnion& token) { return !token.IsNode() && token.GetToken()->GetType() & Token::U_OP_ITERATORS; })
			!= main_vec.end())
		{
			throw BadExecutionTree{ "Expected an lvalue" };
		}
	} // Lvalue unary operator

	temp.clear();

	std::vector<NodeTokenUnion> right_side;

	// Separating right side
	{
		auto it = main_vec.begin();
		for (; it != main_vec.end(); ++it)
		{
			if (it->IsNode()) 
			{
				if (main_vec.end() - it == 1) {
					break;
				} 
				if ((it + 1)->IsNode()) {
					throw BadExecutionTree{ "Expected an operation." };
				}

				if ((it + 1)->GetToken()->GetType() & Token::U_OP_LVALUE) {
					continue;
				}

				break;
			}

			if (it->GetToken()->GetType() & Token::U_OP_LVALUE)
			{
				if (it == main_vec.begin() || !(it - 1)->IsNode()) {
					throw BadExecutionTree{ "Expected an lvalue" };
				}
				if (main_vec.end() - it == 1) {
					throw BadExecutionTree{ "Expected a value" };
				}
				continue;
			}

			break;
		}

		if (it == main_vec.begin()) {
			right_side.swap(main_vec);
		}
		else
		{
			right_side.reserve(main_vec.end() - it);

			for (auto transfer = it; transfer != main_vec.end(); ++transfer) {
				right_side.push_back(std::move(*transfer));
			}

			main_vec.erase(it, main_vec.end());
		}
	} // Separating right side

	std::shared_ptr<Node> right_node;

	// Ternary operator
	for (auto it = right_side.begin(); it != right_side.end(); ++it)
	{
		if (it->IsNode()) {
			continue;
		}

		const size_t op_type = it->GetToken()->GetType();
		if (op_type & Token::U_OP_TERNARY)
		{
			if (op_type & Token::OP_ELSE) {
				throw BadExecutionTree{ "Expected an IF statement operator" };
			}

			auto temp_it = FindRespectedTernaryOp(it + 1, right_side.end());

			if (temp_it == right_side.end()) {
				throw BadExecutionTree{ "Expected an ELSE statement operator" };
			}

			if (it == right_side.begin()
				|| temp_it - it < 2
				|| right_side.end() - temp_it < 2) 
			{
				throw BadExecutionTree{ "Expected a statement" };
			}

			right_node = Node::MakeTernaryOpNode(
				UniteTree(right_side.begin(), it),
				UniteTree(it + 1, temp_it),
				UniteTree(temp_it + 1, right_side.end()),
				*it->GetToken(),
				*temp_it->GetToken());

			break;
		}
	} // Ternary operator

	if (!right_node)
	{
		// Prefix unary operator
		size_t last_op_type = 0;
		for (auto it = right_side.begin(); it != right_side.end(); ++it)
		{
			if (it->IsNode()) 
			{
				temp.push_back(std::move(*it));
				last_op_type = 0;
				continue;
			}

			if (it->GetToken()->GetType() & Token::U_OP_UNARY
				&& (it == right_side.begin() || last_op_type))
			{
				auto temp_it = it;

				for (; temp_it != right_side.end(); ++temp_it)
				{
					if (temp_it->IsNode()) {
						break;
					}

					if (!(temp_it->GetToken()->GetType() & Token::U_OP_UNARY)) {
						throw BadExecutionTree{ "Expected a value" };
					}
				}

				if (temp_it == right_side.end()) {
					throw BadExecutionTree{ "Expected a value" };
				}


				std::shared_ptr<Node> temp_node = Node::MakePrefixUnaryOpNode(temp_it->GetNode(), *(temp_it - 1)->GetToken());

				for (auto point_it = temp_it - 1; point_it != it; --point_it) {
					temp_node = Node::MakePrefixUnaryOpNode(temp_node, *(point_it - 1)->GetToken());
				}

				temp.push_back(temp_node);

				it = temp_it;
				last_op_type = 0;
				continue;
			}

			last_op_type = it->GetToken()->GetType();
			temp.push_back(std::move(*it));
			
		} // Prefix unary operator

		right_side.swap(temp);
		temp.clear();


		UniteBinaryOperators(right_side, Token::U_OP_HIGH_RVALUE);
		UniteBinaryOperators(right_side, Token::U_OP_LOW_RVALUE);
		UniteBinaryOperators(right_side, Token::U_OP_HIGH_LOGIC);
		UniteBinaryOperators(right_side, Token::U_OP_LOW_LOGIC);

		if (right_side.size() != 1) {
			throw BadExecutionTree{ ("Execution tree creation failed, finale right size != 1 (" + std::to_string(right_side.size()) + ")").data() };
		}

		if (!right_side[0].IsNode()) {
			throw BadExecutionTree{ "Execution tree creation failed, finale right side is not a node." };
		}

		right_node = right_side[0].GetNode();
	}

	if (!right_node) {
		throw BadExecutionTree{ "Expected a value" };
	}

	if (main_vec.empty()) {
		return right_node;
	}

	auto it = main_vec.end();
	do
	{
		it -= 2;
		right_node = Node::MakeBinaryOpNode(it->GetNode(), right_node, *(it + 1)->GetToken());
	} while (main_vec.begin() != it);

	return right_node;
}

std::vector<std::shared_ptr<Node>> Parser::UniteBetweenComas(
	std::vector<NodeTokenUnion>::const_iterator begin, 
	std::vector<NodeTokenUnion>::const_iterator end)
{
	if (begin == end) {
		return {};
	}

	if ((!begin->IsNode() && begin->GetToken()->GetType() == Token::OP_COMA)
		|| (!(end - 1)->IsNode() && (end - 1)->GetToken()->GetType() == Token::OP_COMA))
	{
		throw BadExecutionTree{ "Expected a value" };
	}

	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(10);

	std::vector<NodeTokenUnion>::const_iterator first = begin;
	std::vector<NodeTokenUnion>::const_iterator last = begin;
	do
	{
		++last;

		if (last == end || (!last->IsNode() && last->GetToken()->GetType() == Token::OP_COMA))
		{
			nodes.push_back(UniteTree(first, last));


			if (last != end)
			{
				++last;
				first = last;
			}
		}
	} while (last != end);

	return nodes;
}

std::vector<Parser::NodeTokenUnion>::iterator Parser::RvalueOperatorSequenceSearch(
	std::vector<NodeTokenUnion>::iterator beg, 
	std::vector<NodeTokenUnion>::iterator end, 
	size_t token_type)
{
	for (auto temp_it = beg; temp_it != end; ++temp_it)
	{
		if (temp_it->IsNode())
		{
			if (end - temp_it == 1) {
				return temp_it;
			}

			if ((temp_it + 1)->IsNode()) {
				throw BadExecutionTree{ "Expected an operation" };
			}

			if (!((temp_it + 1)->GetToken()->GetType() & token_type)) {
				return temp_it;
			}

			continue;
		}

		if (temp_it->GetToken()->GetType() & token_type)
		{
			if (temp_it == beg || !(temp_it - 1)->IsNode()) {
				throw BadExecutionTree{ "Expected a value" };
			}
			if (end - temp_it == 1 || !(temp_it + 1)->IsNode()) {
				throw BadExecutionTree{ "Expected a value" };
			}
		}
	}

	return end;
}

void Parser::UniteBinaryOperators(std::vector<NodeTokenUnion>& tokens, size_t token_type)
{
	std::vector<NodeTokenUnion> temp;
	temp.reserve(tokens.size());

	for (auto it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->IsNode()
			&& tokens.end() - it != 1)
		{
			if ((it + 1)->IsNode()) {
				throw BadExecutionTree{ "Expected a value" };
			}

			if ((it + 1)->GetToken()->GetType() & token_type)
			{
				auto temp_it = RvalueOperatorSequenceSearch(it, tokens.end(), token_type);

				if (temp_it == tokens.end()) {
					throw BadExecutionTree{ "Expected a value" };
				}

				NodeTokenUnion root = it->GetNode();

				while (it != temp_it)
				{
					if (std::distance(it, temp_it) < 2) {
						throw BadExecutionTree{ "Uniting binary operators failed." };
					}
					if (!(it + 2)->IsNode()) {
						throw BadExecutionTree{ "Uniting binary operators failed, expected an lvalue." };
					}
					if ((it + 1)->IsNode())	{
						throw BadExecutionTree{ "Uniting binary operators failed, expected an operator." };
					}

					root = Node::MakeBinaryOpNode(root.GetNode(), (it + 2)->GetNode(), *(it + 1)->GetToken());
					it += 2;
				}
				temp.push_back(std::move(root));
				it = temp_it;
				continue;
			}
		}

		temp.push_back(std::move(*it));
	}

	tokens.swap(temp);
}

std::vector<Parser::NodeTokenUnion>::const_iterator Parser::FindRespectedClosingBracket(
	std::vector<NodeTokenUnion>::const_iterator beg, 
	std::vector<NodeTokenUnion>::const_iterator end)
{
	size_t opened = 1;

	for (; beg != end; ++beg)
	{
		if (!beg->IsNode())
		{
			switch (beg->GetToken()->GetType())
			{
			case Token::OPENING_BRACKET:
				++opened;
				break;
			case Token::CLOSING_BRACKET:
				--opened;
				break;
			default:
				break;
			}
			if (opened == 0) {
				return beg;
			}
		}
	}

	return end;
}

std::vector<Parser::NodeTokenUnion>::const_iterator Parser::FindRespectedTernaryOp(
	std::vector<NodeTokenUnion>::const_iterator beg, 
	std::vector<NodeTokenUnion>::const_iterator end)
{
	size_t opened = 1;

	for (; beg != end; ++beg)
	{
		if (!beg->IsNode())
		{
			switch (beg->GetToken()->GetType())
			{
			case Token::OP_IF:
				++opened;
				break;
			case Token::OP_ELSE:
				--opened;
				break;
			default:
				break;
			}
			if (opened == 0) {
				return beg;
			}
		}
	}

	return end;
}

Parser::RegexStub::RegexStub(const std::string& stub)
{
	size_ = stub.size();

	if (!stub.empty()) {
		stub_ = "(" + std::regex_replace(stub, std::regex(R"([-[\]{}()*+?.,\^$|#\\])"), R"(\$&)") + ")";
	}
}

const std::string& Parser::RegexStub::GetString() const
{
	return stub_;
}

size_t Parser::RegexStub::GetSize() const
{
	return size_;
}
