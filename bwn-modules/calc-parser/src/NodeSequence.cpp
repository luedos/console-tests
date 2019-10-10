#include "NodeSequence.h"

using namespace bwn::calc_parser;

NodeSequence::NodeSequence(const std::vector<std::shared_ptr<Node>>& nodes)
	: nodes_{ nodes }
{
}

Variable NodeSequence::GetValue(Repository& rep) const
{
	for (auto it = nodes_.begin(); it != nodes_.end(); ++it)
	{
		Variable&& temp = (*it)->GetValue(rep);

		if (nodes_.end() - it == 1) {
			return std::move(temp);
		}		
	}

	return Variable();
}
