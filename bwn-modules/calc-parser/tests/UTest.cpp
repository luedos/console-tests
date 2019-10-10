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
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 125);

		test_val = "0xFF";
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0xFF);

		test_val = "07777";
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 07777);

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
		test_val.ChangeToType(Value::T_INT);

		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 125);

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
	Value double_val = 1.0;
	Value string1_val = "String1";
	Value string2_val = "String1";

	SECTION("Operator \"==\"")
	{
		REQUIRE((string1_val == string2_val).AsBool());

		REQUIRE((bool_val == int_val).AsBool());
		REQUIRE((bool_val == double_val).AsBool());

		REQUIRE((int_val == bool_val).AsBool());
		REQUIRE((int_val == double_val).AsBool());

		REQUIRE((double_val == bool_val).AsBool());
		REQUIRE((double_val == int_val).AsBool());
	}
	SECTION("Operator \"!=\"")
	{
		REQUIRE(!((string1_val != string2_val).AsBool()));

		REQUIRE(!((bool_val != int_val).AsBool()));
		REQUIRE(!((bool_val != double_val).AsBool()));

		REQUIRE(!((int_val != bool_val).AsBool()));
		REQUIRE(!((int_val != double_val).AsBool()));

		REQUIRE(!((double_val != bool_val).AsBool()));
		REQUIRE(!((double_val != int_val).AsBool()));
	}
	SECTION("Operator \"<\"")
	{
		REQUIRE(!((string1_val < string2_val).AsBool()));

		REQUIRE(!((bool_val < int_val).AsBool()));
		REQUIRE(!((bool_val < double_val).AsBool()));

		REQUIRE(!((int_val < bool_val).AsBool()));
		REQUIRE(!((int_val < double_val).AsBool()));

		REQUIRE(!((double_val < bool_val).AsBool()));
		REQUIRE(!((double_val < int_val).AsBool()));
	}
	SECTION("Operator \">\"")
	{
		REQUIRE(!((string1_val > string2_val).AsBool()));

		REQUIRE(!((bool_val > int_val).AsBool()));
		REQUIRE(!((bool_val > double_val).AsBool()));

		REQUIRE(!((int_val > bool_val).AsBool()));
		REQUIRE(!((int_val > double_val).AsBool()));

		REQUIRE(!((double_val > bool_val).AsBool()));
		REQUIRE(!((double_val > int_val).AsBool()));
	}
	SECTION("Operator \"<=\"")
	{
		REQUIRE((string1_val <= string2_val).AsBool());

		REQUIRE((bool_val <= int_val).AsBool());
		REQUIRE((bool_val <= double_val).AsBool());

		REQUIRE((int_val <= bool_val).AsBool());
		REQUIRE((int_val <= double_val).AsBool());

		REQUIRE((double_val <= bool_val).AsBool());
		REQUIRE((double_val <= int_val).AsBool());
	}
	SECTION("Operator \">=\"")
	{
		REQUIRE((string1_val >= string2_val).AsBool());

		REQUIRE((bool_val >= int_val).AsBool());
		REQUIRE((bool_val >= double_val).AsBool());

		REQUIRE((int_val >= bool_val).AsBool());
		REQUIRE((int_val >= double_val).AsBool());

		REQUIRE((double_val >= bool_val).AsBool());
		REQUIRE((double_val >= int_val).AsBool());
	}
}

