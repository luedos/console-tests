#pragma once

#include <string>

#include "Exceptions.h"

namespace bwn
{
namespace calc_parser
{


class Value
{
	//
	// Public classes.
	//
public:
	enum Type
	{
		T_NULL		= 0x00,
		T_BOOL		= 0x01,
		T_UINT		= 0x02,
		T_INT		= 0x04,
		T_DOUBLE	= 0x08,
		T_STRING	= 0x10,

		T_INTEGRAL	= T_INT | T_UINT | T_BOOL,
		T_NUMBER	= T_INTEGRAL | T_DOUBLE
	};
	//
	// Private classes.
	//
private:
	union ValueImpl
	{
		unsigned long long int uint_;
		signed long long int sint_;
		double double_;
		bool bool_;
	};

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Value() = default;
	//! Constructor from uint.
	Value(unsigned int value);
	//! Constructor from uint.
	Value(unsigned long long int value);
	//! Constructor from int.
	Value(signed int value);
	//! Constructor from int.
	Value(signed long long int value);
	//! Constructor from double.
	Value(double value);
	//! Constructor from bool.
	Value(bool value);
	//! Constructor from string.
	Value(const std::string& value);
	//! Constructor from string.
	Value(const char* value);
	//! Copy constructor.
	Value(const Value& other);
	//! Move constructor.
	Value(Value&& other) noexcept;

	//! Copy operator.
	Value& operator=(const Value& other);
	//! Copy operator.
	Value& operator=(Value&& other) noexcept;

	//
	// Public interface.
	//
public:
	//! Returns value as uint.
	unsigned long long int AsUInt() const;
	//! Returns value as int.
	signed long long int AsInt() const;
	//! Returns value as double.
	double AsDouble() const;
	//! Returns value as bool.
	bool AsBool() const;
	//! Returns value as string.
	std::string AsString() const;
	//! Returns Integral representation of value.
	unsigned long long int AsIntegral() const;
	//! Returns value type.
	Type GetType() const;
	//! If type is string returns true if string empty, otherwise returns true if number is zero.
	bool IsEmpty() const;
	//! Returns any value as string.
	std::string ToString() const;
	//! Sum operator.
	friend Value operator+(const Value& left, const Value& right);
	//! Sub operator.
	friend Value operator-(const Value& left, const Value& right);
	//! Mul operator.
	friend Value operator*(const Value& left, const Value& right);
	//! Div operator.
	friend Value operator/(const Value& left, const Value& right);
	//! Mod operator.
	friend Value operator%(const Value& left, const Value& right);
	//! And operator.
	friend Value operator&&(const Value& left, const Value& right);
	//! Or operator.
	friend Value operator||(const Value& left, const Value& right);
	//! Bit and operator.
	friend Value operator&(const Value& left, const Value& right);
	//! Bit or operator.
	friend Value operator|(const Value& left, const Value& right);
	//! Bit xor operator.
	friend Value operator^(const Value& left, const Value& right);
	//! Bit left shift operator.
	friend Value operator<<(const Value& left, const Value& right);
	//! Bit right shift operator.
	friend Value operator>>(const Value& left, const Value& right);
	//! Equality operator.
	friend Value operator==(const Value& left, const Value& right);
	//! Not equal operator.
	friend Value operator!=(const Value& left, const Value& right);
	//! Less operator.
	friend Value operator<(const Value& left, const Value& right);
	//! More operator.
	friend Value operator>(const Value& left, const Value& right);
	//! Less or equal operator.
	friend Value operator<=(const Value& left, const Value& right);
	//! More or equal operator.
	friend Value operator>=(const Value& left, const Value& right);
	//! Postfix increment operator.
	friend Value operator++(Value& other, int);
	//! Postfix decriment operator.
	friend Value operator--(Value& other, int);
	//! Prefix increment operator.
	friend Value& operator++(Value& other);
	//! Prefix decriment operator.
	friend Value& operator--(Value& other);
	//! Self sum operator.
	Value& operator+=(const Value& other);
	//! Self sub operator.
	Value& operator-=(const Value& other);
	//! Self mul operator.
	Value& operator*=(const Value& other);
	//! Self div operator.
	Value& operator/=(const Value& other);
	//! Self mod operator.
	Value& operator%=(const Value& other);
	//! Self bit and operator.
	Value& operator&=(const Value& other);
	//! Self bit or operator.
	Value& operator|=(const Value& other);
	//! Self xor operator.
	Value& operator^=(const Value& other);
	//! Self left shift operator.
	Value& operator<<=(const Value& other);
	//! Self right shift operator.
	Value& operator>>=(const Value& other);
	//! Returns negative number.
	Value operator+() const;
	//! Returns negative number.
	Value operator-() const;
	//! Logical not operator.
	Value operator!() const;
	//! Changes types.
	void ChangeToType(Type type);

