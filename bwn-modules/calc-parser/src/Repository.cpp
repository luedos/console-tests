#include "Repository.h"

#include "Exceptions.h"

using namespace bwn::calc_parser;

void Repository::SetVariable(const std::string& name, const Value& value)
{
	auto it = variables_.find(name);

	if (it == variables_.end()) {
		variables_.emplace(name, value);
	}
	else {
		(*it).second = value;
	}
}

Value Repository::GetVariable(const std::string& name) const
{
	auto it = variables_.find(name);

	if (it == variables_.end()) {
		throw BadValue{ ("Variable with name \"" + name + "\", wasn't found.").data() };
	}

	return it->second;
}

std::map<std::string, Value> bwn::calc_parser::Repository::GetVariables() const
{
	return variables_;
}

bool Repository::IsVariableExist(const std::string& name) const
{
	return variables_.find(name) != variables_.end();
}

void Repository::RemoveVariable(const std::string& name)
{
	if (!IsVariableExist(name)) {
		return;
	}

	variables_.erase(name);
}

void Repository::ClearVariables()
{
	variables_.clear();
}

void Repository::AddFunction(const std::string& name, const RepFunction& function)
{
	if (IsFunctionExist(name)) {
		throw BadFunction{ ("Function with name \"" + name + "\", allready exist.").data() };
	}

	functions_.emplace(name, function);
}

Variable Repository::InvokeFunction(const std::string& name, const std::vector<Variable>& arguments)
{
	auto func = functions_.find(name);

	if (func == functions_.end()) {
		throw BadFunction{ ("Function with name \"" + name + "\", wasn't found.").data() };
	}

	return func->second(*this, arguments);
}

std::map<std::string, Repository::RepFunction> Repository::GetFunctions() const
{
	return functions_;
}

bool Repository::IsFunctionExist(const std::string & name) const
{
	return functions_.find(name) != functions_.end();
}

void Repository::RemoveFunction(const std::string & name)
{
	if (!IsFunctionExist(name)) {
		return;
	}

	functions_.erase(name);
}

void Repository::ClearFunctions()
{
	functions_.clear();
}