TEST_CASE("Value comparising between all different", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = static_cast<long long int>(-9);
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	SECTION("Operator \"==\"")
	{
		REQUIRE(!((null_val == bool_val).AsBool()));
		REQUIRE(!((null_val == int_val).AsBool()));
		REQUIRE(!((null_val == double_val).AsBool()));
		REQUIRE(!((null_val == string1_val).AsBool()));

		REQUIRE(!((bool_val == null_val).AsBool()));
		REQUIRE(!((bool_val == int_val).AsBool()));
		REQUIRE(!((bool_val == double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val == string1_val, BadOperation);

		REQUIRE(!((int_val == null_val).AsBool()));
		REQUIRE(!((int_val == bool_val).AsBool()));
		REQUIRE(!((int_val == double_val).AsBool()));
		REQUIRE_THROWS_AS(int_val == string1_val, BadOperation);

		REQUIRE(!((double_val == bool_val).AsBool()));
		REQUIRE(!((double_val == int_val).AsBool()));
		REQUIRE(!((double_val == null_val).AsBool()));
		REQUIRE_THROWS_AS(double_val == string1_val, BadOperation);

		REQUIRE(!((string1_val == null_val).AsBool()));
		REQUIRE(!((string1_val == string2_val).AsBool()));
		REQUIRE_THROWS_AS(string1_val == bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val == int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val == double_val, BadOperation);
	}
	SECTION("Operator \"!=\"")
	{
		REQUIRE((null_val != bool_val).AsBool());
		REQUIRE((null_val != int_val).AsBool());
		REQUIRE((null_val != double_val).AsBool());
		REQUIRE((null_val != string1_val).AsBool());

		REQUIRE((bool_val != null_val).AsBool());
		REQUIRE((bool_val != int_val).AsBool());
		REQUIRE((bool_val != double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val != string1_val, BadOperation);

		REQUIRE((int_val != null_val).AsBool());
		REQUIRE((int_val != bool_val).AsBool());
		REQUIRE((int_val != double_val).AsBool());
		REQUIRE_THROWS_AS(int_val != string1_val, BadOperation);

		REQUIRE((double_val != null_val).AsBool());
		REQUIRE((double_val != bool_val).AsBool());
		REQUIRE((double_val != int_val).AsBool());
		REQUIRE_THROWS_AS(double_val != string1_val, BadOperation);

		REQUIRE((string1_val != null_val).AsBool());
		REQUIRE((string1_val != string2_val).AsBool());
		REQUIRE_THROWS_AS(string1_val != bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val != int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val != double_val, BadOperation);
	}
	SECTION("Operator \"<\"")
	{
		REQUIRE(!((bool_val < int_val).AsBool()));
		REQUIRE((bool_val < double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val < null_val, BadOperation);

		REQUIRE((int_val < bool_val).AsBool());
		REQUIRE((int_val < double_val).AsBool());
		REQUIRE_THROWS_AS(int_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val < null_val, BadOperation);

		REQUIRE(!((double_val < bool_val).AsBool()));
		REQUIRE(!((double_val < int_val).AsBool()));
		REQUIRE_THROWS_AS(double_val < string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val < null_val, BadOperation);

		REQUIRE((string1_val < string2_val).AsBool());
		REQUIRE_THROWS_AS(string1_val < null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val < double_val, BadOperation);
	}
	SECTION("Operator \">\"")
	{
		REQUIRE((bool_val > int_val).AsBool());
		REQUIRE(!((bool_val > double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val > null_val, BadOperation);

		REQUIRE(!((int_val > bool_val).AsBool()));
		REQUIRE(!((int_val > double_val).AsBool()));
		REQUIRE_THROWS_AS(int_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val > null_val, BadOperation);

		REQUIRE((double_val > bool_val).AsBool());
		REQUIRE((double_val > int_val).AsBool());
		REQUIRE_THROWS_AS(double_val > string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val > null_val, BadOperation);

		REQUIRE(!((string1_val > string2_val).AsBool()));
		REQUIRE_THROWS_AS(string1_val > null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val > double_val, BadOperation);
	}
	SECTION("Operator \"<=\"")
	{
		REQUIRE(!((bool_val <= int_val).AsBool()));
		REQUIRE((bool_val <= double_val).AsBool());
		REQUIRE_THROWS_AS(bool_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <= null_val, BadOperation);

		REQUIRE((int_val <= bool_val).AsBool());
		REQUIRE((int_val <= double_val).AsBool());
		REQUIRE_THROWS_AS(int_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val <= null_val, BadOperation);

		REQUIRE(!((double_val <= bool_val).AsBool()));
		REQUIRE(!((double_val <= int_val).AsBool()));
		REQUIRE_THROWS_AS(double_val <= string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <= null_val, BadOperation);

		REQUIRE((string1_val <= string2_val).AsBool());
		REQUIRE_THROWS_AS(string1_val <= null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val <= double_val, BadOperation);
	}
	SECTION("Operator \">=\"")
	{
		REQUIRE((bool_val >= int_val).AsBool());
		REQUIRE(!((bool_val >= double_val).AsBool()));
		REQUIRE_THROWS_AS(bool_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >= null_val, BadOperation);

		REQUIRE(!((int_val >= bool_val).AsBool()));
		REQUIRE(!((int_val >= double_val).AsBool()));
		REQUIRE_THROWS_AS(int_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(int_val >= null_val, BadOperation);

		REQUIRE((double_val >= bool_val).AsBool());
		REQUIRE((double_val >= int_val).AsBool());
		REQUIRE_THROWS_AS(double_val >= string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >= null_val, BadOperation);

		REQUIRE(!((string1_val >= string2_val)).AsBool());
		REQUIRE_THROWS_AS(string1_val >= null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= int_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val >= double_val, BadOperation);
	}
}

TEST_CASE("Value class unary operations", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = static_cast<long long int>(-20);
	Value double_val = 0.5;
	Value string_val = "This is test string";

	SECTION("Prefix operator \"+\"")
	{
		REQUIRE(((+bool_val) == true).AsBool());
		REQUIRE(((+int_val) == -20).AsBool());
		REQUIRE(((+double_val) == 0.5).AsBool());
		REQUIRE_THROWS_AS(+string_val, BadOperation);
		REQUIRE_THROWS_AS(+null_val, BadOperation);
	}

	SECTION("Prefix operator \"-\"")
	{
		REQUIRE(((-bool_val) == -1).AsBool());
		REQUIRE(((-int_val) == 20).AsBool());
		REQUIRE(((-double_val) == -0.5).AsBool());
		REQUIRE_THROWS_AS(-string_val, BadOperation);
		REQUIRE_THROWS_AS(-null_val, BadOperation);
	}

	SECTION("Prefix operator \"!\"")
	{
		REQUIRE(((!bool_val) == false).AsBool());
		REQUIRE(((!int_val) == 0).AsBool());
		REQUIRE(((!double_val) == 0.0).AsBool());
		REQUIRE_THROWS_AS(!string_val, BadOperation);
		REQUIRE_THROWS_AS(!null_val, BadOperation);
	}

	SECTION("Prefix operator \"++\"")
	{
		REQUIRE(((++bool_val) == 2).AsBool());
		REQUIRE(((++int_val) == -19).AsBool());
		REQUIRE(((++double_val) == 1.5).AsBool());

		REQUIRE((bool_val == 2).AsBool());
		REQUIRE((int_val == -19).AsBool());
		REQUIRE((double_val == 1.5).AsBool());

		REQUIRE_THROWS_AS(++string_val, BadOperation);
		REQUIRE_THROWS_AS(++null_val, BadOperation);
	}

	SECTION("Prefix operator \"--\"")
	{
		REQUIRE(((--bool_val) == false).AsBool());
		REQUIRE(((--int_val) == -21).AsBool());
		REQUIRE(((--double_val) == -0.5).AsBool());

		REQUIRE((bool_val == false).AsBool());
		REQUIRE((int_val == -21).AsBool());
		REQUIRE((double_val == -0.5).AsBool());

		REQUIRE_THROWS_AS(--string_val, BadOperation);
		REQUIRE_THROWS_AS(--null_val, BadOperation);
	}

	SECTION("Postfix operator \"++\"")
	{
		REQUIRE(((bool_val++) == true).AsBool());
		REQUIRE(((int_val++) == -20).AsBool());
		REQUIRE(((double_val++) == 0.5).AsBool());

		REQUIRE((bool_val == 2).AsBool());
		REQUIRE((int_val == -19).AsBool());
		REQUIRE((double_val == 1.5).AsBool());

		REQUIRE_THROWS_AS(string_val++, BadOperation);
		REQUIRE_THROWS_AS(null_val++, BadOperation);
	}

	SECTION("Postfix operator \"--\"")
	{
		REQUIRE(((bool_val--) == true).AsBool());
		REQUIRE(((int_val--) == -20).AsBool());
		REQUIRE(((double_val--) == 0.5).AsBool());

		REQUIRE((bool_val == false).AsBool());
		REQUIRE((int_val == -21).AsBool());
		REQUIRE((double_val == -0.5).AsBool());

		REQUIRE_THROWS_AS(string_val--, BadOperation);
		REQUIRE_THROWS_AS(null_val--, BadOperation);
	}

}

TEST_CASE("Value class unary iterator operation \"--\", extrims", "[Value]")
{
	Value bool_val_min = false;
	Value int_val_min = (1ll << 63);

	SECTION("Prefix operator \"--\"")
	{
		--bool_val_min;
		--int_val_min;

		REQUIRE(bool_val_min.GetType() == Value::T_INT);
		REQUIRE(bool_val_min.AsInt() == -1);

		REQUIRE(int_val_min.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_min.AsDouble() == static_cast<double>((1ll << 63)) - 1);
	}

	SECTION("Postfix operator \"--\"")
	{
		bool_val_min--;
		int_val_min--;

		REQUIRE(bool_val_min.GetType() == Value::T_INT);
		REQUIRE(bool_val_min.AsInt() == -1);

		REQUIRE(int_val_min.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_min.AsDouble() == static_cast<double>(1ll << 63) - 1);
	}
}

TEST_CASE("Value class unary iterator operation \"++\", extrims", "[Value]")
{
	Value bool_val_max = true;
	Value int_val_max = ~(1ll << 63);

	SECTION("Prefix operator \"--\"")
	{
		++bool_val_max;
		++int_val_max;

		REQUIRE(bool_val_max.GetType() == Value::T_INT);
		REQUIRE(bool_val_max.AsInt() == 2);

		REQUIRE(int_val_max.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_max.AsDouble() == static_cast<double>(1ull << 63) + 1.0);
	}

	SECTION("Postfix operator \"--\"")
	{
		bool_val_max++;
		int_val_max++;

		REQUIRE(bool_val_max.GetType() == Value::T_INT);
		REQUIRE(bool_val_max.AsInt() == 2);

		REQUIRE(int_val_max.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val_max.AsDouble() == static_cast<double>(1ull << 63) + 1.0);
	}
}

TEST_CASE("Binary operator \"+=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = -6ll;
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
		bool_val += double_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 8ull);

		REQUIRE_THROWS_AS(bool_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val += null_val, BadOperation);
	}

	SECTION("Assagning to int")
	{
		int_val += 20ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 14ll);

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

		REQUIRE_THROWS_AS(double_val += string1_val, BadOperation);
		REQUIRE_THROWS_AS(double_val += null_val, BadOperation);
	}

	SECTION("Assagning to string")
	{
		REQUIRE_THROWS_AS(string1_val += null_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += bool_val, BadOperation);
		REQUIRE_THROWS_AS(string1_val += int_val, BadOperation);
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

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 6ull);

		bool_val = false;
		bool_val -= double_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == -8ll);

		REQUIRE_THROWS_AS(bool_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val -= null_val, BadOperation);
	}

	SECTION("Substructing from int")
	{
		int_val -= 20ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -26ll);

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

		REQUIRE_THROWS_AS(double_val -= string_val, BadOperation);
		REQUIRE_THROWS_AS(double_val -= null_val, BadOperation);
	}

	SECTION("Assagning to string")
	{
		REQUIRE_THROWS_AS(string_val -= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val -= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"*=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = false;
	Value int_val = -6ll;
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
		bool_val *= double_val;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 8ull);

		REQUIRE_THROWS_AS(bool_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val *= null_val, BadOperation);
	}

	SECTION("Multiplying int")
	{
		int_val *= 20ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -120ll);

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
	
		REQUIRE_THROWS_AS(double_val *= string_val, BadOperation);
		REQUIRE_THROWS_AS(double_val *= null_val, BadOperation);
	}
	
	SECTION("Multiplying string")
	{
		REQUIRE_THROWS_AS(string_val *= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val *= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"/=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
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
		bool_val /= double_val;

		REQUIRE(bool_val.GetType() == Value::T_BOOL);
		REQUIRE(!bool_val.AsBool());

		REQUIRE_THROWS_AS(bool_val /= false, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= 0ll, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= 0.0, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val /= string_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		int_val /= 4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -1ll);

		int_val = -6ll;
		int_val /= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -6ll);

		int_val = -6ll;
		int_val /= double_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		REQUIRE_THROWS_AS(int_val /= false, BadOperation);
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

		REQUIRE_THROWS_AS(double_val /= false, BadOperation);
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

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 2ll);

		bool_val = max_bool;
		bool_val += static_cast<double>(~0ull);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) + 1.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val += -1;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) - 1.0));

		int_val = max_int;
		int_val += 1ll;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(~(1ull << 63)) + 1.0));

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
		REQUIRE(bool_val.AsDouble() == -(static_cast<double>(~0ull) + 1.0));

		bool_val = max_bool;
		bool_val -= -1;

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 2ll);

		bool_val = max_bool;
		bool_val -= -static_cast<double>(~0ull) * 2;

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2 + 1.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val -= 1;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) - 1.0));

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

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 20ll);

		bool_val = max_bool;
		bool_val *= (static_cast<double>(~0ull) * 2.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val *= 2;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) * 2.0));

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

		REQUIRE(bool_val.GetType() == Value::T_INT);
		REQUIRE(bool_val.AsInt() == 20ll);

		bool_val = max_bool;
		bool_val /= 1.0 / (static_cast<double>(~0ull) * 2.0);

		REQUIRE(bool_val.GetType() == Value::T_DOUBLE);
		REQUIRE(bool_val.AsDouble() == (static_cast<double>(~0ull) * 2.0));
	}

	SECTION("Overflow of int")
	{
		Value int_val;

		int_val = min_int;
		int_val /= 0.5;

		REQUIRE(int_val.GetType() == Value::T_DOUBLE);
		REQUIRE(int_val.AsDouble() == (static_cast<double>(1ll << 63) * 2.0));

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

		REQUIRE_THROWS_AS(bool_val %= false, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= 0ll, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= 0.0, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val %= string_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		int_val %= -4ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == -2ll);

		int_val = -6ll;
		int_val %= bool_val;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0ll);

		REQUIRE_THROWS_AS(int_val %= false, BadOperation);
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
		double1_val %= double2_val;

		REQUIRE(double1_val.GetType() == Value::T_DOUBLE);
		REQUIRE(std::abs(double1_val.AsDouble() - 0.6) < 0.00000000000001);

		REQUIRE_THROWS_AS(double1_val %= false, BadOperation);
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
		REQUIRE_THROWS_AS(string_val %= double1_val, BadOperation);
		REQUIRE_THROWS_AS(string_val %= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"&=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
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

		REQUIRE_THROWS_AS(bool_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val &= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val &= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x00100000ll);

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
		REQUIRE_THROWS_AS(double_val &= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val &= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val &= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val &= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val &= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"|=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
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

		REQUIRE_THROWS_AS(bool_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val |= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val |= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x11111100ll);

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
		REQUIRE_THROWS_AS(double_val |= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val |= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val |= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val |= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val |= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"^=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val =  0x00101100ll;
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

		REQUIRE_THROWS_AS(bool_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val ^= string_val, BadOperation);
	}

	SECTION("Changing int")
	{
		int_val ^= 0x11110000ll;

		REQUIRE(int_val.GetType() == Value::T_INT);
		REQUIRE(int_val.AsInt() == 0x11011100ll);

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
		REQUIRE_THROWS_AS(double_val ^= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val ^= string_val, BadOperation);
	}

	SECTION("Changing string")
	{
		REQUIRE_THROWS_AS(string_val ^= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val ^= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"<<=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
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

		REQUIRE_THROWS_AS(bool_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val <<= string_val, BadOperation);
	}

	SECTION("Shifting int")
	{
		int_val <<= 4ll;

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
		REQUIRE_THROWS_AS(double_val <<= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val <<= string_val, BadOperation);
	}

	SECTION("Shifting string")
	{
		REQUIRE_THROWS_AS(string_val <<= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val <<= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \">>=\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = 0x00101100ll;
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

		REQUIRE_THROWS_AS(bool_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(bool_val >>= string_val, BadOperation);
	}

	SECTION("Shifting int")
	{
		int_val >>= 4ll;

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
		REQUIRE_THROWS_AS(double_val >>= int_val, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= 0.8, BadOperation);
		REQUIRE_THROWS_AS(double_val >>= string_val, BadOperation);
	}

	SECTION("Shifting string")
	{
		REQUIRE_THROWS_AS(string_val >>= null_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= bool_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= int_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= double_val, BadOperation);
		REQUIRE_THROWS_AS(string_val >>= string_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"+\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Adding to bool")
	{
		test_val = bool_val + false;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val + int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -5ll);

		test_val = bool_val + double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 9.8);

		REQUIRE_THROWS_AS(test_val = bool_val + string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val + null_val, BadOperation);
	}

	SECTION("Adding to int")
	{
		test_val = int_val + -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -26ll);

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
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Substructing from bool")
	{
		test_val = bool_val - false;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val - int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 7ll);

		test_val = bool_val - double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 1.0 - 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val - string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val - null_val, BadOperation);
	}

	SECTION("Substructing from int")
	{
		test_val = int_val - 20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -26ll);

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
		REQUIRE_THROWS_AS(test_val = string1_val - double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val - string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"*\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Multiplying bool")
	{
		test_val = bool_val * true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val * int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = bool_val * double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val * string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val * null_val, BadOperation);
	}

	SECTION("Multiplying int")
	{
		test_val = int_val * -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 120ll);

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
		REQUIRE_THROWS_AS(test_val = string1_val * double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val * string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"/\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Dividing bool")
	{
		test_val = bool_val / true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(test_val.AsBool());

		test_val = bool_val / int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = bool_val / double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 1.0 / 8.8);

		REQUIRE_THROWS_AS(test_val = bool_val / false, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val / null_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		test_val = int_val / -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = int_val / bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val / double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == -6.0 / 8.8);

		REQUIRE_THROWS_AS(test_val = int_val / false, BadOperation);
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

		test_val = double_val / int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8 / -6.0);

		test_val = double_val / bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == 8.8);

		REQUIRE_THROWS_AS(test_val = double_val / false, BadOperation);
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
		REQUIRE_THROWS_AS(test_val = string1_val / double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val / string2_val, BadOperation);
	}
}

