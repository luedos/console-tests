#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "Exceptions.h"
#include "Value.h"
#include "Token.h"
#include "Parser.h"

using namespace bwn::calc_parser;


TEST_CASE("Value class assigning", "[Value]")
{
	SECTION("Null assigning")
	{
		Value val;

		REQUIRE(val.GetType() == Value::T_NULL);
	}
	SECTION("Assigning boolean") 
	{
		Value val = true;

		REQUIRE(val.GetType() == Value::T_BOOL);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsBool() == true);

		val = false;

		REQUIRE(val.GetType() == Value::T_BOOL);
		REQUIRE(val.IsEmpty());
		REQUIRE(val.AsBool() == false);
	}
	SECTION("Assigning unsigned integer")
	{
		Value val = 10u;

		REQUIRE(val.GetType() == Value::T_UINT);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsUInt() == 10);

		val = static_cast<unsigned long long int>(-25);

		REQUIRE(val.GetType() == Value::T_UINT);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsUInt() == static_cast<unsigned long long int>(-25));

		val = 0u;
		REQUIRE(val.IsEmpty());
	}
	SECTION("Assigning integer")
	{
		Value val = 10;

		REQUIRE(val.GetType() == Value::T_INT);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsInt() == 10);

		val = -25;

		REQUIRE(val.GetType() == Value::T_INT);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsInt() == -25);

		val = 0;
		REQUIRE(val.IsEmpty());
	}
	SECTION("Assigning double")
	{
		Value val = 0.25;

		REQUIRE(val.GetType() == Value::T_DOUBLE);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsDouble() == 0.25);

		val = -125.15;

		REQUIRE(val.GetType() == Value::T_DOUBLE);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsDouble() == -125.15);

		val = static_cast<double>(0.0);
		REQUIRE(val.IsEmpty());
	}
	SECTION("Assigning string")
	{
		Value val = std::string("This is test string");

		REQUIRE(val.GetType() == Value::T_STRING);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsString() == "This is test string");

		val = "This is test const char*";

		REQUIRE(val.GetType() == Value::T_STRING);
		REQUIRE(!val.IsEmpty());
		REQUIRE(val.AsString() == "This is test const char*");

		val = "";
		REQUIRE(val.IsEmpty());
	}
}

TEST_CASE("Changing types", "[Value]")
{
	SECTION("From string")
	{
		Value test_val;

		test_val = "true";
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == true);

		test_val = "false";
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == false);

		test_val = "-125";
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -125);

		test_val = "125";
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 125);

		test_val = "0xFF";
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 0xFF);

		test_val = "07777";
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 07777);

		test_val = "-125.124";
		test_val.ChangeToType(Value::T_DOUBLE);

		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == -125.124);

		test_val = "No metter what!";
		test_val.ChangeToType(Value::T_NULL);

		REQUIRE(test_val.GetType() == Value::T_NULL);
	}

	SECTION("From bool")
	{
		Value test_val;

		test_val = true;
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 1);

		test_val = true;
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 1);

		test_val = true;
		test_val.ChangeToType(Value::T_DOUBLE);

		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 1.0);

		test_val = true;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "true");

		test_val = false;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "false");

		test_val = false;
		test_val.ChangeToType(Value::T_NULL);

		REQUIRE(test_val.GetType() == Value::T_NULL);
	}

	SECTION("From int")
	{
		Value test_val;

		test_val = 125;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == true);

		test_val = 0;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == false);

		test_val = 125;
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 125);

		test_val = 125;
		test_val.ChangeToType(Value::T_DOUBLE);

		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 125.0);

		test_val = 125;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "125");

		test_val = -125;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "-125");

		test_val = -125;
		test_val.ChangeToType(Value::T_NULL);

		REQUIRE(test_val.GetType() == Value::T_NULL);
	}

	SECTION("From uint")
	{
		Value test_val;

		test_val = 125u;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == true);

		test_val = 0u;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == false);

		test_val = 125u;
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 125);

		test_val = 125u;
		test_val.ChangeToType(Value::T_DOUBLE);

		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 125.0);

		test_val = 125u;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "125");
	
		test_val = 125u;
		test_val.ChangeToType(Value::T_NULL);

		REQUIRE(test_val.GetType() == Value::T_NULL);
	}

	SECTION("From double")
	{
		Value test_val;

		test_val = 125.124;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == true);

		test_val = 0.0;
		test_val.ChangeToType(Value::T_BOOL);

		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool() == false);

		test_val = -125.124;
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -125);

		test_val = 125.124;
		test_val.ChangeToType(Value::T_UINT);

		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 125);

		test_val = 125.124;
		test_val.ChangeToType(Value::T_STRING);

		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "125.124");

		test_val = 125.124;
		test_val.ChangeToType(Value::T_NULL);

		REQUIRE(test_val.GetType() == Value::T_NULL);
	}
}

