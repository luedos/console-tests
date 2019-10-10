#include "..\include\Value.h"
#include "..\include\Exceptions.h"
#include <sstream>

using namespace bwn::calc_parser;

Value::Value(unsigned long long int value)
	: values_{ 0 }
	, string_{}
	, type_{ T_UINT }
{
	values_.uint_ = value;
}

Value::Value(signed long long int value)
	: values_{ 0 }
	, string_{}
	, type_{ T_INT }
{
	values_.sint_ = value;
}

Value::Value(double value)
	: values_{ 0 }
	, string_{}
	, type_{ T_DOUBLE }
{
	values_.double_ = value;
}

Value::Value(bool value)
	: values_{ 0 }
	, string_{}
	, type_{ T_BOOL }
{
	values_.bool_ = value;
}

Value::Value(unsigned int value)
	: Value{ static_cast<unsigned long long int>(value) }
{
}

Value::Value(signed int value)
	: Value{ static_cast<signed long long int>(value) }
{
}

Value::Value(const std::string& value)
	: values_{ 0 }
	, string_{ value }
	, type_ { T_STRING }
{
}

Value::Value(const char * value)
	: values_{ 0 }
	, string_{ value }
	, type_{ T_STRING }
{
}

Value::Value(const Value& other)
{
	type_ = other.type_;

	if (type_ == T_STRING) {
		string_ = other.string_;
	}
	else {
		values_ = other.values_;
	}
}

Value::Value(Value&& other) noexcept
{
	type_ = other.type_;

	if (type_ == T_STRING) {
		string_.swap(other.string_);
	}
	else {
		values_ = other.values_;
	}
}

Value& Value::operator=(const Value& other)
{
	if (this == &other) {
		return *this;
	}

	type_ = other.type_;

	if (type_ == T_STRING) {
		string_ = other.string_;
	}
	else {
		values_ = other.values_;
	}

	return *this;
}

Value& Value::operator=(Value&& other) noexcept
{
	if (this == &other) {
		return *this;
	}

	type_ = other.type_;

	if (type_ == T_STRING) {
		string_.swap(other.string_);
	}
	else {
		values_ = other.values_;
	}

	return *this;
}

unsigned long long int Value::AsUInt() const
{
	if (type_ != T_UINT) {
		throw BadValue{ "Type of Value is not UInt" };
	}
	return values_.uint_;
}

signed long long int Value::AsInt() const
{
	if (type_ != T_INT) {
		throw BadValue{ "Type of Value is not Int" };
	}
	return values_.sint_;
}

double Value::AsDouble() const
{
	if (type_ != T_DOUBLE) {
		throw BadValue{ "Type of Value is not Double" };
	}
	return values_.double_;
}

bool Value::AsBool() const
{
	if (type_ != T_BOOL) {
		throw BadValue{ "Type of Value is not Bool" };
	}
	return values_.bool_;
}

std::string Value::AsString() const
{
	if (type_ != T_STRING) {
		throw BadValue{ "Type of Value is not String" };
	}
	return string_;
}

unsigned long long int Value::AsIntegral() const
{
	if (!(type_ & T_INTEGRAL)) {
		throw BadValue{ "Type of Value is not Integral" };
	}
	return values_.uint_;
}

Value::Type Value::GetType() const
{
	return type_;
}

bool Value::IsEmpty() const
{
	if (type_ & T_NULL) {
		return true;
	}

	if (type_ & T_INTEGRAL) {
		return values_.sint_ == 0;
	}

	if (type_ == T_DOUBLE) {
		return values_.double_ == 0;
	}

	if (type_ == T_STRING) {
		return string_.empty();
	}

	return true;
}

std::string Value::ToString() const
{
	std::stringstream stream;

	switch (type_)
	{
	case T_NULL:
		break;
	case T_BOOL:
		stream << std::boolalpha << values_.bool_;
		break;
	case T_INT:
		stream << values_.sint_;
		break;
	case T_UINT:
		stream << values_.uint_;
		break;
	case T_DOUBLE:
		stream << values_.double_;
		break;
	case T_STRING:
		stream << string_;
		break;

	default:
		throw BadValue{ ("Unknown token type (" + std::to_string(type_) + ")").data() };
	}

	return stream.str();
}

