# CMake 最低版本要求
cmake_minimum_required(VERSION 3.14)

# 项目信息
project(CMakeLearningProject 
    VERSION 1.0.0
    DESCRIPTION "一个用于学习CMake的综合项目"
    LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 定义选项
option(BUILD_SHARED_LIBS "构建共享库而非静态库" OFF)
option(BUILD_TESTS "构建测试程序" ON)
option(BUILD_APPS "构建应用程序" ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 打印配置信息
message(STATUS "========================================")
message(STATUS "项目: ${PROJECT_NAME}")
message(STATUS "版本: ${PROJECT_VERSION}")
message(STATUS "C++ 标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "构建类型: ${CMAKE_BUILD_TYPE}")
message(STATUS "共享库: ${BUILD_SHARED_LIBS}")
message(STATUS "构建测试: ${BUILD_TESTS}")
message(STATUS "构建应用: ${BUILD_APPS}")
message(STATUS "========================================")

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 引入外部依赖
include(FetchContent)

if(EXISTS "${PROJECT_SOURCE_DIR}/3rd/json")
    set(FETCHCONTENT_SOURCE_DIR_JSON "${PROJECT_SOURCE_DIR}/3rd/json")
endif()

if(EXISTS "${PROJECT_SOURCE_DIR}/3rd/fmt")
    set(FETCHCONTENT_SOURCE_DIR_FMT "${PROJECT_SOURCE_DIR}/3rd/fmt")
endif()

if(DEFINED FETCHCONTENT_SOURCE_DIR_JSON OR DEFINED FETCHCONTENT_SOURCE_DIR_FMT)
    set(FETCHCONTENT_FULLY_DISCONNECTED ON)
endif()

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)

# 添加子目录
add_subdirectory(src/mathlib)
add_subdirectory(src/stringlib)

if(BUILD_APPS)
    add_subdirectory(apps)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 安装规则
install(DIRECTORY include/ 
    DESTINATION include
    FILES_MATCHING PATTERN "*.h")

# 生成配置文件
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# 添加配置文件到包含路径
include_directories(${PROJECT_BINARY_DIR})
