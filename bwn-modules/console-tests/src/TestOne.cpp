#include "TestOne.h"

#include <iostream>

#define TESTONE_BINARY_RVALUE_OP(op) \
TestOne operator op (const TestOne& left, const TestOne& right) \
{ \
	if (!(left.mode_ & TestOne::T_SILENT_LOGIC_OPS)) { \
		std::cout << left.color_ << "TestOne binary op \"" #op "\" ( " << left.x_ << " | " << right.x_ << " )." << bwn::console_color::reset << std::endl; \
	} \
	return TestOne(left.x_ op right.x_, ((left.mode_ & TestOne::T_COPY_MODE_ON_CREATION) ? left.mode_ : 0), ((left.mode_ & TestOne::T_COPY_COLOR_ON_CREATION) ? left.color_ : bwn::console_color::GREEN)); \
}

#define TESTONE_BINARY_LVALUE_OP(op) \
TestOne& TestOne::operator op (const TestOne& other) \
{ \
	if (!(mode_ & TestOne::T_SILENT_LVALUE_OPS)) { \
		std::cout << color_ << "TestOne binary op \"" #op "\" ( " << x_ << "/" << other.x_ << " )." << bwn::console_color::reset << std::endl; \
	} \
	x_ op other.x_; \
	return *this; \
}

#define TESTONE_PREFIX_LVALUE_OP(op) \
TestOne& operator op (TestOne& other) \
{ \
	if (!(other.mode_ & TestOne::T_SILENT_LVALUE_UNARY_OPS)) { \
		std::cout << other.color_ << "TestOne prefix unary op \"" #op "\" ( " << other.x_ << " )." << bwn::console_color::reset << std::endl; \
	} \
	op other.x_; \
	return other; \
}

#define TESTONE_POSTFIX_LVALUE_OP(op) \
const TestOne operator op(TestOne& other, int) \
{ \
	if (!(other.mode_ & TestOne::T_SILENT_LVALUE_UNARY_OPS)) { \
		std::cout << other.color_ << "TestOne postfix unary op \"" #op "\" ( " << other.x_ << " )." << bwn::console_color::reset  << std::endl; \
	} \
	TestOne out(other.x_, ((other.mode_ & TestOne::T_COPY_MODE_ON_CREATION) ? other.mode_ : 0), ((other.mode_ & TestOne::T_COPY_COLOR_ON_CREATION) ? other.color_ : bwn::console_color::GREEN)); \
	op other.x_; \
	return out; \
}

#define TESTONE_PREFIX_RVALUE_OP(op) \
TestOne TestOne::operator op () const \
{ \
	if (!(mode_ & TestOne::T_SILENT_RVALUE_UNARY_OPS)) { \
		std::cout << color_ << "TestOne unary op \"" #op "\" ( " << x_ << " )." << bwn::console_color::reset  << std::endl; \
	} \
	return TestOne(op x_, ((mode_ & TestOne::T_COPY_MODE_ON_CREATION) ? mode_ : 0), ((mode_ & TestOne::T_COPY_COLOR_ON_CREATION) ? color_ : bwn::console_color::GREEN)); \
}

TestOne::TestOne()
	: x_ { 0 }
	, mode_{ 0 }
{
	std::cout << color_ << "TestOne simple constructor." << bwn::console_color::reset << std::endl;
}

TestOne::TestOne(int in)
	: x_{ in }
	, mode_{ 0 }
{
	std::cout << color_ << "TestOne constructor ( " << x_ << " )." << bwn::console_color::reset << std::endl;
}

TestOne::TestOne(int in, uint32_t mode, bwn::console_color color)
	: x_{ in }
	, mode_{ mode }
	, color_ { color }
{
	if (!(mode_ & T_SILENT_CONSTRUCTION)) {
		std::cout << color_ << "TestOne constructor ( " << x_ << " )." << bwn::console_color::reset << std::endl;
	}
}

TestOne::operator int()
{
	if (!(mode_ & T_SILENT_CONVERTION)) {
		std::cout << color_ << "TestOne cast operator ( " << x_ << " )." << bwn::console_color::reset << std::endl;
	}
	return x_;
}