Value& Value::operator+=(const Value& other)
{
	if (type_ == T_NULL || other.type_ == T_NULL) {
		throw BadOperation{ "Addition operation with NULL type" };
	}

	if ((type_ == Value::T_STRING) ^ (other.type_ == Value::T_STRING)) {
		throw BadOperation{ "Addition operation with string and number" };
	}

	if (type_ == T_STRING) 
	{
		string_ += other.string_;
		return *this;
	}

	switch (other.type_)
	{
	case T_BOOL:
	case T_UINT:
		SelfAdd<unsigned long long int>(other.values_.uint_);
		break;

	case T_INT:
		SelfAdd<long long int>(other.values_.sint_);
		break;

	case T_DOUBLE:
		SelfAdd<double>(other.values_.double_);
		break;
	}

	return *this;
}

Value& Value::operator-=(const Value& other)
{
	if (type_ == T_NULL || other.type_ == T_NULL) {
		throw BadOperation{ "Subtraction operation with NULL type" };
	}

	if (type_ == T_STRING || other.type_ == T_STRING) {
		throw BadOperation{ "Subtraction operation with string" };
	}

	return *this += -other;
}

Value& Value::operator*=(const Value& other)
{
	if (type_ == T_NULL || other.type_ == T_NULL) {
		throw BadOperation{ "Multiplication operation with NULL type" };
	}

	if (type_ == T_STRING || other.type_ == T_STRING) {
		throw BadOperation{ "Multiplication operation with string" };
	}

	switch (other.type_)
	{
	case T_BOOL:
	case T_UINT:
		SelfMul<unsigned long long int>(other.values_.uint_);
		break;

	case T_INT:
		SelfMul<long long int>(other.values_.sint_);
		break;

	case T_DOUBLE:
		SelfMul<double>(other.values_.double_);
		break;
	}

	return *this;
}

Value& Value::operator/=(const Value& other)
{
	if (type_ == T_NULL || other.type_ == T_NULL) {
		throw BadOperation{ "Division operation with NULL type" };
	}

	if (type_ == T_STRING || other.type_ == T_STRING) {
		throw BadOperation{ "Division operation with string" };
	}

	switch (other.type_)
	{
	case T_BOOL:
	case T_UINT:
		SelfDiv<unsigned long long int>(other.values_.uint_);
		break;

	case T_INT:
		SelfDiv<long long int>(other.values_.sint_);
		break;

	case T_DOUBLE:
		SelfDiv<double>(other.values_.double_);
		break;
	}

	return *this;
}

Value& Value::operator%=(const Value& other)
{
	if (type_ == T_NULL || other.type_ == T_NULL) {
		throw BadOperation{ "Modulus operation with NULL type" };
	}

	if (type_ == T_STRING || other.type_ == T_STRING) {
		throw BadOperation{ "Modulus operation with string" };
	}
	
	if (type_ == T_DOUBLE) 
	{
		double devider = 0;

		if (other.type_ == T_DOUBLE) {
			devider = other.values_.double_;
		}
		else if (other.type_ == T_INT) {
			devider = static_cast<double>(other.values_.sint_);
		}
		else {
			devider = static_cast<double>(other.values_.uint_);
		}

		if (devider == 0) {
			throw BadOperation{ "Devision by zero" };
		}

		values_.double_ = std::fmod(values_.double_, devider);
	}
	else if (type_ & T_INTEGRAL) 
	{
		if (other.type_ == T_DOUBLE) {
			throw BadOperation{ "Modulus of integral by double" };
		}
		if (other.values_.uint_ == 0) {
			throw BadOperation{ "Devision by zero" };
		}
		
		unsigned long long devider;

		if (other.type_ == T_INT) {
			devider = std::abs(other.values_.sint_);
		}
		else {
			devider = other.values_.uint_;
		}

		switch (type_)
		{
		case T_BOOL:
		case T_UINT:
			values_.uint_ %= devider;
			break;

		case T_INT:
			if (devider < (1ull << 63))
			{
				if (devider == (1ull << 63) && values_.sint_ == (1ull << 63)) {
					values_.sint_ = 0;
				}
				else {
					values_.sint_ %= static_cast<long long int>(devider);
				}
			}
			break;
		}
	}

	return *this;
}

