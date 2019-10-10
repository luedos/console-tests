#pragma once

#include <string>

namespace bwn
{

template<typename C, typename...Args>
auto invoke(C&& callable, Args&&...args) ->
	decltype(callable(std::forward<Args>(args)...))
{
	return callable(std::forward<Args>(args)...);
}

template<typename O, typename F, typename...Args>
auto invoke(F&& function, O&& obj, Args&&...args) ->
	decltype((obj.*function)(std::forward<Args>(args)...))
{
	return (obj.*function)(std::forward<Args>(args)...);
}

namespace calc_parser
{

std::string ProcessStringLiteral(const std::string& str);

}
}