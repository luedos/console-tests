#pragma once

#include <vector>
#include <string>

namespace bwn
{

class NumeralSystem final
{
	//
	// Public aliases.
	//
public:
	//! Type of the numerical system.
	using Digit = int32_t;
	//! Type of the container.
	using Container = std::vector<Digit>;

	//
	// Constraction and destruction.
	//
public:
	//! Constractor from base.
	explicit NumeralSystem(Digit base);
	//! Constractor from base and start value of base ten.
	NumeralSystem(Digit base, int64_t value);
	//! Copy constractor.
	NumeralSystem(const NumeralSystem& other) = default;
	//! Copy constractor with different base.
	NumeralSystem(const NumeralSystem& other, Digit base);
	//! Move constractor.
	NumeralSystem(NumeralSystem&& other) noexcept = default;
	//! Move constractor with a different base.
	NumeralSystem(NumeralSystem&& other, Digit base) noexcept;

	//! Copy operator (does not change base).
	NumeralSystem& operator=(const NumeralSystem& other);
	//! Move operator (does not change base).
	NumeralSystem& operator=(NumeralSystem&& other) noexcept;

	//
	// Public interface.
	//
public:
	//! Transforms number into string.
	std::string ToString() const;
	//! Returns base of the system.
	Digit GetBase() const;
	//! Returns numerical system with different base.
	NumeralSystem GetNewBase(Digit base) const;
	//! Changes base of the system.
	void ChangeBase(Digit base);
	//! Returns digit by specific index.
	const Digit& operator[] (std::size_t index) const;
	//! Returns number of digits in number.
	std::size_t GetSize() const;
	//! Swaps values of two numeral systems.
	void Swap(NumeralSystem& other);
	//! Returns false if number equal to zero;
	operator bool() const;
	//! Adds value of other numeral system.
	NumeralSystem& operator+=(const NumeralSystem& other);
	//! Adds value as base 10.
	NumeralSystem& operator+=(int64_t value);
	//! Substracts value of other numeral system.
	NumeralSystem& operator-=(const NumeralSystem& other);
	//! Substracts value as base 10.
	NumeralSystem& operator-=(int64_t value);
	//! Multiplies value of other numeral system.
	NumeralSystem& operator*=(const NumeralSystem& other);
	//! Multiplies value as base 10.
	NumeralSystem& operator*=(int64_t value);
	//! Divides on value of other numeral system.
	NumeralSystem& operator/=(const NumeralSystem& other);
	//! Divides value as base 10.
	NumeralSystem& operator/=(int64_t value);
	//! Adds together two numeral system, return system with base of first one.
	friend NumeralSystem operator+ (const NumeralSystem& left, const NumeralSystem& right);
	//! Substracts two numeral system, return system with base of first one.
	friend NumeralSystem operator- (const NumeralSystem& left, const NumeralSystem& right);
	//! Multiplies together two numeral system, return system with base of first one.
	friend NumeralSystem operator* (const NumeralSystem& left, const NumeralSystem& right);
	//! Divides two numeral system, return system with base of first one.
	friend NumeralSystem operator/ (const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator==(const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator!=(const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator>(const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator<(const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator<=(const NumeralSystem& left, const NumeralSystem& right);
	//! Compares two numeral systems.
	friend bool operator>=(const NumeralSystem& left, const NumeralSystem& right);
	template<typename CharT>
	friend std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& stream, const bwn::NumeralSystem& value);

	//
	// Private methods.
	//
private:
	//! Shifts all values to the right, adding zeros in the beginig of the number.
	void ValueShift(std::size_t shift);
	//! Trims end from zeros, returns finale size.
	std::size_t TrimEnd();
	//! Normalizes number.
	void Normalize();

	//
	// Private members.
	//
private:
	//! All numeral digits.
	Container container_;
	//! Base of the system.
	Digit base_;
};

} // namespace bwn

template<typename CharT>
std::basic_ostream<CharT>& bwn::operator<<(std::basic_ostream<CharT>& stream, const bwn::NumeralSystem& value)
{
	for (int32_t i = value.container_.size() - 1; i >= 0; --i)
	{
		stream << value.container_[i];
		if (i) {
			stream << '|';
		}
	}

	return stream;
}
