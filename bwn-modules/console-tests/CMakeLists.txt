cmake_minimum_required (VERSION 3.10)
project (console-tests)

set(${PROJECT_NAME}_SOURCE
	src/DistormWrapper.cpp
	src/pch.cpp
	src/pch.h
	src/TestOne.cpp
	src/unit-first.cpp
	src/unit-main.cpp
	src/unit-second.cpp
	src/unit-third.cpp
	src/Utilits.cpp
)

set(${PROJECT_NAME}_HEADERS
	include/DistormWrapper.h
	include/Invoke.h
	include/PRJG.h
	include/PRNG.h
	include/TestOne.h
	include/units-declarations.h
	include/Utilits.h
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_HEADERS})

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

set(${PROJECT_NAME}_LIBS
	${CONAN_LIBS}
	calc-parser
	code-file
	distorm
	lodepng
	lzo
	pe-bliss
	asmjit
#	xlslib
	xlnt
	iterator-wrapper
	nameof
	magic_enum
	numeral-system
	type-treat
)

if (WIN32)
	set(${PROJECT_NAME}_LIBS ${${PROJECT_NAME}_LIBS}
		timer
	)
endif()

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${${PROJECT_NAME}_LIBS}
)

set_target_properties(${PROJECT_NAME} 
	PROPERTIES
		CXX_STANDARD 17
)

target_compile_options(${PROJECT_NAME}
	PUBLIC
		$<$<CXX_COMPILER_ID:MSVC>:
			/MP /Zf 			
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -pipe -Wpedantic -Wextra>
)