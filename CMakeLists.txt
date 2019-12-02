cmake_minimum_required (VERSION 3.10)
project (console-tests)

if (ENABLE_TESTING)
    enable_testing()
endif()

set(my_conan_settings 
	SETTINGS build_type=${CMAKE_BUILD_TYPE}
	SETTINGS os=${CMAKE_SYSTEM_NAME}
)
if (CONAN_FORCE_ARCH)
	set(my_conan_settings ${my_conan_settings}
			SETTINGS arch=${CONAN_FORCE_ARCH}
			SETTINGS build_arch=${CONAN_FORCE_ARCH})
endif()

message(${my_conan_settings})

if(MSVC)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(my_conan_settings ${my_conan_settings}
            SETTINGS compiler.runtime=MTd
        )
    else()
        set(my_conan_settings ${my_conan_settings}
            SETTINGS compiler.runtime=MT
        )
    endif()

endif()

include(cmake/conan.cmake)
include(cmake/cotire.cmake)

conan_cmake_run(CONANFILE conan/conanfile.txt 
	${my_conan_settings}
	BASIC_SETUP CMAKE_TARGETS BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(extern-modules)
add_subdirectory(bwn-modules)