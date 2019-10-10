#pragma once

#if defined(_MSC_VER)
//  Microsoft
	#ifdef DLL_TESTS_EXPORT
	    #define DLL_TESTS_API __declspec(dllexport)
	#else
	    #define DLL_TESTS_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
//  GCC
	#ifdef DLL_TESTS_EXPORT
		#define DLL_TESTS_API __attribute__((visibility("default")))
	#else
		#define DLL_TESTS_API
	#endif
#else
//  do nothing and hope for the best?
    #define DLL_TESTS_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
