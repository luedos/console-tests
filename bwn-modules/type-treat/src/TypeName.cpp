#include "TypeName.h"

std::string bwn::VariableToString(std::nullptr_t)
{
	return "nullptr";
}

template<>
const std::string bwn::TypeName<char>::to_string() {
	return "char";
}

template<>
const std::string bwn::TypeName<unsigned char>::to_string() {
	return "unsigned char";
}

template<>
const std::string bwn::TypeName<short>::to_string() {
	return "short";
}

template<>
const std::string bwn::TypeName<unsigned short>::to_string() {
	return "unsigned short";
}

template<>
const std::string bwn::TypeName<int>::to_string() {
	return "int";
}

template<>
const std::string bwn::TypeName<unsigned int>::to_string() {
	return "unsigned int";
}

template<>
const std::string bwn::TypeName<long>::to_string() {
	return "long";
}

template<>
const std::string bwn::TypeName<unsigned long>::to_string() {
	return "unsigned long";
}

template<>
const std::string bwn::TypeName<long long>::to_string() {
	return "long long";
}

template<>
const std::string bwn::TypeName<unsigned long long>::to_string() {
	return "unsigned long long";
}

template<>
const std::string bwn::TypeName<float>::to_string() {
	return "float";
}

template<>
const std::string bwn::TypeName<double>::to_string() {
	return "double";
}

template<>
const std::string bwn::TypeName<long double>::to_string() {
	return "long double";
}

template<>
const std::string bwn::TypeName<void>::to_string() {
	return "void";
}

template<>
const std::string bwn::TypeName<bool>::to_string() {
	return "bool";
}

template<>
const std::string bwn::TypeName<decltype(nullptr)>::to_string() {
	return "nullptr";
}

