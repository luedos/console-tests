cmake_minimum_required (VERSION 3.10)
project (calc-parser)

set(${PROJECT_NAME}_SOURCE 
	src/Exceptions.cpp
	src/Node.cpp
	src/NodeFunction.cpp
	src/NodeSequence.cpp
	src/NodeVariable.cpp
	src/Parser.cpp
	src/Repository.cpp
	src/Token.cpp
	src/Utilits.cpp
	src/Value.cpp
	src/Variable.cpp
)

set(${PROJECT_NAME}_HEADERS
	include/Exceptions.h
	include/Node.h
	include/NodeBinaryOp.h
	include/NodeFunction.h
	include/NodeSequence.h
	include/NodeTernaryOp.h
	include/NodeUnaryOp.h
	include/NodeVariable.h
	include/Parser.h
	include/Repository.h
	include/Token.h
	include/Utilits.h
	include/Value.h
	include/Variable.h
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
)

set_target_properties(${PROJECT_NAME} 
	PROPERTIES
		CXX_STANDARD 14
)

target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/MP /W3 /Zf 			
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Werror -Wpedantic -pedantic-errors -pipe>
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