TEST_CASE("Binary operator \"%\"", "[Value]")
{
	Value null_val = Value();
	Value bool_val = true;
	Value int_val = -6ll;
	Value double_val = 8.8;
	Value string1_val = "String1";
	Value string2_val = "String2";

	Value test_val;

	SECTION("Dividing bool")
	{
		test_val = bool_val % true;
		REQUIRE(test_val.GetType() == Value::T_BOOL);
		REQUIRE(!test_val.AsBool());

		test_val = bool_val % int_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 1ll);

		test_val = bool_val % double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(1.0, 8.8));

		REQUIRE_THROWS_AS(test_val = bool_val % false, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % 0ll, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % 0.0, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % string1_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = bool_val % null_val, BadOperation);
	}

	SECTION("Dividing int")
	{
		test_val = int_val % -20ll;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == -6ll);

		test_val = int_val % bool_val;
		REQUIRE(test_val.GetType() == Value::T_INT);
		REQUIRE(test_val.AsInt() == 0ll);

		test_val = int_val % double_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(-6.0, 8.8));

		REQUIRE_THROWS_AS(test_val = int_val % false, BadOperation);
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

		test_val = double_val % int_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, -6.0));

		test_val = double_val % bool_val;
		REQUIRE(test_val.GetType() == Value::T_DOUBLE);
		REQUIRE(test_val.AsDouble() == std::fmod(8.8, 1.0));

		REQUIRE_THROWS_AS(test_val = double_val % false, BadOperation);
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
		REQUIRE_THROWS_AS(test_val = string1_val % double_val, BadOperation);
		REQUIRE_THROWS_AS(test_val = string1_val % string2_val, BadOperation);
	}
}