TEST_CASE("Value comparising between all equal", "[Value]")
{
	Value bool_val = true;
	Value int_val = static_cast<long long int>(1);
	Value uint_val = static_cast<unsigned long long int>(1);
	Value double_val = 1.0;
	Value string1_val = "String1";
	Value string2_val = "String1";

	SECTION("Operator \"==\"")
	{
		REQUIRE((string1_val == string2_val).AsBool());

		REQUIRE((bool_val == int_val).AsBool());
		REQUIRE((bool_val == uint_val).AsBool());
		REQUIRE((bool_val == double_val).AsBool());

		REQUIRE((int_val == bool_val).AsBool());
		REQUIRE((int_val == uint_val).AsBool());
		REQUIRE((int_val == double_val).AsBool());

		REQUIRE((uint_val == bool_val).AsBool());
		REQUIRE((uint_val == int_val).AsBool());
		REQUIRE((uint_val == double_val).AsBool());

		REQUIRE((double_val == bool_val).AsBool());
		REQUIRE((double_val == int_val).AsBool());
		REQUIRE((double_val == uint_val).AsBool());
	}
	SECTION("Operator \"!=\"")
	{
		REQUIRE(!((string1_val != string2_val).AsBool()));

		REQUIRE(!((bool_val != int_val).AsBool()));
		REQUIRE(!((bool_val != uint_val).AsBool()));
		REQUIRE(!((bool_val != double_val).AsBool()));

		REQUIRE(!((int_val != bool_val).AsBool()));
		REQUIRE(!((int_val != uint_val).AsBool()));
		REQUIRE(!((int_val != double_val).AsBool()));

		REQUIRE(!((uint_val != bool_val).AsBool()));
		REQUIRE(!((uint_val != int_val).AsBool()));
		REQUIRE(!((uint_val != double_val).AsBool()));

		REQUIRE(!((double_val != bool_val).AsBool()));
		REQUIRE(!((double_val != int_val).AsBool()));
		REQUIRE(!((double_val != uint_val).AsBool()));
	}
	SECTION("Operator \"<\"")
	{
		REQUIRE(!((string1_val < string2_val).AsBool()));

		REQUIRE(!((bool_val < int_val).AsBool()));
		REQUIRE(!((bool_val < uint_val).AsBool()));
		REQUIRE(!((bool_val < double_val).AsBool()));

		REQUIRE(!((int_val < bool_val).AsBool()));
		REQUIRE(!((int_val < uint_val).AsBool()));
		REQUIRE(!((int_val < double_val).AsBool()));

		REQUIRE(!((uint_val < bool_val).AsBool()));
		REQUIRE(!((uint_val < int_val).AsBool()));
		REQUIRE(!((uint_val < double_val).AsBool()));

		REQUIRE(!((double_val < bool_val).AsBool()));
		REQUIRE(!((double_val < int_val).AsBool()));
		REQUIRE(!((double_val < uint_val).AsBool()));
	}
	SECTION("Operator \">\"")
	{
		REQUIRE(!((string1_val > string2_val).AsBool()));

		REQUIRE(!((bool_val > int_val).AsBool()));
		REQUIRE(!((bool_val > uint_val).AsBool()));
		REQUIRE(!((bool_val > double_val).AsBool()));

		REQUIRE(!((int_val > bool_val).AsBool()));
		REQUIRE(!((int_val > uint_val).AsBool()));
		REQUIRE(!((int_val > double_val).AsBool()));

		REQUIRE(!((uint_val > bool_val).AsBool()));
		REQUIRE(!((uint_val > int_val).AsBool()));
		REQUIRE(!((uint_val > double_val).AsBool()));

		REQUIRE(!((double_val > bool_val).AsBool()));
		REQUIRE(!((double_val > int_val).AsBool()));
		REQUIRE(!((double_val > uint_val).AsBool()));
	}
	SECTION("Operator \"<=\"")
	{
		REQUIRE((string1_val <= string2_val).AsBool());

		REQUIRE((bool_val <= int_val).AsBool());
		REQUIRE((bool_val <= uint_val).AsBool());
		REQUIRE((bool_val <= double_val).AsBool());

		REQUIRE((int_val <= bool_val).AsBool());
		REQUIRE((int_val <= uint_val).AsBool());
		REQUIRE((int_val <= double_val).AsBool());

		REQUIRE((uint_val <= bool_val).AsBool());
		REQUIRE((uint_val <= int_val).AsBool());
		REQUIRE((uint_val <= double_val).AsBool());

		REQUIRE((double_val <= bool_val).AsBool());
		REQUIRE((double_val <= int_val).AsBool());
		REQUIRE((double_val <= uint_val).AsBool());
	}
	SECTION("Operator \">=\"")
	{
		REQUIRE((string1_val >= string2_val).AsBool());

		REQUIRE((bool_val >= int_val).AsBool());
		REQUIRE((bool_val >= uint_val).AsBool());
		REQUIRE((bool_val >= double_val).AsBool());

		REQUIRE((int_val >= bool_val).AsBool());
		REQUIRE((int_val >= uint_val).AsBool());
		REQUIRE((int_val >= double_val).AsBool());

		REQUIRE((uint_val >= bool_val).AsBool());
		REQUIRE((uint_val >= int_val).AsBool());
		REQUIRE((uint_val >= double_val).AsBool());

		REQUIRE((double_val >= bool_val).AsBool());
		REQUIRE((double_val >= int_val).AsBool());
		REQUIRE((double_val >= uint_val).AsBool());
	}
}