Value& Value::operator&=(const Value& other)
{
	if (!(type_ & T_INTEGRAL) || !(other.type_ & T_INTEGRAL)) {
		throw BadOperation{ "Bitwize AND operation with non integral types" };
	}

	values_.uint_ &= other.values_.uint_;

	return *this;
}

Value& Value::operator|=(const Value& other)
{
	if (!(type_ & T_INTEGRAL) || !(other.type_ & T_INTEGRAL)) {
		throw BadOperation{ "Bitwize OR operation with non integral types" };
	}

	values_.uint_ |= other.values_.uint_;

	if (type_ == T_BOOL) {
		values_.uint_ = values_.uint_ > 0;
	}

	return *this;
}

Value& Value::operator^=(const Value& other)
{
	if (!(type_ & T_INTEGRAL) || !(other.type_ & T_INTEGRAL)) {
		throw BadOperation{ "Bitwize XOR operation with non integral types" };
	}

	values_.uint_ ^= other.values_.uint_;

	if (type_ == T_BOOL) {
		values_.uint_ = values_.uint_ > 0;
	}

	return *this;
}

Value& Value::operator<<=(const Value& other)
{
	if (!(type_ & T_INTEGRAL) || !(other.type_ & T_INTEGRAL)) {
		throw BadOperation{ "Bitwize left shift operation with non integral types" };
	}

	if (IsEmpty() || other.IsEmpty()) {
		return *this;
	}

	values_.uint_ <<= other.values_.uint_;

	if (type_ == T_BOOL) {
		values_.uint_ = values_.uint_ > 0;
	}	

	return *this;
}

Value& Value::operator>>=(const Value& other)
{
	if (!(type_ & T_INTEGRAL) || !(other.type_ & T_INTEGRAL)) {
		throw BadOperation{ "Bitwize right shift operation with non integral types" };
	}

	if (IsEmpty() || other.IsEmpty()) {
		return *this;
	}

	values_.uint_ >>= other.values_.uint_;

	if (type_ == T_BOOL) {
		values_.uint_ = values_.uint_ > 0;
	}

	return *this;
}

Value Value::operator+() const
{
	if (type_ == T_NULL) {
		throw BadOperation{ "Unary + operation with NULL type" };
	}

	if (type_ == T_STRING) {
		throw BadOperation{ "Unary + operation with string" };
	}

	return *this;
}

Value Value::operator-() const
{
	if (type_ == T_NULL) {
		throw BadOperation{ "Unary - operation with NULL type" };
	}

	if (type_ == T_STRING) {
		throw BadOperation{ "Unary - operation with string" };
	}

	Value out = *this;
	if (out.type_ == T_DOUBLE) 
	{
		out.values_.double_ = -out.values_.double_;
		return out;
	}

	if (out.type_ == T_INT)
	{
		out.values_.sint_ = -out.values_.sint_;
		return out;
	}

	out.type_ = T_INT;
	out.values_.sint_ = -out.values_.sint_;
	return out;
}

Value Value::operator!() const
{
	if (type_ == T_NULL) {
		throw BadOperation{ "Unary ! operation with NULL type" };
	}

	if (type_ == T_STRING) {
		throw BadOperation{ "Unary ! operation with string" };
	}

	Value out;
	out.type_ = type_;

	if (type_ == T_DOUBLE) {
		out.values_.double_ = !values_.double_;
	}
	else {
		out.values_.uint_ = !values_.uint_;
	}

	return out;
}