TEST_CASE("Simple parsing of operators and brackets", "[Token]")
{
	SECTION("One character symbols (+ - * / % & | ^ = ! < > ? : , ( ) )")
	{
		std::vector<Token> tokens = Token::ParseTokens(" + - * / % & | ^ = ! < > ? : , ( ) ");

		REQUIRE(tokens.size() == 17);

		REQUIRE(tokens[0].GetType() == Token::OP_ADD);
		REQUIRE(tokens[1].GetType() == Token::OP_SUB);
		REQUIRE(tokens[2].GetType() == Token::OP_MUL);
		REQUIRE(tokens[3].GetType() == Token::OP_DIV);
		REQUIRE(tokens[4].GetType() == Token::OP_MOD);
		REQUIRE(tokens[5].GetType() == Token::OP_AND);
		REQUIRE(tokens[6].GetType() == Token::OP_OR);
		REQUIRE(tokens[7].GetType() == Token::OP_XOR);
		REQUIRE(tokens[8].GetType() == Token::OP_EQUAL);
		REQUIRE(tokens[9].GetType() == Token::OP_NOT);
		REQUIRE(tokens[10].GetType() == Token::OP_LOGIC_L);
		REQUIRE(tokens[11].GetType() == Token::OP_LOGIC_G);
		REQUIRE(tokens[12].GetType() == Token::OP_IF);
		REQUIRE(tokens[13].GetType() == Token::OP_ELSE);
		REQUIRE(tokens[14].GetType() == Token::OP_COMA);
		REQUIRE(tokens[15].GetType() == Token::OPENING_BRACKET);
		REQUIRE(tokens[16].GetType() == Token::CLOSING_BRACKET);
	}

	SECTION("Two character symbols (+= -= *= /= %= &= |= ^= == != <= >= ++ -- && || << >>)")
	{
		std::vector<Token> tokens = Token::ParseTokens("+= -= *= /= %= &= |= ^= == != <= >= ++ -- && || << >>");

		REQUIRE(tokens.size() == 18);

		REQUIRE(tokens[0].GetType() == Token::OP_ADD_EQUAL);
		REQUIRE(tokens[1].GetType() == Token::OP_SUB_EQUAL);
		REQUIRE(tokens[2].GetType() == Token::OP_MUL_EQUAL);
		REQUIRE(tokens[3].GetType() == Token::OP_DIV_EQUAL);
		REQUIRE(tokens[4].GetType() == Token::OP_MOD_EQUAL);
		REQUIRE(tokens[5].GetType() == Token::OP_AND_EQUAL);
		REQUIRE(tokens[6].GetType() == Token::OP_OR_EQUAL);
		REQUIRE(tokens[7].GetType() == Token::OP_XOR_EQUAL);
		REQUIRE(tokens[8].GetType() == Token::OP_LOGIC_E);
		REQUIRE(tokens[9].GetType() == Token::OP_LOGIC_NE);
		REQUIRE(tokens[10].GetType() == Token::OP_LOGIC_LE);
		REQUIRE(tokens[11].GetType() == Token::OP_LOGIC_GE);
		REQUIRE(tokens[12].GetType() == Token::OP_PLUSPLUS);
		REQUIRE(tokens[13].GetType() == Token::OP_MINUSMINUS);
		REQUIRE(tokens[14].GetType() == Token::OP_LOGIC_AND);
		REQUIRE(tokens[15].GetType() == Token::OP_LOGIC_OR);
		REQUIRE(tokens[16].GetType() == Token::OP_LSH);
		REQUIRE(tokens[17].GetType() == Token::OP_RSH);
	}

	SECTION("Three character symbols (<<= >>=)")
	{
		std::vector<Token> tokens = Token::ParseTokens("<<= >>=");

		REQUIRE(tokens.size() == 2);

		REQUIRE(tokens[0].GetType() == Token::OP_LSH_EQUAL);
		REQUIRE(tokens[1].GetType() == Token::OP_RSH_EQUAL);
	}
}