TEST_CASE("Value comparising between all different", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = static_cast<long long int>(-9);
	Value uint_val = static_cast<unsigned long long int>(9);
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	SECTION("Operator \"==\"")
	{
		REQUIRE(!((null_val == bool_val).AsBool()));
		REQUIRE(!((null_val == int_val).AsBool()));
		REQUIRE(!((null_val == uint_val).AsBool()));
		REQUIRE(!((null_val == double_val).AsBool()));
		REQUIRE(!((null_val == string1_val).AsBool()));

		REQUIRE(!((string1_val == string2_val).AsBool()));

		REQUIRE(!((bool_val == int_val).AsBool()));
		REQUIRE(!((bool_val == uint_val).AsBool()));
		REQUIRE(!((bool_val == double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val == string1_val, BadOperation);

		REQUIRE(!((int_val == bool_val).AsBool()));
		REQUIRE(!((int_val == uint_val).AsBool()));
		REQUIRE(!((int_val == double_val).AsBool()));		
		REQUIRE_THROWS_AS(int_val == string1_val, BadOperation);

		REQUIRE(!((uint_val == bool_val).AsBool()));
		REQUIRE(!((uint_val == int_val).AsBool()));
		REQUIRE(!((uint_val == double_val).AsBool()));
		REQUIRE_THROWS_AS(uint_val == string1_val, BadOperation);

		REQUIRE(!((double_val == bool_val).AsBool()));
		REQUIRE(!((double_val == int_val).AsBool()));
		REQUIRE(!((double_val == uint_val).AsBool()));
		REQUIRE_THROWS_AS(double_val == string1_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val == bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val == int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val == uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val == double_val, BadOperation);
	}
	SECTION("Operator \"!=\"")
	{
		REQUIRE((null_val != bool_val).AsBool());
		REQUIRE((null_val != int_val).AsBool());
		REQUIRE((null_val != uint_val).AsBool());
		REQUIRE((null_val != double_val).AsBool());
		REQUIRE((null_val != string1_val).AsBool());

		REQUIRE((string1_val != string2_val).AsBool());

		REQUIRE((bool_val != int_val).AsBool());
		REQUIRE((bool_val != uint_val).AsBool());
		REQUIRE((bool_val != double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val != string1_val, BadOperation);

		REQUIRE((int_val != bool_val).AsBool());
		REQUIRE((int_val != uint_val).AsBool());
		REQUIRE((int_val != double_val).AsBool());
		REQUIRE_THROWS_AS(int_val != string1_val, BadOperation);

		REQUIRE((uint_val != bool_val).AsBool());
		REQUIRE((uint_val != int_val).AsBool());
		REQUIRE((uint_val != double_val).AsBool());
		REQUIRE_THROWS_AS(uint_val != string1_val, BadOperation);

		REQUIRE((double_val != bool_val).AsBool());
		REQUIRE((double_val != int_val).AsBool());
		REQUIRE((double_val != uint_val).AsBool());
		REQUIRE_THROWS_AS(double_val != string1_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val != bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val != int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val != uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val != double_val, BadOperation);
	}
	SECTION("Operator \"<\"")
	{
		REQUIRE((string1_val < string2_val).AsBool());

		REQUIRE(!((bool_val < int_val).AsBool()));
		REQUIRE((bool_val < uint_val).AsBool());
		REQUIRE((bool_val < double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val < null_val, BadOperation);

		REQUIRE((int_val < bool_val).AsBool());
		REQUIRE((int_val < uint_val).AsBool());
		REQUIRE((int_val < double_val).AsBool());
		REQUIRE_THROWS_AS(int_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val < null_val, BadOperation);

		REQUIRE(!((uint_val < bool_val).AsBool()));
		REQUIRE(!((uint_val < int_val).AsBool()));
		REQUIRE(!((uint_val < double_val).AsBool()));
		REQUIRE_THROWS_AS(uint_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val < null_val, BadOperation);

		REQUIRE(!((double_val < bool_val).AsBool()));
		REQUIRE(!((double_val < int_val).AsBool()));
		REQUIRE((double_val < uint_val).AsBool());
		REQUIRE_THROWS_AS(double_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val < null_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val < bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < double_val, BadOperation);
	}
	SECTION("Operator \">\"")
	{
		REQUIRE(!((string1_val > string2_val).AsBool()));

		REQUIRE((bool_val > int_val).AsBool());
		REQUIRE(!((bool_val > uint_val).AsBool()));
		REQUIRE(!((bool_val > double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val > null_val, BadOperation);

		REQUIRE(!((int_val > bool_val).AsBool()));
		REQUIRE(!((int_val > uint_val).AsBool()));
		REQUIRE(!((int_val > double_val).AsBool()));
		REQUIRE_THROWS_AS(int_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val > null_val, BadOperation);

		REQUIRE((uint_val > bool_val).AsBool());
		REQUIRE((uint_val > int_val).AsBool());
		REQUIRE((uint_val > double_val).AsBool());
		REQUIRE_THROWS_AS(uint_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val > null_val, BadOperation);

		REQUIRE((double_val > bool_val).AsBool());
		REQUIRE((double_val > int_val).AsBool());
		REQUIRE(!((double_val > uint_val).AsBool()));
		REQUIRE_THROWS_AS(double_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val > null_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val > bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > double_val, BadOperation);
	}
	SECTION("Operator \"<=\"")
	{
		REQUIRE((string1_val <= string2_val).AsBool());

		REQUIRE(!((bool_val <= int_val).AsBool()));
		REQUIRE((bool_val <= uint_val).AsBool());
		REQUIRE((bool_val <= double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <= null_val, BadOperation);

		REQUIRE((int_val <= bool_val).AsBool());
		REQUIRE((int_val <= uint_val).AsBool());
		REQUIRE((int_val <= double_val).AsBool());
		REQUIRE_THROWS_AS(int_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val <= null_val, BadOperation);

		REQUIRE(!((uint_val <= bool_val).AsBool()));
		REQUIRE(!((uint_val <= int_val).AsBool()));
		REQUIRE(!((uint_val <= double_val).AsBool()));
		REQUIRE_THROWS_AS(uint_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val <= null_val, BadOperation);

		REQUIRE(!((double_val <= bool_val).AsBool()));
		REQUIRE(!((double_val <= int_val).AsBool()));
		REQUIRE((double_val <= uint_val).AsBool());
		REQUIRE_THROWS_AS(double_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <= null_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val <= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= double_val, BadOperation);
	}
	SECTION("Operator \">=\"")
	{
		REQUIRE(!((string1_val >= string2_val)).AsBool());

		REQUIRE((bool_val >= int_val).AsBool());
		REQUIRE(!((bool_val >= uint_val).AsBool()));
		REQUIRE(!((bool_val >= double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >= null_val, BadOperation);

		REQUIRE(!((int_val >= bool_val).AsBool()));
		REQUIRE(!((int_val >= uint_val).AsBool()));
		REQUIRE(!((int_val >= double_val).AsBool()));
		REQUIRE_THROWS_AS(int_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val >= null_val, BadOperation);

		REQUIRE((uint_val >= bool_val).AsBool());
		REQUIRE((uint_val >= int_val).AsBool());
		REQUIRE((uint_val >= double_val).AsBool());
		REQUIRE_THROWS_AS(uint_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val >= null_val, BadOperation);

		REQUIRE((double_val >= bool_val).AsBool());
		REQUIRE((double_val >= int_val).AsBool());
		REQUIRE(!((double_val >= uint_val).AsBool()));
		REQUIRE_THROWS_AS(double_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >= null_val, BadOperation);

		REQUIRE_THROWS_AS(string1_val >= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= double_val, BadOperation);
	}
}

TEST_CASE("Value class unary operations", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = static_cast<long long int>(-20);
	Value uint_val = static_cast<unsigned long long int>(20);
	Value double_val = 0.5;
	Value string_val = "This is test string";

	SECTION("Prefix operator \"+\"")
	{
		REQUIRE(((+bool_val) == true).AsBool());
		REQUIRE(((+int_val) == -20).AsBool());
		REQUIRE(((+uint_val) == 20).AsBool());
		REQUIRE(((+double_val) == 0.5).AsBool());
		REQUIRE_THROWS_AS(+string_val, BadOperation);
		REQUIRE_THROWS_AS(+null_val, BadOperation);
	}

	SECTION("Prefix operator \"-\"")
	{
		REQUIRE(((-bool_val) == -1).AsBool());
		REQUIRE(((-int_val) == 20).AsBool());
		REQUIRE(((-uint_val) == -20).AsBool());
		REQUIRE(((-double_val) == -0.5).AsBool());
		REQUIRE_THROWS_AS(-string_val, BadOperation);
		REQUIRE_THROWS_AS(-null_val, BadOperation);
	}

	SECTION("Prefix operator \"!\"")
	{
		REQUIRE(((!bool_val) == false).AsBool());
		REQUIRE(((!int_val) == 0).AsBool());
		REQUIRE(((!uint_val) == 0).AsBool());
		REQUIRE(((!double_val) == 0.0).AsBool());
		REQUIRE_THROWS_AS(!string_val, BadOperation);
		REQUIRE_THROWS_AS(!null_val, BadOperation);
	}

	SECTION("Prefix operator \"++\"")
	{
		REQUIRE(((++bool_val) == 2).AsBool());
		REQUIRE(((++int_val) == -19).AsBool());
		REQUIRE(((++uint_val) == 21).AsBool());
		REQUIRE(((++double_val) == 1.5).AsBool());

		REQUIRE((bool_val == 2).AsBool());
		REQUIRE((int_val == -19).AsBool());
		REQUIRE((uint_val == 21).AsBool());
		REQUIRE((double_val == 1.5).AsBool());

		REQUIRE_THROWS_AS(++string_val, BadOperation);
		REQUIRE_THROWS_AS(++null_val, BadOperation);
	}

	SECTION("Prefix operator \"--\"")
	{
		REQUIRE(((--bool_val) == false).AsBool());
		REQUIRE(((--int_val) == -21).AsBool());
		REQUIRE(((--uint_val) == 19).AsBool());
		REQUIRE(((--double_val) == -0.5).AsBool());

		REQUIRE((bool_val == false).AsBool());
		REQUIRE((int_val == -21).AsBool());
		REQUIRE((uint_val == 19).AsBool());
		REQUIRE((double_val == -0.5).AsBool());

		REQUIRE_THROWS_AS(--string_val, BadOperation);
		REQUIRE_THROWS_AS(--null_val, BadOperation);
	}

	SECTION("Postfix operator \"++\"")
	{
		REQUIRE(((bool_val++) == true).AsBool());
		REQUIRE(((int_val++) == -20).AsBool());
		REQUIRE(((uint_val++) == 20).AsBool());
		REQUIRE(((double_val++) == 0.5).AsBool());

		REQUIRE((bool_val == 2).AsBool());
		REQUIRE((int_val == -19).AsBool());
		REQUIRE((uint_val == 21).AsBool());
		REQUIRE((double_val == 1.5).AsBool());

		REQUIRE_THROWS_AS(string_val++, BadOperation);
		REQUIRE_THROWS_AS(null_val++, BadOperation);
	}

	SECTION("Postfix operator \"--\"")
	{
		REQUIRE(((bool_val--) == true).AsBool());
		REQUIRE(((int_val--) == -20).AsBool());
		REQUIRE(((uint_val--) == 20).AsBool());
		REQUIRE(((double_val--) == 0.5).AsBool());

		REQUIRE((bool_val == false).AsBool());
		REQUIRE((int_val == -21).AsBool());
		REQUIRE((uint_val == 19).AsBool());
		REQUIRE((double_val == -0.5).AsBool());

		REQUIRE_THROWS_AS(string_val--, BadOperation);
		REQUIRE_THROWS_AS(null_val--, BadOperation);
	}

}

TEST_CASE("Value class unary iterator operation \"--\", extrims", "[Value]")
{
	Value bool_val_min = false;
	Value uint_val_min = 0;
	Value int_val_min = (1ll << 63);

	SECTION("Prefix operator \"--\"")
	{
		--bool_val_min;
		--uint_val_min;
		--int_val_min;

		REQUIRE(bool_val_min.GetType() == Value::T_INT);
		REQUIRE(bool_val_min.AsInt() == -1);

		REQUIRE(int_val_min.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_min.AsDouble() == static_cast<double>((1ll << 63)) - 1);

		REQUIRE(uint_val_min.GetType() == Value::T_INT);
		REQUIRE(uint_val_min.AsInt() == -1);
	}

	SECTION("Postfix operator \"--\"")
	{
		bool_val_min--;
		uint_val_min--;
		int_val_min--;

		REQUIRE(bool_val_min.GetType() == Value::T_INT);
		REQUIRE(bool_val_min.AsInt() == -1);

		REQUIRE(int_val_min.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_min.AsDouble() == static_cast<double>(1ll << 63) - 1);

		REQUIRE(uint_val_min.GetType() == Value::T_INT);
		REQUIRE(uint_val_min.AsInt() == -1);
	}
}

TEST_CASE("Value class unary iterator operation \"++\", extrims", "[Value]")
{
	Value bool_val_max = true;
	Value int_val_max = ~(1ll << 63);
	Value uint_val_max = ~0ull;

	SECTION("Prefix operator \"--\"")
	{
		++bool_val_max;
		++int_val_max;
		++uint_val_max;

		REQUIRE(bool_val_max.GetType() == Value::T_UINT);
		REQUIRE(bool_val_max.AsUInt() == 2);

		REQUIRE(int_val_max.GetType() == Value::T_UINT);
		REQUIRE(int_val_max.AsUInt() == (1ull << 63));

		REQUIRE(uint_val_max.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val_max.AsDouble() == static_cast<double>(~0ull) + 1);
	}

	SECTION("Postfix operator \"--\"")
	{
		bool_val_max++;
		int_val_max++;
		uint_val_max++;

		REQUIRE(bool_val_max.GetType() == Value::T_UINT);
		REQUIRE(bool_val_max.AsUInt() == 2);

		REQUIRE(int_val_max.GetType() == Value::T_UINT);
		REQUIRE(int_val_max.AsUInt() == (1ull << 63));

		REQUIRE(uint_val_max.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val_max.AsDouble() == static_cast<double>(~0ull) + 1);
	}
}

TEST_CASE("Binary operator \"+=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	SECTION("Assagning to bool")
	{
		bool_val += 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = false;
		bool_val += int_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -6ll);

		bool_val = false;
		bool_val += uint_val;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 9ull);

		bool_val = false;
		bool_val += double_val;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 8ull);

		REQUIRE_THROWS_AS(bool_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val += null_val, BadOperation);
	}

	SECTION("Assagning to uint")
	{
		uint_val += 20ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 29ull);

		uint_val = 9ull;
		uint_val += int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 3ull);

		uint_val = 9ull;
		uint_val += bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 9ull);

		uint_val = 9ull;
		uint_val += double_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 17ull);

		REQUIRE_THROWS_AS(uint_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val += null_val, BadOperation);
	}

	SECTION("Assagning to int")
	{
		int_val += 20ull;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 14ll);

		int_val = -6ll;
		int_val += uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 3ll);

		int_val = -6ll;
		int_val += bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -6ll);

		int_val = -6ll;
		int_val += double_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 2ll);

		REQUIRE_THROWS_AS(int_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val += null_val, BadOperation);
	}

	SECTION("Assagning to double")
	{
		double_val += 9.2;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == 18.0);

		double_val = 8.8;
		double_val += int_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 - 6));

		double_val = 8.8;
		double_val += bool_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 + 0));

		double_val = 8.8;
		double_val += uint_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 + 9));

		REQUIRE_THROWS_AS(double_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val += null_val, BadOperation);
	}

	SECTION("Assagning to string")
	{
		REQUIRE_THROWS_AS(string1_val += null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += uint_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += double_val, BadOperation);

		string1_val += string2_val;
		REQUIRE(string1_val.GetType() == Value::T_STRING);
		REQUIRE(string1_val.AsString() == "String1String2");
	}
}