void Value::ChangeToType(Type type)
{
	if (type_ == type) {
		return;
	}

	if (type == T_NULL)
	{
		values_.uint_ = 0;
		string_.clear();
		type_ = T_NULL;
		return;
	}

	if (type_ == T_NULL)
	{
		if (type & T_INTEGRAL) {
			values_.uint_ = 0;
		}
		if (type == T_DOUBLE) {
			values_.double_ = 0.0;
		}
		if (type == T_STRING) {
			string_ = "";
		}
		type_ = type;
		return;
	}

	if (type == T_STRING)
	{
		string_ = ToString();
		values_.uint_ = 0;
		type_ = T_STRING;

		return;
	}
	
	if (type == T_DOUBLE) 
	{
		double test = 0;
		if (type_ == T_STRING)
		{
			try
			{
				test = std::stod(string_);
			}
			catch (const std::exception&)
			{
				throw BadConversion{ ("Error converting string \"" + string_ + "\" to double").data() };
			}
		}
		else if (type_ == T_UINT || type_ == T_BOOL)
		{
			test = static_cast<double>(values_.uint_);
		}
		else if (type_ == T_INT)
		{
			test = static_cast<double>(values_.sint_);
		}

		values_.double_ = test;
		type_ = T_DOUBLE;
		return;
	}

	if (type_ == T_DOUBLE)
	{
		if (type == T_BOOL) {
			values_.uint_ = values_.double_ != 0;
		}
		else {
			values_.sint_ = static_cast<signed long long int>(values_.double_);
		}

		type_ = type;
		return;
	}

	if (type == T_INT)
	{
		signed long long int test;
		if (type_ == T_STRING)
		{
			try
			{
				test = std::stoll(string_);
			}
			catch (const std::exception&)
			{
				throw BadConversion{ ("Error converting string \"" + string_ + "\" to int").data() };
			}
		}
		else
		{
			test = values_.uint_;
		}

		values_.sint_ = test;
		type_ = T_INT;
		return;
	}

	if (type == T_UINT)
	{
		unsigned long long int test;
		if (type_ == T_STRING)
		{
			try
			{
				if (string_.size() > 1 && string_[0] == '0')
				{
					if (string_[1] == 'x') {
						test = std::stoull(string_, nullptr, 16);
					}
					else {
						test = std::stoull(string_, nullptr, 8);
					}
				}
				else {
					test = std::stoull(string_);
				}
			}
			catch (const std::exception&)
			{
				throw BadConversion{ ("Error converting string \"" + string_ + "\" to uint").data() };
			}
		}
		else
		{
			test = values_.uint_;
		}

		values_.uint_ = test;
		type_ = T_UINT;
		return;
	}



	if (type == T_BOOL)
	{
		unsigned long long int test;
		if (type_ == T_STRING)
		{
			if (string_ == "true") {
				test = 1;
			}
			else if (string_ == "false") {
				test = 0;
			}
			else {
				throw BadConversion{ ("Error converting string \"" + string_ + "\" to bool").data() };
			}		
		}
		else
		{
			test = values_.uint_ != 0;
		}

		values_.uint_ = test;
		type_ = T_BOOL;
		return;
	}
}

Value bwn::calc_parser::operator+ (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Addition operation with NULL type" };
	}

	if ((left.type_ == Value::T_STRING) ^ (right.type_ == Value::T_STRING)) {
		throw BadOperation{ "Addition operation with string and number" };
	}

	Value out = left;	

	if (left.type_ < right.type_
		&& !(left.type_ == Value::T_UINT && right.type_ == Value::T_INT && (left.values_.sint_ < 0)))
	{
		out.ChangeToType(right.type_);
	}

	out += right;
	return out;
}

Value bwn::calc_parser::operator- (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Subtraction operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Subtraction operation with string" };
	}

	Value out = left;

	if (left.type_ < right.type_
		&& !(left.type_ == Value::T_UINT && right.type_ == Value::T_INT && (left.values_.sint_ < 0)))
	{
		out.ChangeToType(right.type_);
	}
	out -= right;
	return out;
}

Value bwn::calc_parser::operator* (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Multiplication operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Multiplication operation with string" };
	}

	Value out = left;

	if (left.type_ < right.type_
		&& !(left.type_ == Value::T_UINT && right.type_ == Value::T_INT && (left.values_.sint_ < 0)))
	{
		out.ChangeToType(right.type_);
	}

	out *= right;
	return out;
}

Value bwn::calc_parser::operator/ (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Division operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Division operation with string" };
	}

	Value out = left;

	if (left.type_ < right.type_
		&& !(left.type_ == Value::T_UINT && right.type_ == Value::T_INT && (left.values_.sint_ < 0)))
	{
		out.ChangeToType(right.type_);
	}

	out /= right;
	return out;
}

