#pragma once

#include <vector>
#include <string>

//
// Forward declaration for friend functions.
//
namespace bwn
{

class NumeralSystem;

}


namespace std
{

bwn::NumeralSystem abs(const bwn::NumeralSystem& number);
void swap(bwn::NumeralSystem& left, bwn::NumeralSystem& right);

}

namespace bwn
{

NumeralSystem operator+ (const NumeralSystem& left, const NumeralSystem& right);
NumeralSystem operator- (const NumeralSystem& left, const NumeralSystem& right);
NumeralSystem operator* (const NumeralSystem& left, const NumeralSystem& right);
NumeralSystem operator/ (const NumeralSystem& left, const NumeralSystem& right);
bool operator==(const NumeralSystem& left, const NumeralSystem& right);
bool operator!=(const NumeralSystem& left, const NumeralSystem& right);
bool operator>(const NumeralSystem& left, const NumeralSystem& right);
bool operator<(const NumeralSystem& left, const NumeralSystem& right);
bool operator<=(const NumeralSystem& left, const NumeralSystem& right);
bool operator>=(const NumeralSystem& left, const NumeralSystem& right);

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
	// Construction and destruction.
	//
public:
	//! Constructor from base.
	explicit NumeralSystem(Digit base);
	//! Constructor from base and start value of base ten.
	NumeralSystem(Digit base, int64_t value);
	//! Copy constructor.
	NumeralSystem(const NumeralSystem& other) = default;
	//! Copy constructor with different base.
	NumeralSystem(const NumeralSystem& other, Digit base);
	//! Move constructor.
	NumeralSystem(NumeralSystem&& other) noexcept(std::is_nothrow_move_constructible<Container>::value) = default;
	//! Move constructor with a different base.
	NumeralSystem(NumeralSystem&& other, Digit base) noexcept(std::is_nothrow_move_constructible<Container>::value);

	//! Copy operator (does not change base).
	NumeralSystem& operator=(const NumeralSystem& other);
	//! Move operator (does not change base).
	NumeralSystem& operator=(NumeralSystem&& other) noexcept(std::is_nothrow_move_assignable<Container>::value);

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
	std::size_t GetLength() const;
	//! Swaps values of two numeral systems.
	void Swap(NumeralSystem& other);
	//! Returns false if number equal to zero;
	explicit operator bool() const;
	//! Adds value of other numeral system.
	NumeralSystem& operator+=(const NumeralSystem& other);
	//! Substracts value of other numeral system.
	NumeralSystem& operator-=(const NumeralSystem& other);
	//! Multiplies value of other numeral system.
	NumeralSystem& operator*=(const NumeralSystem& other);
	//! Divides on value of other numeral system.
	NumeralSystem& operator/=(const NumeralSystem& other);
	//! Adds together two numeral system, return system with base of first one.
	friend NumeralSystem operator+ (const NumeralSystem& left, const NumeralSystem& right);
	//! Substructs two numeral system, return system with base of first one.
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
	//! Returns number as absolute version.
	friend NumeralSystem std::abs(const NumeralSystem& number);

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
	//! Multiplies system by numbers less then max base.
	void FastMul(Digit value);
	//! Makes number abs.
	void MakeAbs();
	//! Compares to values but only on highest digits.
	static bool LessOnLasts(const NumeralSystem& left, const NumeralSystem& right);

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
