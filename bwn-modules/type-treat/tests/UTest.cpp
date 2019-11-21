#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TypeName.h"

TEST_CASE("Simple types")
{
	REQUIRE(bwn::TypeTreat<int>::Name() == "int");
	REQUIRE(bwn::TypeTreat<long>::Name() == "long");
	REQUIRE(bwn::TypeTreat<char>::Name() == "char");
	REQUIRE(bwn::TypeTreat<void>::Name() == "void");
	REQUIRE(bwn::TypeTreat<std::nullptr_t>::Name() == "nullptr_t");
}

TEST_CASE("Pointers/References")
{
	REQUIRE(bwn::TypeTreat<const int*const*&>::Name() == "const int*const*&");
	REQUIRE(bwn::TypeTreat<long***&&>::Name() == "long***&&");
	REQUIRE(bwn::TypeTreat<char&>::Name() == "char&");
}

TEST_CASE("Arrays/Functions")
{
	REQUIRE(bwn::TypeTreat<int[20]>::Name() == "int[20]");
	REQUIRE(bwn::TypeTreat<long**[]>::Name() == "long**[]");
	REQUIRE(bwn::TypeTreat<char(void*)>::Name() == "char(void*)");
	REQUIRE(bwn::TypeTreat<void(char*, int**&)>::Name() == "void(char*,int**&)");
}