Value bwn::calc_parser::operator% (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Modulus operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Modulus operation with string" };
	}

	Value out = left;

	if (left.type_ < right.type_
		&& !(left.type_ == Value::T_UINT && right.type_ == Value::T_INT && (left.values_.sint_ < 0)))
	{
		out.ChangeToType(right.type_);
	}

	out %= right;
	return out;
}

Value bwn::calc_parser::operator&&(const Value& left, const Value& right)
{
	return !left.IsEmpty() && !right.IsEmpty();
}

Value bwn::calc_parser::operator||(const Value& left, const Value& right)
{
	return !left.IsEmpty() || !right.IsEmpty();
}

Value bwn::calc_parser::operator& (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Bitwise AND operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Bitwise AND operation with string" };
	}

	Value out = left;

	if (out.type_ == Value::T_BOOL) {
		out.ChangeToType(Value::T_UINT);
	}

	out &= right;
	return out;
}

Value bwn::calc_parser::operator| (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Bitwize OR operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Bitwize OR operation with string" };
	}

	Value out = left;

	if (out.type_ == Value::T_BOOL) {
		out.ChangeToType(Value::T_UINT);
	}

	out |= right;
	return out;
}

Value bwn::calc_parser::operator^ (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Bitwize XOR operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Bitwize XOR operation with string" };
	}

	Value out = left;

	if (out.type_ == Value::T_BOOL) {
		out.ChangeToType(Value::T_UINT);
	}
	
	out ^= right;
	return out;
}

Value bwn::calc_parser::operator<<(const Value & left, const Value & right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Bitwize shift left operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Bitwize shift left operation with string" };
	}

	Value out = left;

	if (out.type_ == Value::T_BOOL) {
		out.ChangeToType(Value::T_UINT);
	}

	out <<= right;
	return out;
}

Value bwn::calc_parser::operator>>(const Value & left, const Value & right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Bitwize shift right operation with NULL type" };
	}

	if (left.type_ == Value::T_STRING || right.type_ == Value::T_STRING) {
		throw BadOperation{ "Bitwize shift right operation with string" };
	}

	Value out = left;

	if (out.type_ == Value::T_BOOL) {
		out.ChangeToType(Value::T_UINT);
	}

	out >>= right;
	return out;
}

Value bwn::calc_parser::operator==(const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) 
	{
		if (left.type_ == right.type_) {
			return true;
		}
		return false;
	}

	if ((left.type_ == Value::T_STRING) ^ (right.type_ == Value::T_STRING)) {
		throw BadOperation{ "Comparison between string and a number" };
	}

	if (left.type_ == Value::T_STRING) {
		return left.string_ == right.string_;
	}
	else if (left.type_ & Value::T_INTEGRAL)
	{
		if (right.type_ == Value::T_DOUBLE) 
		{
			if (left.type_ == Value::T_INT) {
				return left.values_.sint_ == right.values_.double_;
			}
			else {
				return left.values_.uint_ == right.values_.double_;
			}
		}

		if (left.values_.uint_ == right.values_.uint_)
		{
			if (!((left.type_ == Value::T_INT) ^ (right.type_ == Value::T_INT))) {
				return true;
			}

			if (left.values_.sint_ < 0 || left.values_.sint_ < 0) {
				return false;
			}

			return true;
		}

		return false;
	}
	else if (left.type_ == Value::T_DOUBLE)
	{
		if (right.type_ == Value::T_DOUBLE) {
			return left.values_.double_ == right.values_.double_;
		}
		else
		{
			if (right.type_ == Value::T_INT) {
				return left.values_.double_ == right.values_.sint_;
			}
			else {
				return left.values_.double_ == right.values_.uint_;
			}
		}
	}

	return false;
}

Value bwn::calc_parser::operator!=(const Value& left, const Value& right)
{
	return !(left == right);
}

