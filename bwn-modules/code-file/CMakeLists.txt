cmake_minimum_required (VERSION 3.10)
project (code-file)

set(${PROJECT_NAME}_SOURCE 
	src/CodeFile.cpp
	src/CodeSection.cpp
)

set(${PROJECT_NAME}_HEADERS
	include/CodeFile.h
	include/CodeFileStructs.h
	include/CodeSection.h
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${CONAN_LIBS}
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