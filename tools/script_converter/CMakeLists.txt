cmake_minimum_required(VERSION 3.10)
project(ScriptConverter)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(ScriptConverter
  ScriptConverter.cpp
)

# 如果是MSVC编译器，使用静态链接
if(MSVC)
  # 使用多线程静态运行库
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# 如果是MinGW，使用静态链接
if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

# 安装规则
install(TARGETS ScriptConverter 
        RUNTIME DESTINATION bin) 