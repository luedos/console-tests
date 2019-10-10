#pragma once

#if __cplusplus >= 201703L

#include <iostream>

namespace bwn
{

namespace prjg
{
#if defined(_MSC_VER)
#define BWN_PRJG_FORCE_INLINE __forceinline
#define BWN_PRJG_NO_INLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define BWN_PRJG_FORCE_INLINE __attribute__((always_inline))
#define BWN_PRJG_NO_INLINE __attribute__((noinline))
#else
#define BWN_PRJG_FORCE_INLINE
#define BWN_PRJG_NO_INLINE
#endif
//
// Utils.
//
template<typename...>
struct TypeList {};
template<size_t...>
struct UintList {};

template<size_t N>
struct ComplexityType
{
	enum { complexity = N };
};

template<typename T, typename...Ts>
T&& GetFirstArg(T&& arg, Ts&&...)
{
	return std::forward<T>(arg);
}
template<typename T>
T&& GetFirstArg(T&& arg)
{
	return std::forward<T>(arg);
}

template<typename T, typename...Ts>
struct GetFirstType
{
	using type = T;
};
template<typename T>
struct GetFirstType<T>
{
	using type = T;
};

template<size_t N, size_t...Ns>
struct KeyGen
{
	enum : size_t { value = KeyGen<Ns...>::value ^ (N * (sizeof...(Ns) + 1) * 433494437) };
};
template<size_t N>
struct KeyGen<N>
{
	enum : size_t { value = N * 2971215073};
};

//
// Function generators.
//
enum E_Gen
{
	GENERATOR_MATH		= 0,
	//GENERATOR_SWITCH	= 1,
	GENERATOR_LOOP		= 1,
	GENERATOR_IFELSE	= 2
};
template<size_t Key, size_t Mode, typename Complexity, typename Switch, typename T, typename...Ts>
struct InlineFunc {};

//
// Math generator.
//

// Operations
#if true

enum E_Operation
{
	OP_SUM		= 0,
	OP_SUB		= 1,
	OP_MUL		= 2,
	OP_DIV		= 3,
	OP_PER		= 4
};
template<typename T1, typename T2, size_t Mode>
struct MathOperation;

template<typename T1, typename T2>
struct MathOperation<T1, T2, OP_SUM>
{
	static void BWN_PRJG_FORCE_INLINE Func(T1& left, T2& right);
};
template<typename T1, typename T2>
void BWN_PRJG_FORCE_INLINE MathOperation<T1, T2, OP_SUM>::Func(T1& left, T2& right)
{
	left += right;
}

template<typename T1, typename T2>
struct MathOperation<T1, T2, OP_SUB>
{
	static void BWN_PRJG_FORCE_INLINE Func(T1& left, T2& right);
};
template<typename T1, typename T2>
void BWN_PRJG_FORCE_INLINE  MathOperation<T1, T2, OP_SUB>::Func(T1& left, T2& right)
{
	left -= right;
}

template<typename T1, typename T2>
struct MathOperation<T1, T2, OP_MUL>
{
	static void BWN_PRJG_FORCE_INLINE  Func(T1& left, T2& right);
};
template<typename T1, typename T2>
void BWN_PRJG_FORCE_INLINE  MathOperation<T1, T2, OP_MUL>::Func(T1& left, T2& right)
{
	left *= right;
}

template<typename T1, typename T2>
struct MathOperation<T1, T2, OP_DIV>
{
	static void BWN_PRJG_FORCE_INLINE  Func(T1& left, T2& right);
};
template<typename T1, typename T2>
void BWN_PRJG_FORCE_INLINE  MathOperation<T1, T2, OP_DIV>::Func(T1& left, T2& right)
{
	left /= right ? right : 1;
}

template<typename T1, typename T2>
struct MathOperation<T1, T2, OP_PER>
{
	static void BWN_PRJG_FORCE_INLINE  Func(T1& left, T2& right);
};
template<typename T1, typename T2>
void BWN_PRJG_FORCE_INLINE  MathOperation<T1, T2, OP_PER>::Func(T1& left, T2& right)
{
	left %= right ? right : 1;
}

#endif // Operations

template<size_t Key, typename Complexity, typename T, typename...Ts>
struct InlineFunc<Key, GENERATOR_MATH, Complexity, void, T, Ts...>
{
	static T BWN_PRJG_FORCE_INLINE Func(T& main, Ts...args);
};

template<size_t Key, typename Complexity, typename T, typename...Ts>
T BWN_PRJG_FORCE_INLINE InlineFunc<Key, GENERATOR_MATH, Complexity, void, T, Ts...>::Func(T& main, Ts...args)
{
	constexpr size_t local_key = Key * 3276509 + 94418953;
	
	if constexpr (sizeof...(args))
	{
		MathOperation<T, typename GetFirstType<Ts...>::type, local_key % 5>::Func(main, GetFirstArg(args...));
		InlineFunc<local_key, GENERATOR_MATH, Complexity, void, Ts...>(args...);
	}
	else 
	{
		T additional = local_key;
		MathOperation<T, T, local_key % 5>::Func(main, additional);
	}
	return main;
}

//
// Branch generator.
//
template<size_t Key, typename Complexity, typename T, typename...Ts>
struct InlineFunc<Key, GENERATOR_IFELSE, Complexity, std::enable_if_t<(Complexity::complexity > 20)>, T, Ts...>
{
	static T BWN_PRJG_FORCE_INLINE Func(T& main, Ts...args);
};

template<size_t Key, typename Complexity, typename T, typename...Ts>
T BWN_PRJG_FORCE_INLINE InlineFunc<Key, GENERATOR_IFELSE, Complexity, std::enable_if_t<(Complexity::complexity > 20)>, T, Ts...>::Func(T& main, Ts...args)
{
	constexpr size_t local_key1 = Key * 1354828 + 27644437;
	constexpr size_t local_key2 = local_key1 * 1354828 + 27644437;
	constexpr size_t local_key3 = local_key2 * 1354828 + 27644437;
	
	if constexpr (sizeof...(Ts))
	{
		if (main > Key % 100)
		{
			InlineFunc<local_key1, local_key1 % 3, ComplexityType<Complexity::complexety * 0.6>, void, T, Ts...>(main, args...);
		}
		else if (main > (local_key1 % 1000 + Key % 100))
		{
			InlineFunc<local_key2, local_key2 % 3, ComplexityType<Complexity::complexety * 0.6>, void, T, Ts...>(main, args...);
		}
		else if (main > (local_key2 % 10000 + local_key1 % 1000 + Key % 100))
		{
			InlineFunc<local_key3, local_key3 % 3, ComplexityType<Complexity::complexety * 0.6>, void, T, Ts...>(main, args...);
		}
	}
	else
	{
		InlineFunc<local_key1, local_key1 % 3, ComplexityType<Complexity::complexety * 0.6>, void, T, Ts...>(main, args...);
	}

	return main;
}


//
// Loop generator.
//

template<size_t Key, typename Complexity, typename T, typename...Ts>
struct InlineFunc<Key, GENERATOR_LOOP, Complexity, std::enable_if_t<(Complexity::complexity > 50)>, T, Ts...>
{
	static T BWN_PRJG_FORCE_INLINE Func(T& main, Ts...args);
};

template<size_t Key, typename Complexity, typename T, typename...Ts>
T BWN_PRJG_FORCE_INLINE InlineFunc<Key, GENERATOR_LOOP, Complexity, std::enable_if_t<(Complexity::complexity > 50)>, T, Ts...>::Func(T& main, Ts...args)
{
	constexpr size_t local_key = Key * 1354828 + 27644437;

	for (size_t i = 0; i < local_key % 0xF; ++i)
	{
		InlineFunc<local_key, local_key % 3, ComplexityType<Complexity::complexety * 0.6>, void, T, Ts...>(main, args...);
	}

	return main;
}

//
// Main generator.
//

template<typename T1, typename T2>
struct JunkGen;

template<size_t N, size_t...Ns, typename T, typename...Ts>
struct JunkGen<UintList<N, Ns...>, TypeList<T, Ts...>>
{
	enum : size_t { key = KeyGen<N, Ns...>::value };
	static T BWN_PRJG_NO_INLINE Func(T first, Ts...args);
};

template<size_t N, size_t...Ns, typename T, typename...Ts>
T BWN_PRJG_NO_INLINE JunkGen<UintList<N, Ns...>, TypeList<T, Ts...>>::Func(T first, Ts...args)
{
	first = InlineFunc< key, key % 3, ComplexityType<50>, void, T, Ts...>::Func(first, args...);

	return first;
}



}

}

#endif