#pragma once

#include <array>

#if defined(TYPE_TREAT_STRING_VIEW)
namespace bwn
{
namespace type_treat
{

using StringView = TYPE_TREAT_STRING_VIEW;

} // namespace type_treat
} // namespace bwn
#elif __cplusplus >= 201703L
#include <string_view>
namespace bwn
{
namespace type_treat
{

using StringView = std::string_view;

} // namespace type_treat
} // namespace bwn
#else
#include <experimental/string_view>
namespace bwn
{
namespace type_treat
{

using StringView = std::experimental::string_view;

} // namespace type_treat
} // namespace bwn
#endif

namespace bwn
{

template<char...CharsV>
struct CtimeString
{
	//
	// Public aliases
	//
public:
	//! Type used as string representation in runtime.
	using StringView = type_treat::StringView;

	//
	// Public interface.
	//
public:
	//! Returns string representation for runtime uses.
	static StringView Get() noexcept
	{
		static constexpr std::array<char, sizeof...(CharsV)> buffer{ CharsV... };
		return StringView(buffer.data(), buffer.size());
	}
};

template<typename...>
struct CtimeConcat;

template<char...FirstVs, char...SecondVs>
struct CtimeConcat<
	CtimeString<FirstVs...>,
	CtimeString<SecondVs...>>
{
	//! Concatenation of two Strings.
	using String = CtimeString<FirstVs..., SecondVs...>;
};

template<char...FirstVs, char...SecondVs, typename...TailTs>
struct CtimeConcat<
	CtimeString<FirstVs...>,
	CtimeString<SecondVs...>,
	TailTs...>
{
	//! Recursive concatenation of Strings.
	using String = typename CtimeConcat<CtimeString<FirstVs..., SecondVs...>, TailTs...>::String;
};

template<typename...TypeTs>
using CtimeConcatT = typename CtimeConcat<TypeTs...>::String;

template<uint64_t, typename>
struct CtimeParseUint;
template<uint64_t ValueV, char...CharsVs>
struct CtimeParseUint<ValueV, CtimeString<CharsVs...>>
{
	//! Recursive parsing of number in base 10.
	using String = typename CtimeParseUint<ValueV / 10, CtimeString<0x30 + ValueV % 10, CharsVs...>>::String;
};
template<char FirstV, char...CharsVs>
struct CtimeParseUint<0, CtimeString<FirstV, CharsVs...>>
{
	//! Recursion end.
	using String = CtimeString<FirstV, CharsVs...>;
};
template<>
struct CtimeParseUint<0, CtimeString<>>
{
	//! Extreme case of stopping recursion if initial number is zero.
	using String = CtimeString<'0'>;
};
template<uint64_t ValueV>
using CtimeParseUintT = typename CtimeParseUint<ValueV, CtimeString<>>::String;

template<int64_t ValueV, typename = std::void_t<>>
struct CtimeParseInt
{
	//! Regular parsing as uint for positive numbers.
	using String = CtimeParseUintT<static_cast<uint64_t>(ValueV)>;
};
template<int64_t ValueV>
struct CtimeParseInt<ValueV, typename std::enable_if<(ValueV < 0)>::type>
{
	//! Parsing of number as negative.
	using String = CtimeConcatT<
	    CtimeString<'-'>,
		CtimeParseUintT<static_cast<uint64_t>(-ValueV)>>;
};
template<int64_t ValueV>
using CtimeParseIntT = typename CtimeParseInt<ValueV, CtimeString<>>::String;

template<uint64_t, typename>
struct CtimeParseUintHex;
template<uint64_t ValueV, char...CharsVs>
struct CtimeParseUintHex<ValueV, CtimeString<CharsVs...>>
{
	//! Recursive parsing of number in base 16.
	using String = typename CtimeParseUintHex<ValueV / 16, CtimeString<0x30 + ((ValueV % 16) > 9) * 0x27 + ValueV % 16 , CharsVs...>>::String;
};
template<char FirstV, char...CharsVs>
struct CtimeParseUintHex<0, CtimeString<FirstV, CharsVs...>>
{
	//! Recursion end.
	using String = CtimeString<FirstV, CharsVs...>;
};
template<>
struct CtimeParseUintHex<0, CtimeString<>>
{
	//! Extreme case of stopping recursion if initial number is zero.
	using String = CtimeString<'0'>;
};
template<uint64_t ValueV>
using CtimeParseUintHexT = typename CtimeParseUintHex<ValueV, CtimeString<>>::String;

//! Wraps CtimeString in brackets if value is true.
template<bool, typename>
struct WrapIf;
template<char...CharsVs>
struct WrapIf<true, CtimeString<CharsVs...>>
{
	using String = CtimeString<'(', CharsVs..., ')'>;
};
template<char...CharsVs>
struct WrapIf<false, CtimeString<CharsVs...>>
{
	using String = CtimeString<CharsVs...>;
};

//! Wraps CtimeString in brackets if it's not empty.
template<typename>
struct WrapIfUnempty;
template<char...CharsVs>
struct WrapIfUnempty<CtimeString<CharsVs...>>
{
	using String = CtimeString<'(', CharsVs..., ')'>;
};
template<>
struct WrapIfUnempty<CtimeString<>>
{
	using String = CtimeString<>;
};

//
// Forward declaration.
//
template<typename T, typename...Args>
struct TypeTreat;

//
// Ptrless, class for dereferencing classes all treats of pointers.
//
enum ReferenceType
{
	NONE_REF    = 0x0,
	LVALUE_REF  = 0x1,
	RVALUE_REF  = 0x2
};

//! Ending of recursion.
template<typename TypeT, size_t PtrNumV = 0, size_t RefNumV = 0>
struct Ptrless : std::false_type
{
	using Type = TypeT;
	enum { ref_nesting = PtrNumV, ptr_nesting = RefNumV };
	using String = CtimeString<>;
};
//! Start of recursion with lvalue reference.
template<typename TypeT>
struct Ptrless<TypeT&> : std::true_type
{
	using Nested =  Ptrless<TypeT, 0, LVALUE_REF>;
	enum { ref_nesting = LVALUE_REF, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'&'>>;
};
//! Start of recursion with rvalue reference.
template<typename TypeT>
struct Ptrless<TypeT&&> : std::true_type
{
	using Nested =  Ptrless<TypeT, 0, RVALUE_REF>;
	enum { ref_nesting = RVALUE_REF, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'&', '&'>>;
};
//! Recursion for pointer type.
template<typename TypeT, size_t PtrNumV, size_t RefNumV>
struct Ptrless<TypeT*, PtrNumV, RefNumV> : std::true_type
{
	using Nested =  Ptrless<TypeT, PtrNumV + 1, RefNumV>;
	enum { ref_nesting = RefNumV, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'*'>>;
};
//! Start of recursion with pointer type.
template<typename TypeT>
struct Ptrless<TypeT*> : std::true_type
{
	using Nested =  Ptrless<TypeT, 1, NONE_REF>;
	enum { ref_nesting = NONE_REF, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'*'>>;
};
//! Recursion for const pointer type.
template<typename TypeT, size_t PtrNumV, size_t RefNumV>
struct Ptrless<TypeT *const, PtrNumV, RefNumV> : std::true_type
{
	using Nested =  Ptrless<TypeT, PtrNumV + 1, RefNumV>;
	enum { ref_nesting = RefNumV, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'*','c','o','n','s','t'>>;
};
//! Start of recursion with const pointer type.
template<typename TypeT>
struct Ptrless<TypeT *const> : std::true_type
{
	using Nested =  Ptrless<TypeT, 1, NONE_REF>;
	enum { ref_nesting = NONE_REF, ptr_nesting = Nested::ptr_nesting };
	using Type = typename Nested::Type;
	using String = CtimeConcatT<typename Nested::String, CtimeString<'*','c','o','n','s','t'>>;
};


//
// ArrayTreat, class about all needed treats of arrays.
//
template<typename TypeT>
struct ArrayTreat : std::false_type
{
	using Type = TypeT;
	using ArrayPtrLess = TypeT;
	using String = CtimeString<>;
};
template<typename TypeT, std::size_t SizeV>
struct ArrayTreat<TypeT[SizeV]> : std::true_type
{
	using Type = TypeT;
	using ArrayPtrLess = typename ArrayTreat<typename Ptrless<TypeT>::Type>::ArrayPtrLess;
	using String = CtimeConcatT<CtimeString<'['>, CtimeParseUintT<SizeV>, CtimeString<']'>>;
};
template<typename TypeT>
struct ArrayTreat<TypeT[]> : std::true_type
{
	using Type = TypeT;
	using ArrayPtrLess = typename ArrayTreat<typename Ptrless<TypeT>::Type>::ArrayPtrLess;
	using String = CtimeString<'[',']'>;
};

//! Recursion class for representing nesting arrays.
template<typename TypeT, typename = std::void_t<>>
struct ArrayToString
{
	using String = typename Ptrless<TypeT>::String;
};
//! Recursion.
template<typename TypeT>
struct ArrayToString<TypeT, typename std::enable_if<ArrayTreat<typename Ptrless<TypeT>::Type>::value>::type>
{
private:
	using Clear = typename Ptrless<TypeT>::Type;

public:
	using String = CtimeConcatT<
	    typename ArrayToString<typename ArrayTreat<Clear>::Type>::String,
	    typename WrapIfUnempty<typename Ptrless<TypeT>::String>::String,
	    typename ArrayTreat<Clear>::String>;
};

//
// FunctionTreat, class about all needed treats of functions.
//
template<typename RetT>
struct FunctionTreat : std::false_type
{
	using Return = RetT;
	using ArgsString = CtimeString<>;
};
template<typename RetT>
struct FunctionTreat<RetT()> : std::true_type
{
	using Return = RetT;
	using ArgsString = CtimeString<>;
};
template<typename RetT, typename...ArgsTs>
struct FunctionTreat<RetT(ArgsTs...)> : std::true_type
{
	using Return = RetT;
	using ArgsString = typename TypeTreat<ArgsTs...>::String;
};

//
// TypeName, class setting up names for all needed types.
//
template<typename>
struct TypeName
{
	using String = CtimeString<'d','e','f','a','u','l','t'>;
};
template<typename TypeT>
struct TypeName<const TypeT>
{
	using String = CtimeConcatT<CtimeString<'c','o','n','s','t',' '>, typename TypeName<TypeT>::String>;
};
template<template <typename...> class TypeT, typename...ArgsTs>
struct TypeName<TypeT<ArgsTs...>>
{
	using String = CtimeConcatT<
		CtimeString<'t','e','m','p','l','a','t','e','<'>,
	    typename TypeTreat<ArgsTs...>::String,
		CtimeString<'>'>>;
};

//! Specialization for enabling higher level recursion with TypeTreat.
template<typename RetT, typename...ArgsTs>
struct TypeName<RetT(ArgsTs...)>
{
	using String = typename TypeTreat<RetT(ArgsTs...)>::String;
};
template<typename TypeT, size_t SizeV>
struct TypeName<TypeT[SizeV]>
{
	using String = typename TypeTreat<TypeT[SizeV]>::String;
};
template<typename TypeT>
struct TypeName<TypeT[]>
{
	using String = typename TypeTreat<TypeT[]>::String;
};
template<typename TypeT>
struct TypeName<TypeT*>
{
	using String = typename TypeTreat<TypeT*>::String;
};
template<typename TypeT>
struct TypeName<TypeT *const>
{
	using String = typename TypeTreat<TypeT *const>::String;
};

//! All default types.
template<>
struct TypeName<char>
{
	using String = CtimeString<'c','h','a','r'>;
};
template<>
struct TypeName<unsigned char>
{
	using String = CtimeString<'u','n','s','i','g','n','e','d',' ','c','h','a','r'>;
};
template<>
struct TypeName<short>
{
	using String = CtimeString<'s','h','o','r','t'>;
};
template<>
struct TypeName<unsigned short>
{
	using String = CtimeString<'u','n','s','i','g','n','e','d',' ','s','h','o','r','t'>;
};
template<>
struct TypeName<int>
{
	using String = CtimeString<'i','n','t'>;
};
template<>
struct TypeName<unsigned int>
{
	using String = CtimeString<'u','n','s','i','g','n','e','d',' ','i','n','t'>;
};
template<>
struct TypeName<long>
{
	using String = CtimeString<'l','o','n','g'>;
};
template<>
struct TypeName<unsigned long>
{
	using String = CtimeString<'u','n','s','i','g','n','e','d',' ','l','o','n','g'>;
};
template<>
struct TypeName<long long>
{
	using String = CtimeString<'l','o','n','g',' ','l','o','n','g'>;
};
template<>
struct TypeName<unsigned long long>
{
	using String = CtimeString<'u','n','s','i','g','n','e','d',' ','l','o','n','g',' ','l','o','n','g'>;
};
template<>
struct TypeName<float>
{
	using String = CtimeString<'f','l','o','a','t'>;
};
template<>
struct TypeName<double>
{
	using String = CtimeString<'d','o','u','b','l','e'>;
};
template<>
struct TypeName<long double>
{
	using String = CtimeString<'l','o','n','g',' ','d','o','u','b','l','e'>;
};
template<>
struct TypeName<void>
{
	using String = CtimeString<'v','o','i','d'>;
};
template<>
struct TypeName<bool>
{
	using String = CtimeString<'b','o','o','l'>;
};
template<>
struct TypeName<std::nullptr_t>
{
	using String = CtimeString<'n','u','l','l','p','t','r','_','t'>;
};



//
// TypeTreat, class for actual type parsing.
//
//! Default used for parsing bunch of types as list (with comas).
template<typename TypeT, typename...ArgsTs>
struct TypeTreat
{
	//
	// Public interface.
	//
public:
	//! Compile time string.
	using String = CtimeConcatT<
		typename TypeTreat<TypeT>::String,
		CtimeConcatT<CtimeString<','>, typename TypeTreat<ArgsTs>::String>...>;
	//! Returns string representation.
	static constexpr typename String::StringView Name() noexcept
	{
		return String::Get();
	}
};

template<typename TypeT>
struct TypeTreat<TypeT>
{
	//
	// Private compile time operations.
	//
private:
	using FirstLayer = typename Ptrless<TypeT>::Type;
	using StringThaseOne = typename std::conditional<
		ArrayTreat<FirstLayer>::value,
		typename ArrayToString<TypeT>::String,
		typename Ptrless<TypeT>::String>::type;
	using SecondLayer = typename ArrayTreat<FirstLayer>::ArrayPtrLess;

	template<typename FunctionT, typename PostfixS, typename = std::void_t<>>
	struct FunctionWrapper
	{
		using String = CtimeConcatT<typename TypeName<FunctionT>::String, PostfixS>;
	};

	template<typename FunctionT, typename PostfixS>
	struct FunctionWrapper<FunctionT, PostfixS, typename std::enable_if<FunctionTreat<FunctionT>::value>::type>
	{
		using String = CtimeConcatT<
			typename TypeTreat<typename FunctionTreat<FunctionT>::Return>::String,
			typename WrapIfUnempty<PostfixS>::String,
			typename WrapIf<true, typename FunctionTreat<FunctionT>::ArgsString>::String>;
	};

	//
	// Public interface.
	//
public:
	//! Compile time string.
	using String = typename FunctionWrapper<SecondLayer, StringThaseOne>::String;
	//! Returns string representation.
	static constexpr typename String::StringView Name() noexcept
	{
		return String::Get();
	}
};

} // namespace bwn
