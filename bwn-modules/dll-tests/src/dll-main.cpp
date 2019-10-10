#include "dll-main.h"

#include <iostream>

void dll_first_func(unsigned int first, unsigned int second)
{
	std::cout << "Hello world from first dll function, parameters are : " << first << ", and " << second << std::endl;
}


std::string dll_string_first(const std::string& first, const std::string& second)
{
	std::cout << "Hello from dll_string_first(\"" << first << "\", \"" << second << "\")" << std::endl;
	return first + second;
}
std::string dll_string_second(const std::string& first, const std::string& second)
{
	std::cout << "Hello from dll_string_second(\"" << first << "\", \"" << second << "\")" << std::endl;
	return first + second;
}
std::string dll_string_third(const std::string& first, const std::string& second)
{
	std::cout << "Hello from dll_string_third(\"" << first << "\", \"" << second << "\")" << std::endl;
	return first + second;
}
std::string dll_string_forth(const std::string& first, const std::string& second)
{
	std::cout << "Hello from dll_string_forth(\"" << first << "\", \"" << second << "\")" << std::endl;
	return first + second;
}