	//
	// Private members.
	//
private:
	//! Returns absolute value even if unsigned.
	template<typename T>
	std::enable_if_t<std::is_unsigned_v<T>, T> GetAbs(T value) 
	{
		return value;
	}
	template<typename T>
	std::enable_if_t<std::is_signed_v<T>, T> GetAbs(T value)
	{
		if (value < static_cast<T>(0)) {
			return -value;
		}
		return value;
	}
	//! Addes to Value template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, void> SelfAdd(T value);
	//! Multiplies Value on template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, void> SelfMul(T value);
	//! Divedes Value by template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>, void> SelfDiv(T value);

	//
	// Private members.
	//
private:
	//! Simple values.
	ValueImpl values_ = {0};
	//! String value.
	std::string string_ = {};
	//! Value type.
	Type type_ = T_NULL;
};

Value operator+(const Value& left, const Value& right);
Value operator-(const Value& left, const Value& right);
Value operator*(const Value& left, const Value& right);
Value operator/(const Value& left, const Value& right);
Value operator%(const Value& left, const Value& right);
Value operator&&(const Value& left, const Value& right);
Value operator||(const Value& left, const Value& right);
Value operator&(const Value& left, const Value& right);
Value operator|(const Value& left, const Value& right);
Value operator^(const Value& left, const Value& right);
Value operator<<(const Value& left, const Value& right);
Value operator>>(const Value& left, const Value& right);
Value operator==(const Value& left, const Value& right);
Value operator!=(const Value& left, const Value& right);
Value operator<(const Value& left, const Value& right);
Value operator>(const Value& left, const Value& right);
Value operator<=(const Value& left, const Value& right);
Value operator>=(const Value& left, const Value& right);
Value operator++(Value& other, int);
Value operator--(Value& other, int);
Value& operator++(Value& other);
Value& operator--(Value& other);

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, void> Value::SelfAdd(T value)
{
	constexpr unsigned long long int max_uint = ~0ull;
	constexpr long long int max_int = ~(1ll << 63);
	constexpr long long int min_int = 1ll << 63;

	if (value == static_cast<T>(0)) {
		return;
	}

	if (type_ == T_BOOL)
	{
		if (value > static_cast<T>(0))
		{
			if (value > static_cast<T>(1) || values_.bool_ == true) {
				ChangeToType(T_UINT);
			}
		}
		else
		{
			if (value < static_cast<T>(-1) || values_.bool_ == false) {
				ChangeToType(T_INT);
			}
		}
	}

	if (type_ == T_UINT)
	{
		if (value < static_cast<T>(0)) 
		{
			if (values_.uint_ < GetAbs(value))
			{

				if (values_.uint_ > max_int) {
					value += max_uint;
				}
				ChangeToType(T_INT);
			}
		}
		else if (value > (max_uint - values_.uint_)) {
			ChangeToType(T_DOUBLE);
		}
	}

	if (type_ == T_INT)
	{
		if (value > static_cast<T>(0)
			&& (static_cast<unsigned long long int>(max_int) - static_cast<unsigned long long int>(values_.sint_) < value))
		{
			ChangeToType(T_UINT);

			if (values_.uint_ > static_cast<unsigned long long int>(max_int)) 
			{
				value -= max_uint;

				if (std::is_floating_point_v<T> && (max_uint - values_.uint_ < value)) {
					ChangeToType(T_DOUBLE);
				}
			}
			else if (max_uint - values_.uint_ < value) {
				ChangeToType(T_DOUBLE);
			}

		}
		else if (value < static_cast<T>(0)
			&& (static_cast<unsigned long long int>(values_.sint_) - static_cast<unsigned long long int>(min_int) < GetAbs(value)))
		{
			ChangeToType(T_DOUBLE);
		}
	}

	switch (type_)
	{
	case T_BOOL:
		values_.bool_ += value;
		break;

	case T_UINT:
		values_.uint_ += value;
		break;
		
	case T_INT:
		values_.sint_ += value;
		break;

	case T_DOUBLE:
		values_.double_ += value;
		break;
	}
}

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, void> Value::SelfMul(T value)
{
	constexpr unsigned long long int max_uint = ~0ull;
	constexpr long long int max_int = ~(1ll << 63);
	constexpr long long int min_int = 1ll << 63;

	if (IsEmpty() || value == static_cast<T>(1)) {
		return;
	}

	if (type_ == T_BOOL)
	{
		if (value < static_cast<T>(0)) {
			ChangeToType(T_INT);
		}
		else if (value > static_cast<T>(1)) {
			ChangeToType(T_UINT);
		}
	}

	if (type_ == T_UINT)
	{
		if (value < static_cast<T>(0)) 
		{
			if (values_.uint_ > max_int) 
			{
				if (static_cast<double>(value) > -1.0)
				{
					values_.uint_ *= GetAbs(value);
					value = -1.0;
					
					if (values_.uint_ > max_int) {
						ChangeToType(T_DOUBLE);
					}
					else {
						ChangeToType(T_INT);
					}
				}
			}
			else {
				ChangeToType(T_INT);
			}
		}
		else if (static_cast<double>(values_.uint_) * value > (static_cast<double>(max_uint) - 800.0)) {
			ChangeToType(T_DOUBLE);
		}
	}

	if (type_ == T_INT && std::abs(static_cast<double>(value)) > 1)
	{
		if (value < static_cast<T>(0))
		{
			if (values_.sint_ == (1ll << 63)) {
				ChangeToType(T_DOUBLE);
			}
			else 
			{
				values_.sint_ *= -1;
				value = GetAbs(value);
			}
		}

		if (type_ != T_DOUBLE && std::abs(static_cast<double>(values_.sint_)) * value > static_cast<double>(max_int)) 
		{
			if (values_.sint_ < 0) {
				ChangeToType(T_DOUBLE);
			}
			else if (static_cast<double>(values_.sint_) * value > (static_cast<double>(max_uint) - 800.0)) {
				ChangeToType(T_DOUBLE);
			}
			else {
				ChangeToType(T_UINT);
			}
		}
	}

	switch (type_)
	{
	case T_BOOL:
		values_.uint_ *= value;
		if (values_.uint_ > 1ull) {
			values_.uint_ = 1ull;
		}
		break;

	case T_UINT:
		values_.uint_ *= value;
		break;

	case T_INT:
		values_.sint_ *= value;
		break;

	case T_DOUBLE:
		values_.double_ *= value;
		break;
	}
}

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, void> Value::SelfDiv(T value)
{
	constexpr unsigned long long int max_uint = ~0ull;
	constexpr long long int max_int = ~(1ll << 63);
	constexpr long long int min_int = 1ll << 63;

	if (value == static_cast<T>(0)) {
		throw BadOperation{ "Devision by zero" };
	}

	if (IsEmpty() || value == static_cast<T>(1)) {
		return;
	}

	if (type_ == T_BOOL)
	{
		if (value < static_cast<T>(0)) {
			ChangeToType(T_INT);
		}
		else if (value < static_cast<T>(1)) {
			ChangeToType(T_UINT);
		}
	}

	if (type_ == T_UINT)
	{
		if (value < static_cast<T>(0))
		{
			if (values_.uint_ > max_int)
			{
				if (static_cast<double>(value) < -1.0)
				{
					values_.uint_ /= GetAbs(value);
					value = -1.0;

					if (values_.uint_ > max_int) {
						ChangeToType(T_DOUBLE);
					}
					else {
						ChangeToType(T_INT);
					}
				}
			}
			else {
				ChangeToType(T_INT);
			}
		}
		else if (static_cast<double>(values_.uint_) / value > (static_cast<double>(max_uint) - 800.0)) {
			ChangeToType(T_DOUBLE);
		}
	}

	if (type_ == T_INT && std::abs(static_cast<double>(value)) < 1)
	{
		if (value < static_cast<T>(0))
		{
			if (values_.sint_ == (1ll << 63)) {
				ChangeToType(T_DOUBLE);
			}
			else
			{
				values_.sint_ = -values_.sint_;
				value = GetAbs(value);
			}
		}

		if (type_ != T_DOUBLE && std::abs(static_cast<double>(values_.sint_)) / value > static_cast<double>(max_int))
		{
			if (values_.sint_ < 0) {
				ChangeToType(T_DOUBLE);
			}
			else if (static_cast<double>(values_.sint_) / value > (static_cast<double>(max_uint) - 800.0)) {
				ChangeToType(T_DOUBLE);
			}
			else {
				ChangeToType(T_UINT);
			}
		}
	}

	switch (type_)
	{
	case T_BOOL:
		values_.uint_ /= value;
		if (values_.uint_ > 1ull) {
			values_.uint_ = 1ull;
		}
		break;

	case T_UINT:
		values_.uint_ /= value;
		break;

	case T_INT:
		if (std::is_signed_v<T>) {
			values_.sint_ /= value;
		}
		else {
			values_.sint_ /= static_cast<long long int>(value);
		}
		break;

	case T_DOUBLE:
		values_.double_ /= value;
		break;
	}

}



} // namespace calc_parser
} // namespace bwn