TEST_CASE("Binary operator \"-=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Substructing from bool")
	{
		bool_val = true;
		bool_val -= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = false;
		bool_val -= int_val;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 6ull);

		bool_val = false;
		bool_val -= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -9ll);

		bool_val = false;
		bool_val -= double_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -8ll);

		REQUIRE_THROWS_AS(bool_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val -= null_val, BadOperation);
	}

	SECTION("Substructing from uint")
	{
		uint_val -= 4ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 5ull);

		uint_val = 9ull;
		uint_val -= int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 15ull);

		uint_val = 9ull;
		uint_val -= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 9ull);

		uint_val = 9ull;
		uint_val -= double_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0ll);

		REQUIRE_THROWS_AS(uint_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val -= null_val, BadOperation);
	}

	SECTION("Substructing from int")
	{
		int_val -= 20ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -26ll);

		int_val = -6ll;
		int_val -= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -15ll);

		int_val = -6ll;
		int_val -= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -6ll);

		int_val = -6ll;
		int_val -= double_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -14ll);

		REQUIRE_THROWS_AS(int_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(int_val -= null_val, BadOperation);
	}

	SECTION("Substructing from double")
	{
		double_val -= 9.2;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 - 9.2));

		double_val = 8.8;
		double_val -= int_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 - -6));

		double_val = 8.8;
		double_val -= bool_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 - 0));

		double_val = 8.8;
		double_val -= uint_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 - 9));

		REQUIRE_THROWS_AS(double_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(double_val -= null_val, BadOperation);
	}

	SECTION("Assagning to string")
	{
		REQUIRE_THROWS_AS(string_val -= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"*=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Multiplying bool")
	{
		bool_val *= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val *= int_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -6ll);

		bool_val = true;
		bool_val *= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 9ull);

		bool_val = true;
		bool_val *= double_val;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 8ull);

		REQUIRE_THROWS_AS(bool_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val *= null_val, BadOperation);
	}

	SECTION("Multiplying uint")
	{
		uint_val *= 20ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 180ull);

		uint_val = 9ull;
		uint_val *= int_val;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -54ll);

		uint_val = 9ull;
		uint_val *= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0ull);

		uint_val = 9ull;
		uint_val *= double_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 79ull);

		REQUIRE_THROWS_AS(uint_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val *= null_val, BadOperation);
	}

	SECTION("Multiplying int")
	{
		int_val *= 20ull;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -120ll);

		int_val = -6ll;
		int_val *= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -54ll);

		int_val = -6ll;
		int_val *= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		int_val = -6ll;
		int_val *= double_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -52ll);

		REQUIRE_THROWS_AS(int_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(int_val *= null_val, BadOperation);
	}

	SECTION("Multiplying double")
	{
		double_val *= 9.2;
	
		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 * 9.2));
	
		double_val = 8.8;
		double_val *= int_val;
	
		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 * -6));
	
		double_val = 8.8;
		double_val *= bool_val;
	
		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 * 0));
	
		double_val = 8.8;
		double_val *= uint_val;
	
		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 * 9));
	
		REQUIRE_THROWS_AS(double_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(double_val *= null_val, BadOperation);
	}
	
	SECTION("Multiplying string")
	{
		REQUIRE_THROWS_AS(string_val *= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"/=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Dividing bool")
	{
		bool_val /= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val /= int_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 0ll);

		bool_val = true;
		bool_val /= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val /= double_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val /= false, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= 0ull, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= 0ll, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= 0.0, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= string_val, BadOperation);
	}

	SECTION("Dividing uint")
	{
		uint_val /= 2ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 4ull);

		uint_val = 9ull;
		uint_val /= int_val;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -1ll);

		uint_val = 9ull;
		uint_val /= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 9ull);

		uint_val = 9ull;
		uint_val /= double_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 1ull);

		REQUIRE_THROWS_AS(uint_val /= false, BadOperation);
		REQUIRE_THROWS_AS(uint_val /= 0ull, BadOperation);
		REQUIRE_THROWS_AS(uint_val /= 0ll, BadOperation);
		REQUIRE_THROWS_AS(uint_val /= 0.0, BadOperation);
		REQUIRE_THROWS_AS(uint_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val /= string_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		int_val /= 4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -1ll);

		int_val = -6ll;
		int_val /= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		int_val = -6ll;
		int_val /= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -6ll);

		int_val = -6ll;
		int_val /= double_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		REQUIRE_THROWS_AS(int_val /= false, BadOperation);
		REQUIRE_THROWS_AS(int_val /= 0ull, BadOperation);
		REQUIRE_THROWS_AS(int_val /= 0ll, BadOperation);
		REQUIRE_THROWS_AS(int_val /= 0.0, BadOperation);
		REQUIRE_THROWS_AS(int_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val /= string_val, BadOperation);
	}

	SECTION("Dividing double")
	{
		double_val /= 9.2;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 / 9.2));

		double_val = 8.8;
		double_val /= int_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 / -6));

		double_val = 8.8;
		double_val /= bool_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 / 1));

		double_val = 8.8;
		double_val /= uint_val;

		REQUIRE(double_val.GetType() == Value::T_DOUBLE);
		REQUIRE(double_val.AsDouble() == (8.8 / 9));

		REQUIRE_THROWS_AS(double_val /= false, BadOperation);
		REQUIRE_THROWS_AS(double_val /= 0ull, BadOperation);
		REQUIRE_THROWS_AS(double_val /= 0ll, BadOperation);
		REQUIRE_THROWS_AS(double_val /= 0.0, BadOperation);
		REQUIRE_THROWS_AS(double_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val /= string_val, BadOperation);
	}

	SECTION("Dividing string")
	{
		REQUIRE_THROWS_AS(string_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val /= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val /= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val /= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val /= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val /= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"+=\", extrims", "[Value]")
{
	const Value min_bool = false;
	const Value max_bool = true;
	const Value min_int = (1ll << 63);
	const Value max_int = ~(1ll << 63);
	const Value min_uint = 0ull;
	const Value max_uint = ~0ull;

	SECTION("Overflow of bool")
	{
		Value bool_val;

		bool_val = min_bool;
		bool_val += -1;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -1ll);

		bool_val = min_bool;
		bool_val += (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		bool_val = max_bool;
		bool_val += 1;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 2ull);

		bool_val = max_bool;
		bool_val += ~0ull;

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) + 1.0));
	}

	SECTION("Overflow of uint")
	{
		Value uint_val;

		uint_val = min_uint;
		uint_val += -1;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -1ll);

		uint_val = min_uint;
		uint_val += (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		uint_val = max_uint;
		uint_val += 1;

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (static_cast<double>(~0ull) + 1.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val += -1;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) - 1.0));

		int_val = max_int;
		int_val += 1;

		REQUIRE(int_val.GetType() == Value::T_UINT);
		REQUIRE(int_val.AsUInt() == (~(1ull << 63) + 1ull));

		int_val = max_int;
		int_val += ~0ull;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) + static_cast<double>(~0ull)));

		int_val = min_int;
		int_val += static_cast<double>(~0ull) * 2.0;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) + static_cast<double>(~0ull)));
	}
}