TestOne::TestOne(const TestOne& other)
	: x_{ other.x_ }
	, mode_{ 0 }
{
	if (other.mode_ & T_COPY_MODE_ON_CREATION) {
		mode_ = other.mode_;
	}
	if (other.mode_ & T_COPY_COLOR_ON_CREATION) {
		color_ = other.color_;
	}

	if (!(mode_ & T_SILENT_CONSTRUCTION)) {
		std::cout << color_ << "TestOne copy constructor ( " << x_ << " )." << bwn::console_color::reset << std::endl;
	}
}

TestOne::TestOne(TestOne&& other) noexcept
	: mode_{ 0 }
{
	if (other.mode_ & T_COPY_MODE_ON_CREATION) {
		mode_ = other.mode_;
	}
	if (other.mode_ & T_COPY_COLOR_ON_CREATION) {
		color_ = other.color_;
	}

	if (!(mode_ & T_SILENT_CONSTRUCTION)) {
		std::cout << color_ << "TestOne move constructor ( " << x_ << " | " << other.x_ << " )." << bwn::console_color::reset << std::endl;
	}
	std::swap<int>(x_, other.x_);
}

TestOne& TestOne::operator=(const TestOne& other)
{
	if (this == &other)
		return *this;

	if (other.mode_ & T_COPY_MODE_ON_ASS) {
		mode_ = other.mode_;
	}
	if (other.mode_ & T_COPY_COLOR_ON_ASS) {
		color_ = other.color_;
	}

	if (!(mode_ & T_SILENT_ASS_OPS)) {
		std::cout << color_ << "TestOne copy operator ( " << x_ << " | " << other.x_ << " )." << bwn::console_color::reset << std::endl;
	}

	x_ = other.x_;

	return *this;
}

TestOne& TestOne::operator=(TestOne&& other) noexcept
{
	if (this == &other)
		return *this;

	if (other.mode_ & T_COPY_MODE_ON_ASS) {
		mode_ = other.mode_;
	}
	if (other.mode_ & T_COPY_COLOR_ON_ASS) {
		color_ = other.color_;
	}

	if (!(mode_ & T_SILENT_ASS_OPS)) {
		std::cout << color_ << "TestOne move operator ( " << x_ << " | " << other.x_ << " )." << bwn::console_color::reset << std::endl;
	}

	std::swap<int>(x_, other.x_);

	return *this;
}

TestOne::~TestOne()
{
	if (!(mode_ & T_SILENT_DESTRUCTION)) {
		std::cout << color_ << "TestOne destructor ( " << x_ << " )." << bwn::console_color::reset << std::endl;
	}
}

TESTONE_BINARY_RVALUE_OP(+)
TESTONE_BINARY_RVALUE_OP(-)
TESTONE_BINARY_RVALUE_OP(*)
TESTONE_BINARY_RVALUE_OP(/)
TESTONE_BINARY_RVALUE_OP(%)
TESTONE_BINARY_RVALUE_OP(&)
TESTONE_BINARY_RVALUE_OP(|)
TESTONE_BINARY_RVALUE_OP(^)
TESTONE_BINARY_RVALUE_OP(&&)
TESTONE_BINARY_RVALUE_OP(||)
TESTONE_BINARY_RVALUE_OP(==)
TESTONE_BINARY_RVALUE_OP(!=)
TESTONE_BINARY_RVALUE_OP(<)
TESTONE_BINARY_RVALUE_OP(>)
TESTONE_BINARY_RVALUE_OP(<=)
TESTONE_BINARY_RVALUE_OP(>=)

TESTONE_BINARY_LVALUE_OP(+=)
TESTONE_BINARY_LVALUE_OP(-=)
TESTONE_BINARY_LVALUE_OP(*=)
TESTONE_BINARY_LVALUE_OP(/=)
TESTONE_BINARY_LVALUE_OP(%=)
TESTONE_BINARY_LVALUE_OP(&=)
TESTONE_BINARY_LVALUE_OP(|=)
TESTONE_BINARY_LVALUE_OP(^=)

TESTONE_PREFIX_LVALUE_OP(++)
TESTONE_PREFIX_LVALUE_OP(--)

TESTONE_POSTFIX_LVALUE_OP(++)
TESTONE_POSTFIX_LVALUE_OP(--)

TESTONE_PREFIX_RVALUE_OP(+)
TESTONE_PREFIX_RVALUE_OP(-)
TESTONE_PREFIX_RVALUE_OP(!)