Value bwn::calc_parser::operator< (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Less operation with NULL type" };
	}

	if ((left.type_ == Value::T_STRING) ^ (right.type_ == Value::T_STRING)) {
		throw BadOperation{ "Comparison between string and a number" };
	}

	if (left.type_ == Value::T_STRING) {
		return left.string_ < right.string_;
	}
	else if (left.type_ & Value::T_INTEGRAL)
	{
		if (right.type_ == Value::T_DOUBLE)
		{
			if (left.type_ == Value::T_INT) {
				return left.values_.sint_ < right.values_.double_;
			}
			else {
				return left.values_.uint_ < right.values_.double_;
			}
		}
		else 
		{
			if (left.type_ != Value::T_INT && right.type_ != Value::T_INT) {
				return left.values_.uint_ < right.values_.uint_;
			}
			else if (left.type_ == Value::T_INT && right.type_ == Value::T_INT) {
				return left.values_.sint_ < right.values_.sint_;
			}
			else if (left.type_ == Value::T_INT) 
			{
				if (right.values_.sint_ < 0 || left.values_.sint_ < 0) {
					return true;
				}

				return left.values_.sint_ < right.values_.uint_;
			}
			else 
			{
				if (right.values_.sint_ < 0 || left.values_.sint_ < 0) {
					return false;
				}

				return left.values_.uint_ < right.values_.sint_;
			}
		}
	}
	else if (left.type_ == Value::T_DOUBLE)
	{
		if (right.type_ == Value::T_DOUBLE) {
			return left.values_.double_ < right.values_.double_;
		}
		else
		{
			if (right.type_ == Value::T_INT) {
				return left.values_.double_ < right.values_.sint_;
			}
			else {
				return left.values_.double_ < right.values_.uint_;
			}
		}
	}

	return false;
}

Value bwn::calc_parser::operator> (const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Greater operation with NULL type" };
	}
	
	return !(left < right) && !(left == right);
}

Value bwn::calc_parser::operator<=(const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Less or equal operation with NULL type" };
	}

	return (left < right) || (left == right);
}

Value bwn::calc_parser::operator>=(const Value& left, const Value& right)
{
	if (left.type_ == Value::T_NULL || right.type_ == Value::T_NULL) {
		throw BadOperation{ "Greater or equal operation with NULL type" };
	}

	return !(left < right) || (left == right);
}

Value bwn::calc_parser::operator++(Value& other, int)
{
	Value ret = other;
	++other;

	return ret;
}

Value bwn::calc_parser::operator--(Value& other, int)
{
	Value ret = other;
	--other;

	return ret;
}

Value& bwn::calc_parser::operator++(Value& other)
{
	switch (other.type_)
	{
	case Value::T_NULL:
		throw BadOperation{ "Incorect usage of operator \"++\" with NULL type" };

	case Value::T_BOOL:
		if (other.values_.bool_ > 0) {
			other.ChangeToType(Value::T_UINT);
		}
		++other.values_.uint_;
		break;

	case Value::T_INT:
		if (other.values_.sint_ == ~(1ull << 63)) 
		{
			other.ChangeToType(Value::T_UINT);
			return ++other;
		}

		++other.values_.sint_;
		break;
	
	case Value::T_UINT:
		if (other.values_.uint_ == ~0) 
		{
			other.ChangeToType(Value::T_DOUBLE);
			return ++other;
		}

		++other.values_.uint_;
		break;

	case Value::T_DOUBLE:
		++other.values_.double_;
		break;

	case Value::T_STRING:
		throw BadOperation{ "Incorect usage of operator \"++\" with string" };
		break;
	}

	return other;
}

Value& bwn::calc_parser::operator--(Value& other)
{
	switch (other.type_)
	{
	case Value::T_NULL:
		throw BadOperation{ "Incorect usage of operator \"++\" with NULL type" };

	case Value::T_UINT:
		if (!other.values_.uint_) 
		{
			other.ChangeToType(Value::T_INT);
			return --other;
		}
		--other.values_.uint_;
		break;

	case Value::T_BOOL:
		if (!other.values_.bool_) {
			other.ChangeToType(Value::T_INT);
		}
	case Value::T_INT:
		
		if (other.values_.sint_ == (1ull << 63))
		{
			other.ChangeToType(Value::T_DOUBLE);
			return --other;
		}

		--other.values_.sint_;
		break;

	case Value::T_DOUBLE:
		--other.values_.double_;
		break;

	case Value::T_STRING:
		throw BadOperation{ "Incorect usage of operator \"--\" with string" };
		break;
	}

	return other;
}
