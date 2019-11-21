#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "TypeTreat.h"

template<char FirstV, char...CharsVs>
struct bwn::TypeName<bwn::CtimeString<FirstV, CharsVs...>>
{
	using String = bwn::CtimeConcatT<
		CtimeString<'C','t','i','m','e','S','t','r','i','n','g','<'>,
		CtimeString<'\'',FirstV,'\''>,
		CtimeString<',','\'',CharsVs,'\''>...,
		CtimeString<'>'>>;
};

TEST_CASE("Simple types")
{
	REQUIRE(bwn::TypeTreat<int>::Name() == "int");
	REQUIRE(bwn::TypeTreat<long>::Name() == "long");
	REQUIRE(bwn::TypeTreat<char>::Name() == "char");
	REQUIRE(bwn::TypeTreat<void>::Name() == "void");
	REQUIRE(bwn::TypeTreat<std::nullptr_t>::Name() == "nullptr_t");
	REQUIRE(bwn::TypeTreat<bwn::CtimeString<>>::Name() == "default");
	REQUIRE(bwn::TypeTreat<bwn::CtimeString<'b','w','n'>>::Name() == "CtimeString<\'b\',\'w\',\'n\'>");
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

	using ArrayLayer = int***[10];
	using FunctionLayer = int&&(int**,int**&);
	REQUIRE(bwn::TypeTreat<ArrayLayer[20]>::Name() == "int***[10][20]");
	REQUIRE(bwn::TypeTreat<ArrayLayer***[20]>::Name() == "int***(***)[10][20]");
	REQUIRE(bwn::TypeTreat<FunctionLayer**[20]>::Name() == "int&&(**[20])(int**,int**&)");
	REQUIRE(bwn::TypeTreat<FunctionLayer**[20]>::Name() == "int&&(**[20])(int**,int**&)");
	REQUIRE(bwn::TypeTreat<FunctionLayer*&(ArrayLayer[])>::Name() == "int&&(*&)(int**,int**&)(int***(*)[10])");

}