TEST_CASE("Binary operator \"-=\", extrims", "[Value]")
{
	const Value min_bool = false;
	const Value max_bool = true;
	const Value min_int = (1ll << 63);
	const Value max_int = ~(1ll << 63);
	const Value min_uint = 0ull;
	const Value max_uint = ~0ull;

	SECTION("Overflow of bool")
	{
		Value bool_val;

		bool_val = min_bool;
		bool_val -= 1;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -1ll);

		bool_val = min_bool;
		bool_val -= (static_cast<double>(~0ull) + 1.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		bool_val = max_bool;
		bool_val -= -1;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 2ull);

		bool_val = max_bool;
		bool_val -= -static_cast<double>(~0ull) * 2;

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2 + 1.0));
	}

	SECTION("Overflow of uint")
	{
		Value uint_val;

		uint_val = min_uint;
		uint_val -= 1;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -1ll);

		uint_val = min_uint;
		uint_val -= (static_cast<double>(~0ull) + 1.0);

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		uint_val = max_uint;
		uint_val -= -1;

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (static_cast<double>(~0ull) + 1.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val -= 1;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) - 1.0));

		int_val = max_int;
		int_val -= -1;

		REQUIRE(int_val.GetType() == Value::T_UINT);
		REQUIRE(int_val.AsUInt() == (~(1ull << 63) + 1ull));

		int_val = max_int;
		int_val -= -static_cast<double>(~0ull);

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) + static_cast<double>(~0ull)));

		int_val = min_int;
		int_val -= -static_cast<double>(~0ull) * 2.0;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) + static_cast<double>(~0ull)));
	}
}

