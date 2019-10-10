#pragma once

#include "Repository.h"
#include <vector>

namespace bwn
{
namespace calc_parser
{

//
// Forvard declarations.
//
class Node;
class Token;

class Parser : private Repository
{
	//
	// Uliases.
	//
public:
	//! Function objects.
	using Function = Repository::RepFunction;

	using Repository::ClearFunctions;
	using Repository::ClearVariables;
	using Repository::AddFunction;
	using Repository::IsVariableExist;
	using Repository::GetVariable;
	using Repository::SetVariable;

	//
	// Private classes.
	//
private:
	//! Class for excecution tree uniting.
	class NodeTokenUnion
	{
		//
		// Construction and destruction.
		//
	public:
		//! Constructor from Node.
		NodeTokenUnion(std::shared_ptr<Node> node);
		//! Constructor from Token.
		NodeTokenUnion(std::shared_ptr<Token> token);

		//
		// Public interface.
		//
	public:
		//! Returns true if union containes Node. 
		bool IsNode() const;
		//! Returns Node.
		std::shared_ptr<Node> GetNode() const;
		//! Returns Token.
		std::shared_ptr<Token> GetToken() const;

		//
		// Private members.
		//
	private:
		//! Node member.
		std::shared_ptr<Node> node_;
		//! Token member.
		std::shared_ptr<Token> token_;
	};
	//! Class for regex stubs incapsulation.
	class RegexStub
	{
		//
		// Construction and destruction.
		//
	public:
		//! constructor.
		RegexStub(const std::string& stub);

		//
		// Public interface.
		//
	public:
		//! Returns stub string for regex search.
		const std::string& GetString() const;
		//! Returns size of regex searched stub.
		size_t GetSize() const;

		//
		// Private members.
		//
	private:
		//! Stub string.
		std::string stub_ = {};
		//! Actual size in regex search.
		size_t size_ = 0;
	};

	//
	// Public interface.
	//
public:
	//! Returns processed data.
	std::string ProcessData(const std::string& data);
	//! Proceses single statement.
	void ProcessStatement(const std::string& statement);
	//! Sets front stub.
	void SetFrontStub(const std::string& stub);
	//! Sets back stub.
	void SetBackStub(const std::string& stub);
	//! Sets comment line starting stub.
	void SetCommentLineStub(const std::string& stub);
	//! Sets comments block front stub.
	void SetCommentFrontStub(const std::string& stub);
	//! Sets comments block back stub.
	void SetCommentBackStub(const std::string& stub);
	//! Sets output keyword.
	void SetOutputKeyword(const std::string& keyword);

	//
	// Private members.
	//
private:
	//! Processes statement without comments deleting.
	void ProcessStatementCommentsFree(const std::string statement);
	//! Removes all comments.
	std::string RemoveComments(const std::string& data);
	//! Returns root of the callable tree.
	std::shared_ptr<Node> UniteTree(
		std::vector<NodeTokenUnion>::const_iterator beg, 
		std::vector<NodeTokenUnion>::const_iterator end);
	//! Returns sequence of nodes which were separeted by COMA operator. 
	std::vector<std::shared_ptr<Node>> UniteBetweenComas(
		std::vector<NodeTokenUnion>::const_iterator begin, 
		std::vector<NodeTokenUnion>::const_iterator end);
	//! Returns ending of operator sequence of specific type.
	std::vector<NodeTokenUnion>::iterator RvalueOperatorSequenceSearch(
		std::vector<NodeTokenUnion>::iterator beg,
		std::vector<NodeTokenUnion>::iterator end,
		size_t token_type);
	//! Unites operators sequences of specific operator type.
	void UniteBinaryOperators(std::vector<NodeTokenUnion>& tokens, size_t token_type);
	//! Returns respected closing bracket.
	std::vector<NodeTokenUnion>::const_iterator FindRespectedClosingBracket(
		std::vector<NodeTokenUnion>::const_iterator beg,
		std::vector<NodeTokenUnion>::const_iterator end);
	//! Returns respected ternary ELSE operator.
	std::vector<NodeTokenUnion>::const_iterator FindRespectedTernaryOp(
		std::vector<NodeTokenUnion>::const_iterator beg,
		std::vector<NodeTokenUnion>::const_iterator end);

	//
	// Private members.
	//
private:
	//! Line comment stub.
	RegexStub comment_line_ = std::string("//");
	//! Front stub of comment block.
	RegexStub comment_block_front_ = std::string("/*");
	//! Back stub of comment block.
	RegexStub comment_block_back_ = std::string("*/");
	//! Infront stub.
	RegexStub front_stub_ = std::string{};
	//! Back stub.
	RegexStub back_stub_ = std::string("\n");
	//! Output variable name.
	std::string output_kword_ = "OUTPUT";
};

}
}