#pragma once

#include <string>
#include <type_traits>

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
		T_INT		= 0x02,
		T_DOUBLE	= 0x04,
		T_STRING	= 0x08,

		T_INTEGRAL	= T_INT | T_BOOL,
		T_NUMBER	= T_INTEGRAL | T_DOUBLE
	};
	//
	// Private classes.
	//
private:
	union ValueImpl
	{
		long long int sint_;
		double double_;
		bool bool_;
	};

	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Value() = default;
	//! Constructor from unsigned int.
	Value(unsigned int value);
	//! Constructor from int.
	Value(int value);
	//! Constructor from int.
	Value(long long int value);
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
	//! Returns value as int.
	signed long long int AsInt() const;
	//! Returns value as double.
	double AsDouble() const;
	//! Returns value as bool.
	bool AsBool() const;
	//! Returns value as string.
	std::string AsString() const;
	//! Returns Integral representation of value.
	long long int AsIntegral() const;
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
	//! Returns string representation of a value type.
	static const char* TypeAsString(Type type);

	//
	// Private members.
	//
private:
	//! Returns absolute value even if unsigned.
	template<typename T>
	typename std::enable_if<std::is_unsigned<T>::value, T>::type GetAbs(T value)
	{
		return value;
	}
	template<typename T>
	typename std::enable_if<std::is_signed<T>::value, T>::type GetAbs(T value)
	{
		if (value < static_cast<T>(0)) {
			return -value;
		}
		return value;
	}
	//! Addes to Value template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type SelfAdd(T value);
	//! Multiplies Value on template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type SelfMul(T value);
	//! Divides Value by template number type with all overflow checks, works only for arithmetic types.
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type SelfDiv(T value);

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
typename std::enable_if<std::is_arithmetic<T>::value, void>::type Value::SelfAdd(T value)
{
	constexpr long long int max_int = ~(1ll << 63);
	constexpr long long int min_int = 1ll << 63;

	if (value == static_cast<T>(0)) {
		return;
	}

	if (type_ == T_BOOL)
	{
		const bool overflow = value > static_cast<T>(0) && (value > static_cast<T>(1) || values_.bool_ == true);
		const bool underflow = value < static_cast<T>(0) && (GetAbs(value) > static_cast<T>(1) || values_.bool_ == false);

		if (underflow || overflow) {
			ChangeToType(T_INT);
		}
	}

	if (type_ == T_INT)
	{
		if (std::is_floating_point<T>::value)
		{
			double approximate_result = static_cast<double>(values_.sint_) + value;

			approximate_result += approximate_result > 0.0 ? 1300.0 : -1300.0;

			if (approximate_result > static_cast<double>(max_int) || approximate_result < static_cast<double>(min_int)) {
				ChangeToType(T_DOUBLE);
			}
		}
		else
		{
			const unsigned long long ull_value = static_cast<unsigned long long>(GetAbs(value));

			const bool overflow = value > static_cast<T>(0) && ((static_cast<unsigned long long>(max_int) - static_cast<unsigned long long>(values_.sint_)) < ull_value);
			const bool underflow = value < static_cast<T>(0) && ((static_cast<unsigned long long>(values_.sint_) - static_cast<unsigned long long>(min_int)) < ull_value);

			if (underflow || overflow) {
				ChangeToType(T_DOUBLE);
			}
		}		
	}

	switch (type_)
	{
	case T_BOOL:
		values_.sint_ += static_cast<long long int>(value);

		if (values_.sint_) {
			values_.bool_ = true;
		}
		break;
		
	case T_INT:
		values_.sint_ += static_cast<long long int>(value);
		break;

	case T_DOUBLE:
		values_.double_ += value;
		break;

	default:
		break;
	}
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type Value::SelfMul(T value)
{
	constexpr long long int max_int = ~(1ll << 63);
	constexpr long long int min_int = 1ll << 63;

	if (IsEmpty() || value == static_cast<T>(1)) {
		return;
	}

	if (type_ == T_BOOL)
	{
		if (value < static_cast<T>(0) || value > static_cast<T>(1)) {
			ChangeToType(T_INT);
		}
	}

	if (type_ == T_INT && GetAbs(value) >= static_cast<T>(1))
	{
		if (values_.sint_ == (1ll << 63)
			&& value < static_cast<T>(0)
			&& GetAbs(value) == static_cast<T>(1))
		{
			ChangeToType(T_DOUBLE);
		}
		else
		{
			double approximate_result = static_cast<double>(values_.sint_) * value;

			approximate_result += approximate_result > 0.0 ? 1300.0 : -1300.0;

			if (approximate_result > static_cast<double>(max_int) || approximate_result < static_cast<double>(min_int)) {
				ChangeToType(T_DOUBLE);
			}
		}
	}

	switch (type_)
	{
	case T_BOOL:
	case T_INT:
		values_.sint_ *= value;
		break;

	case T_DOUBLE:
		values_.double_ *= value;
		break;

	default:
		break;
	}
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, void>::type Value::SelfDiv(T value)
{
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
		if (value < static_cast<T>(1)) {
			ChangeToType(T_INT);
		}
	}

	if (type_ == T_INT && GetAbs(value) < static_cast<T>(1))
	{
		if (values_.sint_ == (1ll << 63)
			&& value < static_cast<T>(0)
			&& GetAbs(value) == static_cast<T>(1))
		{
			ChangeToType(T_DOUBLE);
		}
		else
		{
			double approximate_result = static_cast<double>(values_.sint_) / value;

			approximate_result += approximate_result > 0.0 ? 1300.0 : -1300.0;

			if (approximate_result > static_cast<double>(max_int) || approximate_result < static_cast<double>(min_int)) {
				ChangeToType(T_DOUBLE);
			}
		}
	}

	switch (type_)
	{
	case T_BOOL:		
	case T_INT:
		values_.sint_ /= value;
		break;

	case T_DOUBLE:
		values_.double_ /= value;
		break;

	default:
		break;
	}

}

} // namespace calc_parser
} // namespace bwn
