cmake_minimum_required (VERSION 3.10)
project (exturn-libraries)

if(WIN32)
	add_subdirectory(timer)
endif()

add_subdirectory(calc-parser)
add_subdirectory(code-file)
add_subdirectory(dll-tests)
add_subdirectory(iterator-wrapper)
add_subdirectory(numeral-system)
add_subdirectory(console-tests)