TEST_CASE("Simple parsing of values", "[Token]")
{
	SECTION("Parsing for names (abcd abcd1234 ___abcd ___123 ___ _ 123 1_ 123abcd)")
	{
		std::vector<Token> tokens = Token::ParseTokens("abcd abcd1234 ___abcd ___123 ___ _ 123 1_ 123abcd");

		REQUIRE(tokens.size() == 11);

		REQUIRE((tokens[0].GetType() == Token::LVALUE && tokens[0].GetName() == "abcd"));
		REQUIRE((tokens[1].GetType() == Token::LVALUE && tokens[1].GetName() == "abcd1234"));
		REQUIRE((tokens[2].GetType() == Token::LVALUE && tokens[2].GetName() == "___abcd"));
		REQUIRE((tokens[3].GetType() == Token::LVALUE && tokens[3].GetName() == "___123"));
		REQUIRE((tokens[4].GetType() == Token::LVALUE && tokens[4].GetName() == "___"));
		REQUIRE((tokens[5].GetType() == Token::LVALUE && tokens[5].GetName() == "_"));
		REQUIRE( tokens[6].GetType() != Token::LVALUE);
		REQUIRE( tokens[7].GetType() != Token::LVALUE);
		REQUIRE((tokens[8].GetType() == Token::LVALUE && tokens[8].GetName() == "_"));
		REQUIRE( tokens[9].GetType() != Token::LVALUE);
		REQUIRE((tokens[10].GetType() == Token::LVALUE && tokens[10].GetName() == "abcd"));
	}

	SECTION("Parsing for literals (1234567890 1234567890.0123456789 123.0e+12 123e-1 123.0e-12 0x1234567890abcdef 012345670 true false NULL \"Simple string\")")
	{
		std::vector<Token> tokens = Token::ParseTokens("  1234567890 1234567890.0123456789 123.0e+12 123e-1 123.0e-12 0x1234567890abcdef 012345670 true false NULL \"Simple string\"  ");

		REQUIRE(tokens.size() == 11);

		REQUIRE(tokens[0].GetType() == Token::PRVALUE);
		REQUIRE(tokens[0].GetValue().GetType() == Value::T_INT);
		REQUIRE(tokens[0].GetValue().AsInt() == 1234567890ll);

		REQUIRE(tokens[1].GetType() == Token::PRVALUE);
		REQUIRE(tokens[1].GetValue().GetType() == Value::T_DOUBLE);
		REQUIRE(tokens[1].GetValue().AsDouble() == 1234567890.0123456789);

		REQUIRE(tokens[2].GetType() == Token::PRVALUE);
		REQUIRE(tokens[2].GetValue().GetType() == Value::T_DOUBLE);
		REQUIRE(tokens[2].GetValue().AsDouble() == 123.0e+12);

		REQUIRE(tokens[3].GetType() == Token::PRVALUE);
		REQUIRE(tokens[3].GetValue().GetType() == Value::T_DOUBLE);
		REQUIRE(tokens[3].GetValue().AsDouble() == 123e-1);

		REQUIRE(tokens[4].GetType() == Token::PRVALUE);
		REQUIRE(tokens[4].GetValue().GetType() == Value::T_DOUBLE);
		REQUIRE(tokens[4].GetValue().AsDouble() == 123.0e-12);

		REQUIRE(tokens[5].GetType() == Token::PRVALUE);
		REQUIRE(tokens[5].GetValue().GetType() == Value::T_INT);
		REQUIRE(tokens[5].GetValue().AsInt() == 0x1234567890abcdefull);

		REQUIRE(tokens[6].GetType() == Token::PRVALUE);
		REQUIRE(tokens[6].GetValue().GetType() == Value::T_INT);
		REQUIRE(tokens[6].GetValue().AsInt() == 012345670ull);

		REQUIRE(tokens[7].GetType() == Token::PRVALUE);
		REQUIRE(tokens[7].GetValue().GetType() == Value::T_BOOL);
		REQUIRE(tokens[7].GetValue().AsBool() == true);

		REQUIRE(tokens[8].GetType() == Token::PRVALUE);
		REQUIRE(tokens[8].GetValue().GetType() == Value::T_BOOL);
		REQUIRE(tokens[8].GetValue().AsBool() == false);

		REQUIRE(tokens[9].GetType() == Token::PRVALUE);
		REQUIRE(tokens[9].GetValue().GetType() == Value::T_NULL);

		REQUIRE(tokens[10].GetType() == Token::PRVALUE);
		REQUIRE(tokens[10].GetValue().GetType() == Value::T_STRING);
		REQUIRE(tokens[10].GetValue().AsString() == "Simple string");
	}
}

