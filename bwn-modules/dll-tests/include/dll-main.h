#pragma once
#include "Defines.h"
#include <string>

void DLL_TESTS_API dll_first_func(unsigned int first, unsigned int second);

std::string DLL_TESTS_API dll_string_first(const std::string& first, const std::string& second);
std::string DLL_TESTS_API dll_string_second(const std::string& first, const std::string& second);
std::string DLL_TESTS_API dll_string_third(const std::string& first, const std::string& second);
std::string DLL_TESTS_API dll_string_forth(const std::string& first, const std::string& second);