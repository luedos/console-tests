cmake_minimum_required (VERSION 3.10)
project (lzo)

set(${PROJECT_NAME}_SOURCE 
	src/compr1b.h
	src/compr1c.h
	src/config1.h
	src/config1a.h
	src/config1b.h
	src/config1c.h
	src/config1f.h
	src/config1x.h
	src/config1y.h
	src/config1z.h
	src/config2a.h
	src/lzo1.c
	src/lzo1a.c
	src/lzo1a_99.c
	src/lzo1a_cm.ch
	src/lzo1a_cr.ch
	src/lzo1a_de.h
	src/lzo1b_1.c
	src/lzo1b_2.c
	src/lzo1b_3.c
	src/lzo1b_4.c
	src/lzo1b_5.c
	src/lzo1b_6.c
	src/lzo1b_7.c
	src/lzo1b_8.c
	src/lzo1b_9.c
	src/lzo1b_99.c
	src/lzo1b_9x.c
	src/lzo1b_c.ch
	src/lzo1b_cc.c
	src/lzo1b_cc.h
	src/lzo1b_cm.ch
	src/lzo1b_cr.ch
	src/lzo1b_d.ch
	src/lzo1b_d1.c
	src/lzo1b_d2.c
	src/lzo1b_de.h
	src/lzo1b_r.ch
	src/lzo1b_rr.c
	src/lzo1b_sm.ch
	src/lzo1b_tm.ch
	src/lzo1b_xx.c
	src/lzo1c_1.c
	src/lzo1c_2.c
	src/lzo1c_3.c
	src/lzo1c_4.c
	src/lzo1c_5.c
	src/lzo1c_6.c
	src/lzo1c_7.c
	src/lzo1c_8.c
	src/lzo1c_9.c
	src/lzo1c_99.c
	src/lzo1c_9x.c
	src/lzo1c_cc.c
	src/lzo1c_cc.h
	src/lzo1c_d1.c
	src/lzo1c_d2.c
	src/lzo1c_rr.c
	src/lzo1c_xx.c
	src/lzo1f_1.c
	src/lzo1f_9x.c
	src/lzo1f_d.ch
	src/lzo1f_d1.c
	src/lzo1f_d2.c
	src/lzo1x_1.c
	src/lzo1x_1k.c
	src/lzo1x_1l.c
	src/lzo1x_1o.c
	src/lzo1x_9x.c
	src/lzo1x_c.ch
	src/lzo1x_d.ch
	src/lzo1x_d1.c
	src/lzo1x_d2.c
	src/lzo1x_d3.c
	src/lzo1x_o.c
	src/lzo1x_oo.ch
	src/lzo1y_1.c
	src/lzo1y_9x.c
	src/lzo1y_d1.c
	src/lzo1y_d2.c
	src/lzo1y_d3.c
	src/lzo1y_o.c
	src/lzo1z_9x.c
	src/lzo1z_d1.c
	src/lzo1z_d2.c
	src/lzo1z_d3.c
	src/lzo1_99.c
	src/lzo1_cm.ch
	src/lzo1_d.ch
	src/lzo2a_9x.c
	src/lzo2a_d.ch
	src/lzo2a_d1.c
	src/lzo2a_d2.c
	src/lzo_conf.h
	src/lzo_crc.c
	src/lzo_dict.h
	src/lzo_dll.ch
	src/lzo_func.h
	src/lzo_init.c
	src/lzo_mchw.ch
	src/lzo_ptr.c
	src/lzo_ptr.h
	src/lzo_str.c
	src/lzo_supp.h
	src/lzo_swd.ch
	src/lzo_util.c
	src/stats1a.h
	src/stats1b.h
	src/stats1c.h
)


set(${PROJECT_NAME}_HEADERS
	include/lzo1.h
	include/lzo1a.h
	include/lzo1b.h
	include/lzo1c.h
	include/lzo1f.h
	include/lzo1x.h
	include/lzo1y.h
	include/lzo1z.h
	include/lzo2a.h
	include/lzoconf.h
	include/lzodefs.h
	include/lzoutil.h
	include/lzo_asm.h
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