TEST_CASE("Binary operator \"*=\", extrims", "[Value]")
{
	const Value min_bool = false;
	const Value max_bool = true;
	const Value min_int = (1ll << 63);
	const Value max_int = ~(1ll << 63);
	const Value min_uint = 0ull;
	const Value max_uint = ~0ull;

	SECTION("Overflow of bool")
	{
		Value bool_val;

		bool_val = max_bool;
		bool_val *= -10;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -10ll);

		bool_val = max_bool;
		bool_val *= (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		bool_val = max_bool;
		bool_val *= 20;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 20ull);

		bool_val = max_bool;
		bool_val *= (static_cast<double>(~0ull) * 2.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of uint")
	{
		Value uint_val;

		uint_val = 1ull;
		uint_val *= -10;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -10ll);

		uint_val = 1ull;
		uint_val *= (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		uint_val = max_uint;
		uint_val *= 2;

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val *= 2;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) * 2.0));

		int_val = max_int;
		int_val *= 1.5625;

		REQUIRE(int_val.GetType() == Value::T_UINT);
		REQUIRE(int_val.AsUInt() == (~(1ull << 63) * 1.5625));

		int_val = max_int;
		int_val *= 4;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) * 4.0));

		int_val = min_int;
		int_val *= -4;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) * 4.0));
	}
}

TEST_CASE("Binary operator \"/=\", extrims", "[Value]")
{
	const Value min_bool = false;
	const Value max_bool = true;
	const Value min_int = (1ll << 63);
	const Value max_int = ~(1ll << 63);
	const Value min_uint = 0ull;
	const Value max_uint = ~0ull;

	SECTION("Overflow of bool")
	{
		Value bool_val;

		bool_val = max_bool;
		bool_val /= -1.0 / 10;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -10ll);

		bool_val = max_bool;
		bool_val /= 1.0 / (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		bool_val = max_bool;
		bool_val /= 1.0 / 20;

		REQUIRE(bool_val.GetType() == Value::T_UINT);
		REQUIRE(bool_val.AsUInt() == 20ull);

		bool_val = max_bool;
		bool_val /= 1.0 / (static_cast<double>(~0ull) * 2.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of uint")
	{
		Value uint_val;

		uint_val = 1ull;
		uint_val /= -1.0 / 10;

		REQUIRE(uint_val.GetType() == Value::T_INT);
		REQUIRE(uint_val.AsInt() == -10ll);

		uint_val = 1ull;
		uint_val /= 1.0 / (-static_cast<double>(~0ull) - 1.0);

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (-static_cast<double>(~0ull) - 1.0));

		uint_val = max_uint;
		uint_val /= 0.5;

		REQUIRE(uint_val.GetType() == Value::T_DOUBLE);
		REQUIRE(uint_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val /= 0.5;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) * 2.0));

		int_val = max_int;
		int_val /= 0.64;

		REQUIRE(int_val.GetType() == Value::T_UINT);
		REQUIRE(int_val.AsUInt() == (~(1ull << 63) / 0.64));

		int_val = max_int;
		int_val /= 0.25;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) * 4.0));

		int_val = min_int;
		int_val /= -0.25;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) * 4.0));
	}
}

