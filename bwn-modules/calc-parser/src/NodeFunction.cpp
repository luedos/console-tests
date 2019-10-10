#include "NodeFunction.h"

using namespace bwn::calc_parser;

NodeFunction::NodeFunction(const std::string& name, const std::vector<std::shared_ptr<Node>>& arguments)
	: name_{ name }
	, arguments_{ arguments }
{
}

Variable NodeFunction::GetValue(Repository& rep) const
{
	std::vector<Variable> args;
	args.reserve(arguments_.size());

	for (auto it = arguments_.begin(); it != arguments_.end(); ++it) {
		args.push_back((*it)->GetValue(rep));
	}

	return rep.InvokeFunction(name_, args);
}
