#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TypeName.h"

TEST_CASE("Simple types")
{
	REQUIRE(bwn::TypeTreat<int>::get_name() == "int");
	REQUIRE(bwn::TypeTreat<long>::get_name() == "long");
	REQUIRE(bwn::TypeTreat<char>::get_name() == "char");
	REQUIRE(bwn::TypeTreat<void>::get_name() == "void");
	REQUIRE(bwn::TypeTreat<std::nullptr_t>::get_name() == "nullptr");
}

TEST_CASE("Pointers/References")
{
	REQUIRE(bwn::TypeTreat<const int*const*&>::get_name() == "const int*const*&");
	REQUIRE(bwn::TypeTreat<long***&&>::get_name() == "long***&&");
	REQUIRE(bwn::TypeTreat<char&>::get_name() == "char&");
}

TEST_CASE("Arrays/Functions")
{
	REQUIRE(bwn::TypeTreat<int[20]>::get_name() == "int[20]");
	REQUIRE(bwn::TypeTreat<long**[]>::get_name() == "long**[]");
	REQUIRE(bwn::TypeTreat<char(void*)>::get_name() == "char(void*)");
	REQUIRE(bwn::TypeTreat<void(char*, int**&)>::get_name() == "void(char*, int**&)");
}