TEST_CASE("Complex parsing", "[Token]")
{
	SECTION("(>>>>>+++++=ABC<<<<<-----+=)")
	{
		std::vector<Token> tokens = Token::ParseTokens(">>>>>+++++=ABC<<<<<-----+=");

		REQUIRE(tokens.size() == 14);

		REQUIRE(tokens[0].GetType() == Token::OP_RSH);
		REQUIRE(tokens[1].GetType() == Token::OP_RSH);
		REQUIRE(tokens[2].GetType() == Token::OP_LOGIC_G);
		REQUIRE(tokens[3].GetType() == Token::OP_PLUSPLUS);
		REQUIRE(tokens[4].GetType() == Token::OP_PLUSPLUS);
		REQUIRE(tokens[5].GetType() == Token::OP_ADD_EQUAL);

		REQUIRE((tokens[6].GetType() == Token::LVALUE && tokens[6].GetName() == "ABC"));
		REQUIRE(tokens[7].GetType() == Token::OP_LSH);
		REQUIRE(tokens[8].GetType() == Token::OP_LSH);
		REQUIRE(tokens[9].GetType() == Token::OP_LOGIC_L);
		REQUIRE(tokens[10].GetType() == Token::OP_MINUSMINUS);
		REQUIRE(tokens[11].GetType() == Token::OP_MINUSMINUS);
		REQUIRE(tokens[12].GetType() == Token::OP_SUB);
		REQUIRE(tokens[13].GetType() == Token::OP_ADD_EQUAL);
	}

	SECTION("(+== -== >>>= <<<= <<== >>== ++== --==)")
	{
		std::vector<Token> tokens = Token::ParseTokens("+== -== >>>= <<<= <<== >>== ++== --==");

		REQUIRE(tokens.size() == 16);

		REQUIRE(tokens[0].GetType() == Token::OP_ADD_EQUAL);
		REQUIRE(tokens[1].GetType() == Token::OP_EQUAL);
		REQUIRE(tokens[2].GetType() == Token::OP_SUB_EQUAL);
		REQUIRE(tokens[3].GetType() == Token::OP_EQUAL);

		REQUIRE(tokens[4].GetType() == Token::OP_RSH);
		REQUIRE(tokens[5].GetType() == Token::OP_LOGIC_GE);
		REQUIRE(tokens[6].GetType() == Token::OP_LSH);
		REQUIRE(tokens[7].GetType() == Token::OP_LOGIC_LE);

		REQUIRE(tokens[8].GetType() == Token::OP_LSH_EQUAL);
		REQUIRE(tokens[9].GetType() == Token::OP_EQUAL);
		REQUIRE(tokens[10].GetType() == Token::OP_RSH_EQUAL);
		REQUIRE(tokens[11].GetType() == Token::OP_EQUAL);

		REQUIRE(tokens[12].GetType() == Token::OP_PLUSPLUS);
		REQUIRE(tokens[13].GetType() == Token::OP_LOGIC_E);
		REQUIRE(tokens[14].GetType() == Token::OP_MINUSMINUS);
		REQUIRE(tokens[15].GetType() == Token::OP_LOGIC_E);
	}

	SECTION("(-123 +123 ++123 123- 123+)")
	{
		std::vector<Token> tokens = Token::ParseTokens("-123 +123 ++123 123- 123+");

		REQUIRE(tokens.size() == 10);

		REQUIRE(tokens[0].GetType() == Token::OP_SUB);
		REQUIRE(tokens[1].GetType() == Token::PRVALUE);
		REQUIRE(tokens[2].GetType() == Token::OP_ADD);
		REQUIRE(tokens[3].GetType() == Token::PRVALUE);
		REQUIRE(tokens[4].GetType() == Token::OP_PLUSPLUS);
		REQUIRE(tokens[5].GetType() == Token::PRVALUE);
		REQUIRE(tokens[6].GetType() == Token::PRVALUE);
		REQUIRE(tokens[7].GetType() == Token::OP_SUB);
		REQUIRE(tokens[8].GetType() == Token::PRVALUE);
		REQUIRE(tokens[9].GetType() == Token::OP_ADD);
	}
}

