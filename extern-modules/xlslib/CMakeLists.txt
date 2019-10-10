cmake_minimum_required (VERSION 3.10)
project (xlslib)

set(${PROJECT_NAME}_SOURCE
    xlslib/assert_assist.cpp
    xlslib/biffsection.h
    xlslib/blank.cpp
    xlslib/blank.h
    xlslib/boolean.cpp
    xlslib/boolean.h
    xlslib/cbridge.cpp
    xlslib/cbridge.h
    xlslib/cell.cpp
    xlslib/cell.h
    xlslib/colinfo.cpp
    xlslib/colinfo.h
    xlslib/colors.cpp
    xlslib/colors.h
    xlslib/common.h
    xlslib/continue.cpp
    xlslib/continue.h
    xlslib/datast.cpp
    xlslib/datast.h
    xlslib/docsumminfo.cpp
    xlslib/docsumminfo.h
    xlslib/err.cpp
    xlslib/err.h
    xlslib/extformat.cpp
    xlslib/extformat.h
    xlslib/font.cpp
    xlslib/font.h
    xlslib/format.cpp
    xlslib/format.h
    xlslib/formtags.h
    xlslib/formula_cell.cpp
    xlslib/formula_cell.h
    xlslib/formula_const.h
    xlslib/formula.cpp
    xlslib/formula_estimate.cpp
    xlslib/formula_estimate.h
    xlslib/formula_expr.cpp
    xlslib/formula_expr.h
    xlslib/formula.h
    xlslib/formula.txt
    xlslib/globalrec.cpp
    xlslib/globalrec.h
    xlslib/HPSF.cpp
    xlslib/HPSF.h
    xlslib/index.cpp
    xlslib/index.h
    xlslib/label.cpp
    xlslib/label.h
    xlslib/merged.cpp
    xlslib/merged.h
    xlslib/note.cpp
    xlslib/note.h
    xlslib/number.cpp
    xlslib/number.h
    xlslib/range.cpp
    xlslib/range.h
    xlslib/recdef.cpp
    xlslib/recdef.h
    xlslib/record.cpp
    xlslib/record.h
    xlslib/rectypes.h
    xlslib/row.cpp
    xlslib/row.h
    xlslib/sheetrec.cpp
    xlslib/sheetrec.h
    xlslib/summinfo.cpp
    xlslib/summinfo.h
    xlslib/tostr.h
    xlslib/unit.cpp
    xlslib/unit.h
    xlslib/workbook.cpp
    xlslib/workbook.h

	common/overnew.cpp
	common/overnew.h
	common/stringtok.h
	common/systype.h
	common/timespan.h
	common/xlconfig.h.in
	common/xls_poppack.h
	common/xls_pshpack1.h
	common/xls_pshpack2.h
	common/xls_pshpack4.h
	common/xlstypes.h
	common/xlsys.h

	oledoc/binfile.cpp
	oledoc/binfile.h
	oledoc/oledoc.cpp
	oledoc/oledoc.h
	oledoc/olefs.cpp
	oledoc/olefs.h
	oledoc/oleprop.cpp
	oledoc/oleprop.h
)

set(${PROJECT_NAME}_HEADERS
	xlslib.h
	xlconfig.h
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE} ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/common
		${PROJECT_SOURCE_DIR}/xlslib
		${PROJECT_SOURCE_DIR}/oledoc
	PUBLIC
		${PROJECT_SOURCE_DIR}
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