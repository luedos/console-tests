cmake_minimum_required (VERSION 3.10)
project (distorm)

set(${PROJECT_NAME}_SOURCE 
	src/config.h
	src/decoder.h		src/decoder.c
						src/distorm.c
	src/instructions.h	src/instructions.c
	src/insts.h			src/insts.c
						src/mnemonics.c
	src/operands.h		src/operands.c
	src/prefix.h		src/prefix.c
	src/textdefs.h		src/textdefs.c
	src/wstring.h		src/wstring.c
	src/x86defs.h
)

set(${PROJECT_NAME}_HEADERS
	include/distorm.h
	include/mnemonics.h
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
			/MP /Zf 			
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -pipe>
)