TEST_CASE("Binary operator \"%=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double1_val = 8.8;
	Value double2_val = 4.1;
	Value string_val = "String1";

	SECTION("Dividing bool")
	{
		bool_val = true;
		bool_val %= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val %= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val %= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val %= false, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= 0ull, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= 0ll, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= 0.0, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= string_val, BadOperation);
	}

	SECTION("Dividing uint")
	{
		uint_val %= 4ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 1ull);

		uint_val = 9ull;
		uint_val %= int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 3ull);

		uint_val = 9ull;
		uint_val %= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0ull);

		REQUIRE_THROWS_AS(uint_val %= false, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= 0ull, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= 0ll, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= 0.0, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val %= string_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		int_val %= -4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -2ll);

		int_val = -6ll;
		int_val %= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -6ll);

		int_val = -6ll;
		int_val %= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		REQUIRE_THROWS_AS(int_val %= false, BadOperation);
		REQUIRE_THROWS_AS(int_val %= 0ull, BadOperation);
		REQUIRE_THROWS_AS(int_val %= 0ll, BadOperation);
		REQUIRE_THROWS_AS(int_val %= 0.0, BadOperation);
		REQUIRE_THROWS_AS(int_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val %= string_val, BadOperation);
	}

	SECTION("Dividing double")
	{
		double1_val %= 3.2;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 2.4) < 0.00000000000001);

		double1_val = 8.8;
		double1_val %= int_val;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 2.8) < 0.00000000000001);

		double1_val = 8.8;
		double1_val %= bool_val;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 0.8) < 0.00000000000001);

		double1_val = 8.8;
		double1_val %= uint_val;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 8.8) < 0.00000000000001);

		double1_val = 8.8;
		double1_val %= double2_val;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 0.6) < 0.00000000000001);

		REQUIRE_THROWS_AS(double1_val %= false, BadOperation);
		REQUIRE_THROWS_AS(double1_val %= 0ull, BadOperation);
		REQUIRE_THROWS_AS(double1_val %= 0ll, BadOperation);
		REQUIRE_THROWS_AS(double1_val %= 0.0, BadOperation);
		REQUIRE_THROWS_AS(double1_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(double1_val %= string_val, BadOperation);
	}

	SECTION("Dividing string")
	{
		REQUIRE_THROWS_AS(string_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"&=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
	Value uint_val = 0x01011010ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Changing bool")
	{
		bool_val = true;
		bool_val &= 0;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val &= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val &= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val &= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val &= string_val, BadOperation);
	}

	SECTION("Changing uint")
	{
		uint_val &= 0x11110000ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x01010000ull);

		uint_val = 0x01011010ull;
		uint_val &= int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x00001000ull);

		uint_val = 0x01011010ull;
		uint_val &= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0);

		REQUIRE_THROWS_AS(uint_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val &= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val &= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00100000ll);

		int_val = 0x00101100ll;
		int_val &= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00001000ll);

		int_val = 0x00101100ll;
		int_val &= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		REQUIRE_THROWS_AS(int_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(int_val &= string_val, BadOperation);
	}

	SECTION("Changing double")
	{
		REQUIRE_THROWS_AS(double_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val &= bool_val, BadOperation);
		REQUIRE_THROWS_AS(double_val &= uint_val, BadOperation);
		REQUIRE_THROWS_AS(double_val &= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val &= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val &= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"|=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
	Value uint_val = 0x01011010ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Changing bool")
	{
		bool_val = true;
		bool_val |= 0;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val |= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val |= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val |= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val |= string_val, BadOperation);
	}

	SECTION("Changing uint")
	{
		uint_val |= 0x11110000ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x11111010ull);

		uint_val = 0x01011010ull;
		uint_val |= int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x01111110ull);

		uint_val = 0x01011010ull;
		uint_val |= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x01011011ull);

		REQUIRE_THROWS_AS(uint_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val |= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val |= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x11111100ll);

		int_val = 0x00101100ll;
		int_val |= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x01111110ll);

		int_val = 0x00101100ll;
		int_val |= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00101101ll);

		REQUIRE_THROWS_AS(int_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(int_val |= string_val, BadOperation);
	}

	SECTION("Changing double")
	{
		REQUIRE_THROWS_AS(double_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val |= bool_val, BadOperation);
		REQUIRE_THROWS_AS(double_val |= uint_val, BadOperation);
		REQUIRE_THROWS_AS(double_val |= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val |= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val |= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"^=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val =  0x00101100ll;
	Value uint_val = 0x01011010ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Changing bool")
	{
		bool_val = true;
		bool_val ^= 0;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val ^= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val ^= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val ^= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val ^= string_val, BadOperation);
	}

	SECTION("Changing uint")
	{
		uint_val ^= 0x11110000ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x10101010ull);

		uint_val = 0x01011010ull;
		uint_val ^= int_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x01110110ull);

		uint_val = 0x01011010ull;
		uint_val ^= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x01011011ull);

		REQUIRE_THROWS_AS(uint_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val ^= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val ^= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x11011100ll);

		int_val = 0x00101100ll;
		int_val ^= uint_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x01110110ll);

		int_val = 0x00101100ll;
		int_val ^= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00101101ll);

		REQUIRE_THROWS_AS(int_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(int_val ^= string_val, BadOperation);
	}

	SECTION("Changing double")
	{
		REQUIRE_THROWS_AS(double_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= bool_val, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= uint_val, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"<<=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
	Value uint_val = 0x01011010ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Shifting bool")
	{
		bool_val = true;
		bool_val <<= 0;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val <<= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val <<= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val <<= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <<= string_val, BadOperation);
	}

	SECTION("Shifting uint")
	{
		uint_val <<= 4ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x10110100ull);

		uint_val = 0x01011010ull;
		uint_val <<= 4ll;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x10110100ull);

		uint_val = 0x01011010ull;
		uint_val <<= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x02022020ull);

		REQUIRE_THROWS_AS(uint_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val <<= string_val, BadOperation);
	}

	SECTION("Shifting int")
	{
		int_val <<= 4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x01011000ll);

		int_val = 0x00101100ll;
		int_val <<= 4ull;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x01011000ll);

		int_val = 0x00101100ll;
		int_val <<= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00202200ll);

		REQUIRE_THROWS_AS(int_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(int_val <<= string_val, BadOperation);
	}

	SECTION("Shifting double")
	{
		REQUIRE_THROWS_AS(double_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= bool_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= uint_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= string_val, BadOperation);
	}

	SECTION("Shifting string")
	{
		REQUIRE_THROWS_AS(string_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \">>=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
	Value uint_val = 0x01011010ull;
	Value double_val = 8.8;
	Value string_val = "String1";

	SECTION("Shifting bool")
	{
		bool_val = true;
		bool_val >>= 0;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val >>= 1;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		bool_val = true;
		bool_val >>= int_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(bool_val.AsBool());

		bool_val = true;
		bool_val >>= uint_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >>= string_val, BadOperation);
	}

	SECTION("Shifting uint")
	{
		uint_val >>= 4ull;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x00101101ull);

		uint_val = 0x01011010ull;
		uint_val >>= 4ll;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x00101101ull);

		uint_val = 0x01011010ull;
		uint_val >>= bool_val;

		REQUIRE(uint_val.GetType() == Value::T_UINT);
		REQUIRE(uint_val.AsUInt() == 0x00808808ull);

		REQUIRE_THROWS_AS(uint_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(uint_val >>= string_val, BadOperation);
	}

	SECTION("Shifting int")
	{
		int_val >>= 4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00010110ll);

		int_val = 0x00101100ll;
		int_val >>= 4ull;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00010110ll);

		int_val = 0x00101100ll;
		int_val >>= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x0080880ll);

		REQUIRE_THROWS_AS(int_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(int_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(int_val >>= string_val, BadOperation);
	}

	SECTION("Shifting double")
	{
		REQUIRE_THROWS_AS(double_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= bool_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= uint_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= string_val, BadOperation);
	}

	SECTION("Shifting string")
	{
		REQUIRE_THROWS_AS(string_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= uint_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"+\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Adding to bool")
	{
		test_val = bool_val + false;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val + uint_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 10ull);

		test_val = bool_val + int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -5ll);

		test_val = bool_val + double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 9.8);

		REQUIRE_THROWS_AS(test_val = bool_val + string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val + null_val, BadOperation);
	}

	SECTION("Adding to uint")
	{
		test_val = uint_val + 10ull;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 19ull);

		test_val = uint_val + bool_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 10ull);

		test_val = uint_val + int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 3ll);

		test_val = uint_val + double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 17.8);

		REQUIRE_THROWS_AS(test_val = uint_val + string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val + null_val, BadOperation);
	}

	SECTION("Adding to int")
	{
		test_val = int_val + -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -26ll);

		test_val = int_val + uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 3ll);

		test_val = int_val + bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -5ll);

		test_val = int_val + double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - 6.0);

		REQUIRE_THROWS_AS(test_val = int_val + string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val + null_val, BadOperation);
	}

	SECTION("Adding to double")
	{
		test_val = double_val + 3.1;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 11.9);

		test_val = double_val + uint_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 17.8);

		test_val = double_val + int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - 6.0);

		test_val = double_val + bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 9.8);
		
		REQUIRE_THROWS_AS(test_val = double_val + string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val + null_val, BadOperation);
	}

	SECTION("Assagning to string")
	{
		REQUIRE_THROWS_AS(test_val = string1_val + null_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val + bool_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val + int_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val + uint_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val + double_val, BadOperation);

		test_val = string1_val + string2_val;
		REQUIRE(test_val.GetType() == Value::T_STRING);
		REQUIRE(test_val.AsString() == "String1String2");
	}
}

