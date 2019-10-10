cmake_minimum_required (VERSION 3.10)
project (pe-bliss)

set(${PROJECT_NAME}_SOURCE 
	src/entropy.cpp
	src/file_version_info.cpp
	src/message_table.cpp
	src/pe_base.cpp
	src/pe_bound_import.cpp
	src/pe_checksum.cpp
	src/pe_debug.cpp
	src/pe_directory.cpp
	src/pe_dotnet.cpp
	src/pe_exception.cpp
	src/pe_exception_directory.cpp
	src/pe_exports.cpp
	src/pe_factory.cpp
	src/pe_imports.cpp
	src/pe_load_config.cpp
	src/pe_properties.cpp
	src/pe_properties_generic.cpp
	src/pe_rebuilder.cpp
	src/pe_relocations.cpp
	src/pe_resources.cpp
	src/pe_resource_manager.cpp
	src/pe_resource_viewer.cpp
	src/pe_rich_data.cpp
	src/pe_section.cpp
	src/pe_tls.cpp
	src/resource_bitmap_reader.cpp
	src/resource_bitmap_writer.cpp
	src/resource_cursor_icon_reader.cpp
	src/resource_cursor_icon_writer.cpp
	src/resource_data_info.cpp
	src/resource_message_list_reader.cpp
	src/resource_string_table_reader.cpp
	src/resource_version_info_reader.cpp
	src/resource_version_info_writer.cpp
	src/utils.cpp
	src/version_info_editor.cpp
	src/version_info_viewer.cpp
)

set(${PROJECT_NAME}_HEADERS
	include/entropy.h
	include/file_version_info.h
	include/message_table.h
	include/pe_base.h
	include/pe_bliss.h
	include/pe_bliss_resources.h
	include/pe_bound_import.h
	include/pe_checksum.h
	include/pe_debug.h
	include/pe_directory.h
	include/pe_dotnet.h
	include/pe_exception.h
	include/pe_exception_directory.h
	include/pe_exports.h
	include/pe_factory.h
	include/pe_imports.h
	include/pe_load_config.h
	include/pe_properties.h
	include/pe_properties_generic.h
	include/pe_rebuilder.h
	include/pe_relocations.h
	include/pe_resources.h
	include/pe_resource_manager.h
	include/pe_resource_viewer.h
	include/pe_rich_data.h
	include/pe_section.h
	include/pe_structures.h
	include/pe_tls.h
	include/resource_bitmap_reader.h
	include/resource_bitmap_writer.h
	include/resource_cursor_icon_reader.h
	include/resource_cursor_icon_writer.h
	include/resource_data_info.h
	include/resource_internal.h
	include/resource_message_list_reader.h
	include/resource_string_table_reader.h
	include/resource_version_info_reader.h
	include/resource_version_info_writer.h
	include/stdint_defs.h
	include/utils.h
	include/version_info_editor.h
	include/version_info_types.h
	include/version_info_viewer.h
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
			-Wall -pipe>
)