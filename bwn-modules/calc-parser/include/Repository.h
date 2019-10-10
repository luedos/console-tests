#pragma once

#include <map>
#include <string>
#include <functional>
#include <vector>

#include "Variable.h"

namespace bwn
{
namespace calc_parser
{

class Repository
{
	//
	// Uliases.
	//
public:
	//! Function objects.
	using RepFunction = std::function<Variable(Repository&, const std::vector<Variable>&)>;

	//
	// Public interface.
	//
public:
	//! Sets variable in the set (if variable does not exist, adds it).
	void SetVariable(const std::string& name, const Value& value = {});
	//! Returns value of the variable.
	Value GetVariable(const std::string& name) const;
	//! Returns all variable from repository.
	std::map<std::string, Value> GetVariables() const;
	//! Returns true if variable exist.
	bool IsVariableExist(const std::string& name) const;
	//! Returns value of the variable.
	Variable InvokeFunction(const std::string& name, const std::vector<Variable>& arguments);
	//! Returns all variable from repository.
	std::map<std::string, RepFunction> GetFunctions() const;
	//! Returns true if variable exist.
	bool IsFunctionExist(const std::string& name) const;

	//
	// Protected methods.
	//
protected:
	//! Returns true if variable exist.
	void RemoveVariable(const std::string& name);
	//! Sets variable in the set (if variable does not exist, adds it).
	void AddFunction(const std::string& name, const RepFunction& function);
	//! Returns true if variable exist.
	void RemoveFunction(const std::string& name);
	//! Clears repository from variables.
	void ClearVariables();
	//! Clears repository from functions.
	void ClearFunctions();

	//
	// Private members.
	//
private:
	//! Variables.
	std::map<std::string, Value> variables_;
	//! Functions.
	std::map<std::string, RepFunction> functions_;
};

} // namespace calc_parser
} // namespace bwn