TEST_CASE("Reading statements", "[Parser]")
{
	Parser parser;

	SECTION("Simple processing (first = second = 20)")
	{
		parser.ProcessStatement("first = second = 20");

		REQUIRE(parser.IsVariableExist("first"));
		REQUIRE(parser.IsVariableExist("second"));

		Value value = parser.GetVariable("first");
		REQUIRE((value.GetType() == Value::T_INT && value.AsInt() == 20ll) /*first*/);

		value = parser.GetVariable("second");
		REQUIRE((value.GetType() == Value::T_INT && value.AsInt() == 20ll) /*second*/);
	}

	SECTION("Testing default options ( first = 20 \n second = 25\n third = \"Simple string\" \n OUTPUT = first + second \n)")
	{
		std::string output = parser.ProcessData("first = 20 \n second = 25\n third = \"Simple string\" \n OUTPUT = first + second \n");

		REQUIRE(parser.IsVariableExist("first"));
		REQUIRE(parser.IsVariableExist("second"));
		REQUIRE(parser.IsVariableExist("third"));

		Value value;

		value = parser.GetVariable("first");
		REQUIRE((value.GetType() == Value::T_INT && value.AsInt() == 20ll) /*first*/);

		value = parser.GetVariable("second");
		REQUIRE((value.GetType() == Value::T_INT && value.AsInt() == 25ll) /*second*/);

		value = parser.GetVariable("third");
		REQUIRE((value.GetType() == Value::T_STRING && value.AsString() == "Simple string") /*third*/);

		REQUIRE(output == "45");
	}

	SECTION("Testing stubs working (stubs : ([start]), ([end])) ("
		"ind string\n"
		"ind start([start])first = 10([end])ind end\n"
		"anther([start])second = first + 10, third = second + first([end])\n"
		"finale answher : ([start])my_output = third + 1([end])\n"
		")")
	{
		parser.SetFrontStub("([start])");
		parser.SetBackStub("([end])");
		parser.SetOutputKeyword("my_output");
		std::string output;
		
		output = parser.ProcessData(
			"ind string\n"
			"ind start([start])first = 10([end])ind end\n"
			"anther([start])second = first + 10, third = second + first([end])\n"
			"finale answher : ([start])my_output = third + 1([end])\n");
		

		REQUIRE(output == "ind string\n"
			"ind startind end\n"
			"anther\n"
			"finale answher : 31\n");
	}
}