TEST_CASE("Binary operator \"-\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Substructing from bool")
	{
		test_val = bool_val - false;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val - uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -8ll);

		test_val = bool_val - int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 7ll);

		test_val = bool_val - double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 1.0 - 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val - string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val - null_val, BadOperation);
	}

	SECTION("Substructing from uint")
	{
		test_val = uint_val - 5ull;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 4ull);

		test_val = uint_val - bool_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 8ull);

		test_val = uint_val - int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 15ll);

		test_val = uint_val - double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 9.0 - 8.8);

		REQUIRE_THROWS_AS(test_val = uint_val - string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val - null_val, BadOperation);
	}

	SECTION("Substructing from int")
	{
		test_val = int_val - 20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -26ll);

		test_val = int_val - uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -15ll);

		test_val = int_val - bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -7ll);

		test_val = int_val - double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == -6.0 - 8.8);

		REQUIRE_THROWS_AS(test_val = int_val - string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val - null_val, BadOperation);
	}

	SECTION("Substructing from double")
	{
		test_val = double_val - 3.1;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - 3.1);

		test_val = double_val - uint_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - 9.0);

		test_val = double_val - int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - -6.0);

		test_val = double_val - bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 - 1.0);

		REQUIRE_THROWS_AS(test_val = double_val - string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val - null_val, BadOperation);
	}

	SECTION("Substructing from string")
	{
		REQUIRE_THROWS_AS(test_val = string1_val - null_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - bool_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - int_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - uint_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"*\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Multiplying bool")
	{
		test_val = bool_val * true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val * uint_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 9ull);

		test_val = bool_val * int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = bool_val * double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val * string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val * null_val, BadOperation);
	}

	SECTION("Multiplying uint")
	{
		test_val = uint_val * 10ull;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 90ull);

		test_val = uint_val * bool_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 9ull);

		test_val = uint_val * int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -54ll);

		test_val = uint_val * double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 * 9.0);

		REQUIRE_THROWS_AS(test_val = uint_val * string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val * null_val, BadOperation);
	}

	SECTION("Multiplying int")
	{
		test_val = int_val * -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 120ll);

		test_val = int_val * uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -54ll);

		test_val = int_val * bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val * double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 * -6.0);

		REQUIRE_THROWS_AS(test_val = int_val * string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val * null_val, BadOperation);
	}

	SECTION("Multiplying double")
	{
		test_val = double_val * 3.1;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 * 3.1);

		test_val = double_val * uint_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 * 9.0);

		test_val = double_val * int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 * -6.0);

		test_val = double_val * bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8);

		REQUIRE_THROWS_AS(test_val = double_val * string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val * null_val, BadOperation);
	}

	SECTION("Multiplying string")
	{
		REQUIRE_THROWS_AS(test_val = string1_val * null_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * bool_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * int_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * uint_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"/\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Dividing bool")
	{
		test_val = bool_val / true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val / uint_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 0ull);

		test_val = bool_val / int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = bool_val / double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 1.0 / 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val / false, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / null_val, BadOperation);
	}

	SECTION("Dividing uint")
	{
		test_val = uint_val / 10ull;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 0ull);

		test_val = uint_val / bool_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 9ull);

		test_val = uint_val / int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -1ll);

		test_val = uint_val / double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 9.0 / 8.8);

		REQUIRE_THROWS_AS(test_val = uint_val / false, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val / 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val / 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val / 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val / string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val / null_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		test_val = int_val / -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = int_val / uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = int_val / bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val / double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == -6.0 / 8.8);

		REQUIRE_THROWS_AS(test_val = int_val / false, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val / 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val / 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val / 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val / string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val / null_val, BadOperation);
	}

	SECTION("Dividing double")
	{
		test_val = double_val / 3.1;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 / 3.1);

		test_val = double_val / uint_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 / 9.0);

		test_val = double_val / int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 / -6.0);

		test_val = double_val / bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8);

		REQUIRE_THROWS_AS(test_val = double_val / false, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val / 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val / 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val / 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val / string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val / null_val, BadOperation);
	}

	SECTION("Dividing string")
	{
		REQUIRE_THROWS_AS(test_val = string1_val / null_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / bool_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / int_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / uint_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"%\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value uint_val = 9ull;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Dividing bool")
	{
		test_val = bool_val % true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(!test_val.AsBool());

		test_val = bool_val % uint_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 1ull);

		test_val = bool_val % int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 1ll);

		test_val = bool_val % double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(1.0, 8.8));

		REQUIRE_THROWS_AS(test_val = bool_val % false, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % null_val, BadOperation);
	}

	SECTION("Dividing uint")
	{
		test_val = uint_val % 10ull;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 9ull);

		test_val = uint_val % bool_val;
		REQUIRE(test_val.GetType() == Value::T_UINT);
		REQUIRE(test_val.AsUInt() == 0ull);

		test_val = uint_val % int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 3ll);

		test_val = uint_val % double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(9.0, 8.8));

		REQUIRE_THROWS_AS(test_val = uint_val % false, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val % 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val % 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val % 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val % string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = uint_val % null_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		test_val = int_val % -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val % uint_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val % bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = int_val % double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(-6.0, 8.8));

		REQUIRE_THROWS_AS(test_val = int_val % false, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val % 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val % 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val % 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val % string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = int_val % null_val, BadOperation);
	}

	SECTION("Dividing double")
	{
		test_val = double_val % 3.1;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, 3.1));

		test_val = double_val % uint_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, 9.0));

		test_val = double_val % int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, -6.0));

		test_val = double_val % bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, 1.0));

		REQUIRE_THROWS_AS(test_val = double_val % false, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val % 0ull, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val % 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val % 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val % string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = double_val % null_val, BadOperation);
	}

	SECTION("Dividing string")
	{
		REQUIRE_THROWS_AS(test_val = string1_val % null_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % bool_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % int_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % uint_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % string2_val, BadOperation);
	}
}
