#pragma once

#include "Utilits.h"


struct TestOne
{
	enum
	{
		T_SILENT_CONSTRUCTION			= 0x01,
		T_SILENT_DESTRUCTION			= 0x02,
		T_SILENT_CONVERTION				= 0x04,
		T_SILENT_ASS_OPS				= 0x08,
		T_SILENT_LVALUE_OPS				= 0x10,
		T_SILENT_LOGIC_OPS				= 0x20,
		T_SILENT_HIGH_RVALUE_OPS		= 0x40,
		T_SILENT_LOW_RVALUE_OPS			= 0x80,
		T_SILENT_RVALUE_UNARY_OPS		= 0x100,
		T_SILENT_LVALUE_UNARY_OPS		= 0x200,
		T_SILENT_ALL_OPS = T_SILENT_ASS_OPS 
		| T_SILENT_LVALUE_OPS 
		| T_SILENT_LOGIC_OPS 
		| T_SILENT_HIGH_RVALUE_OPS 
		| T_SILENT_LOW_RVALUE_OPS
		| T_SILENT_RVALUE_UNARY_OPS
		| T_SILENT_LVALUE_UNARY_OPS,
		T_COPY_MODE_ON_CREATION			= 0x400,
		T_COPY_MODE_ON_ASS				= 0x800,
		T_COPY_COLOR_ON_CREATION		= 0x1000,
		T_COPY_COLOR_ON_ASS				= 0x2000,
	};


	TestOne();
	explicit TestOne(int in);
	explicit TestOne(int in, uint32_t mode, bwn::console_color color);
	TestOne(const TestOne& other);
	TestOne(TestOne&& other) noexcept;
	~TestOne();

	TestOne& operator=(const TestOne& other);
	TestOne& operator=(TestOne&& other) noexcept ;

	explicit operator int();

	friend TestOne operator+	(const TestOne& left, const TestOne& right);
	friend TestOne operator-	(const TestOne& left, const TestOne& right);
	friend TestOne operator*	(const TestOne& left, const TestOne& right);
	friend TestOne operator/	(const TestOne& left, const TestOne& right);
	friend TestOne operator%	(const TestOne& left, const TestOne& right);
	friend TestOne operator&	(const TestOne& left, const TestOne& right);
	friend TestOne operator|	(const TestOne& left, const TestOne& right);
	friend TestOne operator^	(const TestOne& left, const TestOne& right);
	friend TestOne operator&&	(const TestOne& left, const TestOne& right);
	friend TestOne operator||	(const TestOne& left, const TestOne& right);
	friend TestOne operator==	(const TestOne& left, const TestOne& right);
	friend TestOne operator!=	(const TestOne& left, const TestOne& right);
	friend TestOne operator<	(const TestOne& left, const TestOne& right);
	friend TestOne operator>	(const TestOne& left, const TestOne& right);
	friend TestOne operator<=	(const TestOne& left, const TestOne& right);
	friend TestOne operator>=	(const TestOne& left, const TestOne& right);
	friend const TestOne operator++	(TestOne& other, int);
	friend const TestOne operator--	(TestOne& other, int);
	friend TestOne& operator++	(TestOne& other);
	friend TestOne& operator--	(TestOne& other);

	TestOne& operator+=	(const TestOne& other);
	TestOne& operator-=	(const TestOne& other);
	TestOne& operator*=	(const TestOne& other);
	TestOne& operator/=	(const TestOne& other);
	TestOne& operator%=	(const TestOne& other);
	TestOne& operator&=	(const TestOne& other);
	TestOne& operator|=	(const TestOne& other);
	TestOne& operator^=	(const TestOne& other);

	TestOne operator+() const;
	TestOne operator-() const;
	TestOne operator!() const;	


	int x_;

private:
	uint32_t mode_;
	bwn::console_color color_ =  { bwn::console_color::GREEN };
};
