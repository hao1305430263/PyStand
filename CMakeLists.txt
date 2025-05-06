cmake_minimum_required(VERSION 3.10)

project (PyStand LANGUAGES CXX RC)

option(PYSTAND_CONSOLE "Build PyStand as a console application." OFF)
set(PYSTAND_EMBEDDED_SCRIPT "embedded_script.py" CACHE STRING "Path to Python script to embed")

# 检查转换工具是否存在
find_program(SCRIPT_CONVERTER "ScriptConverter" PATHS "${CMAKE_SOURCE_DIR}" DOC "Path to ScriptConverter executable")

if(NOT SCRIPT_CONVERTER)
  message(FATAL_ERROR "找不到ScriptConverter工具。请先编译tools/script_converter目录下的转换工具。")
endif()

# 将Python脚本转换为头文件
set(EMBEDDED_SCRIPT_HEADER "${CMAKE_BINARY_DIR}/generated/embedded_script.h")

# 确保目标目录存在
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/generated")

# 添加命令将Python脚本转换为头文件
add_custom_command(
  OUTPUT "${EMBEDDED_SCRIPT_HEADER}"
  COMMAND ${SCRIPT_CONVERTER}
          "${CMAKE_SOURCE_DIR}/${PYSTAND_EMBEDDED_SCRIPT}" 
          "${EMBEDDED_SCRIPT_HEADER}"
  DEPENDS "${CMAKE_SOURCE_DIR}/${PYSTAND_EMBEDDED_SCRIPT}"
  COMMENT "生成嵌入式Python脚本头文件"
)

# 添加自定义目标以确保头文件在构建前生成
add_custom_target(generate_embedded_script DEPENDS "${EMBEDDED_SCRIPT_HEADER}")

# 添加包含目录
include_directories(${CMAKE_BINARY_DIR}/generated)

# sources
set(sources
	PyStand.cpp
	resource.rc
	)

# 添加编译前生成的头文件
list(APPEND sources "${EMBEDDED_SCRIPT_HEADER}")

if (PYSTAND_CONSOLE)
	add_executable(PyStand ${sources})
	target_compile_definitions(PyStand PRIVATE PYSTAND_CONSOLE)
else()
	add_executable(PyStand WIN32 ${sources})
endif()

# 添加依赖，确保头文件先生成
add_dependencies(PyStand generate_embedded_script)

# static link
if (CMAKE_GENERATOR MATCHES "Visual Studio")
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	target_compile_options(PyStand
		PUBLIC
		$<$<CONFIG:Debug>:/MTd>
		$<$<CONFIG:Release>:/MT>
		$<$<CONFIG:MinSizeRel>:/MT>
		)
	target_link_options(PyStand PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
else()
	# for mingw
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE} -s")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -s")
	target_link_libraries(PyStand 
		-static
		shlwapi
		winmm
		)
endif()



