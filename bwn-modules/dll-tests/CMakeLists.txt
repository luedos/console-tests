cmake_minimum_required (VERSION 3.10)
project (dll-tests)

set(${PROJECT_NAME}_SOURCE 
	src/dll-main.cpp
)

set(${PROJECT_NAME}_HEADERS
	include/Defines.h
	include/dll-main.h
)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_HEADERS})

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		DLL_TESTS_EXPORT
)

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