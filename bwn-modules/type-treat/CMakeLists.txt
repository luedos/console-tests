cmake_minimum_required (VERSION 3.10)
project (type-treat)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
	INTERFACE
		${PROJECT_SOURCE_DIR}/include
)

set(${PROJECT_NAME}_TEST_SOURCE
	tests/catch.hpp
	tests/UTest.cpp
)

add_executable(${PROJECT_NAME}-tests ${${PROJECT_NAME}_TEST_SOURCE})

target_link_libraries(${PROJECT_NAME}-tests
	PUBLIC
		${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME}-tests
	PROPERTIES
		CXX_STANDARD 14
)

target_compile_options(${PROJECT_NAME}-tests
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/MP /W3 /Zf
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Werror -Wpedantic -pipe>
)

add_test(
	NAME
		${PROJECT_NAME}-tests
	COMMAND
		$<TARGET_FILE:${PROJECT_NAME}-tests>
	WORKING_DIRECTORY
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)