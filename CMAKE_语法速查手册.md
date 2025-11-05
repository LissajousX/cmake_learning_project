# CMake 语法速查手册

## 目录

1. [基础语法](#基础语法)
2. [变量操作](#变量操作)
3. [常用命令](#常用命令)
4. [控制流程](#控制流程)
5. [目标管理](#目标管理)
6. [文件操作](#文件操作)
7. [实用函数](#实用函数)

---

## 基础语法

### 注释

```cmake
# 这是单行注释

#[[ 
这是多行注释
可以跨越多行
]]
```

### 命令格式

```cmake
# 基本格式: 命令名(参数1 参数2 参数3)
set(MY_VAR "value")

# 参数可以换行
set(MY_VAR 
    "value1"
    "value2"
    "value3"
)

# 命令不区分大小写,但推荐小写
SET(var "value")  # 可以,但不推荐
set(var "value")  # 推荐
```

### 变量引用

```cmake
# 设置变量
set(MY_VAR "Hello")

# 引用变量: ${变量名}
message("${MY_VAR}")  # 输出: Hello

# 嵌套引用
set(VAR_NAME "MY_VAR")
message("${${VAR_NAME}}")  # 输出: Hello
```

### 字符串

```cmake
# 普通字符串
set(STR "Hello World")

# 多行字符串
set(MULTI_LINE "Line 1
Line 2
Line 3")

# 字符串拼接
set(A "Hello")
set(B "World")
set(C "${A} ${B}")  # "Hello World"

# 转义字符
set(PATH "C:\\Program Files\\App")  # Windows路径
```

### 列表

```cmake
# 创建列表(用分号分隔)
set(MY_LIST item1 item2 item3)
# 或
set(MY_LIST "item1;item2;item3")

# 访问列表元素
list(GET MY_LIST 0 FIRST_ITEM)  # 获取第一个元素
list(LENGTH MY_LIST LIST_LEN)   # 获取列表长度

# 添加元素
list(APPEND MY_LIST item4)

# 遍历列表
foreach(item ${MY_LIST})
    message("Item: ${item}")
endforeach()
```

---

## 变量操作

### set() - 设置变量

```cmake
# 普通变量
set(VAR "value")

# 列表变量
set(LIST_VAR item1 item2 item3)

# 缓存变量(可在CMake GUI中修改)
set(CACHE_VAR "default" CACHE STRING "描述信息")

# 环境变量
set(ENV{PATH} "/usr/local/bin:$ENV{PATH}")

# 清除变量
unset(VAR)
```

### 变量作用域

```cmake
# 函数内的变量是局部的
function(my_function)
    set(LOCAL_VAR "local")  # 局部变量
    set(PARENT_VAR "value" PARENT_SCOPE)  # 设置父作用域变量
endfunction()

# 目录作用域
add_subdirectory(subdir)  # subdir中的变量不影响当前目录
```

### 预定义变量

```cmake
# 项目相关
${PROJECT_NAME}           # 项目名称
${PROJECT_VERSION}        # 项目版本
${PROJECT_SOURCE_DIR}     # 项目源码根目录
${PROJECT_BINARY_DIR}     # 项目构建根目录

# 当前目录
${CMAKE_CURRENT_SOURCE_DIR}  # 当前CMakeLists.txt所在目录
${CMAKE_CURRENT_BINARY_DIR}  # 当前构建目录

# 系统信息
${CMAKE_SYSTEM_NAME}      # 系统名称(Linux/Windows/Darwin)
${CMAKE_SYSTEM_VERSION}   # 系统版本
${CMAKE_HOST_SYSTEM_NAME} # 主机系统名称

# 编译器
${CMAKE_CXX_COMPILER}     # C++编译器路径
${CMAKE_CXX_COMPILER_ID}  # 编译器ID(GNU/MSVC/Clang)
${CMAKE_CXX_STANDARD}     # C++标准版本

# 构建类型
${CMAKE_BUILD_TYPE}       # Debug/Release/RelWithDebInfo/MinSizeRel

# 平台判断
${WIN32}                  # Windows平台
${UNIX}                   # Unix-like平台
${APPLE}                  # macOS平台
${MSVC}                   # MSVC编译器
```

---

## 常用命令

### cmake_minimum_required()

```cmake
# 指定所需的最低CMake版本
cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.10...3.20)  # 版本范围
```

### project()

```cmake
# 定义项目
project(MyProject)

# 带版本和语言
project(MyProject 
    VERSION 1.2.3
    DESCRIPTION "项目描述"
    LANGUAGES CXX C
)

# 自动定义的变量:
# ${MyProject_VERSION}
# ${MyProject_VERSION_MAJOR}
# ${MyProject_VERSION_MINOR}
# ${MyProject_VERSION_PATCH}
```

### message()

```cmake
# 输出消息
message("普通消息")
message(STATUS "状态消息")      # 前缀: --
message(WARNING "警告消息")     # 黄色警告
message(AUTHOR_WARNING "作者警告")
message(FATAL_ERROR "致命错误")  # 停止处理
message(SEND_ERROR "错误")      # 继续处理但不生成

# 变量输出
message("变量值: ${MY_VAR}")
```

### option()

```cmake
# 定义布尔选项(可在命令行或GUI中修改)
option(BUILD_TESTS "构建测试" ON)
option(ENABLE_LOGGING "启用日志" OFF)

# 使用
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# 命令行修改: cmake -DBUILD_TESTS=OFF ..
```

### include()

```cmake
# 包含其他CMake文件
include(CMakePrintHelpers)
include(CheckCXXCompilerFlag)

# 包含自定义模块
include(${CMAKE_SOURCE_DIR}/cmake/MyModule.cmake)

# 可选包含
include(OptionalModule OPTIONAL)
```

### add_subdirectory()

```cmake
# 添加子目录(必须包含CMakeLists.txt)
add_subdirectory(src)
add_subdirectory(tests)

# 指定二进制目录
add_subdirectory(external/lib ${CMAKE_BINARY_DIR}/external)
```

---

## 控制流程

### if/elseif/else/endif

```cmake
# 基本条件判断
if(condition)
    # 执行代码
endif()

# if-else
if(BUILD_TESTS)
    message("构建测试")
else()
    message("不构建测试")
endif()

# if-elseif-else
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug模式")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release模式")
else()
    message("其他模式")
endif()
```

### 条件表达式

```cmake
# 变量存在且非空/非FALSE/非OFF/非0
if(MY_VAR)
    message("MY_VAR为真")
endif()

# 变量不存在或为空
if(NOT MY_VAR)
    message("MY_VAR为假")
endif()

# 字符串比较
if(VAR STREQUAL "value")      # 相等
if(VAR MATCHES "regex")       # 正则匹配

# 数值比较
if(NUM EQUAL 10)              # 等于
if(NUM LESS 10)               # 小于
if(NUM GREATER 10)            # 大于
if(NUM LESS_EQUAL 10)         # 小于等于

# 逻辑运算
if(A AND B)                   # 与
if(A OR B)                    # 或
if(NOT A)                     # 非

# 文件/目录判断
if(EXISTS "${FILE_PATH}")     # 文件或目录存在
if(IS_DIRECTORY "${PATH}")    # 是目录
if(IS_ABSOLUTE "${PATH}")     # 是绝对路径

# 目标存在
if(TARGET my_target)          # 目标已定义

# 命令存在
if(COMMAND my_command)        # 命令已定义
```

### foreach循环

```cmake
# 遍历列表
set(ITEMS apple banana orange)
foreach(item ${ITEMS})
    message("Item: ${item}")
endforeach()

# 遍历范围
foreach(i RANGE 5)            # 0到5
    message("i = ${i}")
endforeach()

foreach(i RANGE 1 10 2)       # 1到10,步长2
    message("i = ${i}")
endforeach()

# 遍历列表(带索引)
foreach(item IN LISTS ITEMS)
    message("Item: ${item}")
endforeach()
```

### while循环

```cmake
set(i 0)
while(i LESS 5)
    message("i = ${i}")
    math(EXPR i "${i} + 1")
endwhile()
```

### function和macro

```cmake
# 函数(有独立作用域)
function(my_function arg1 arg2)
    message("arg1: ${arg1}")
    message("arg2: ${arg2}")
    set(RESULT "value" PARENT_SCOPE)  # 设置父作用域变量
endfunction()

# 调用
my_function("hello" "world")

# 宏(无独立作用域,类似文本替换)
macro(my_macro arg)
    message("arg: ${arg}")
endmacro()

my_macro("test")

# 可变参数
function(print_all)
    foreach(arg ${ARGN})  # ARGN包含所有额外参数
        message("${arg}")
    endforeach()
endfunction()

print_all(a b c d)
```

---

## 目标管理

### add_executable()

```cmake
# 创建可执行文件
add_executable(myapp main.cpp)

# 多个源文件
add_executable(myapp 
    main.cpp
    utils.cpp
    helper.cpp
)

# 使用变量
set(SOURCES main.cpp utils.cpp)
add_executable(myapp ${SOURCES})

# Win32应用(Windows)
add_executable(myapp WIN32 main.cpp)
```

### add_library()

```cmake
# 静态库
add_library(mylib STATIC lib.cpp)

# 共享库
add_library(mylib SHARED lib.cpp)

# 模块库(插件)
add_library(mylib MODULE plugin.cpp)

# 根据BUILD_SHARED_LIBS决定
add_library(mylib lib.cpp)

# 接口库(仅头文件)
add_library(mylib INTERFACE)

# 对象库(中间对象文件)
add_library(mylib OBJECT lib.cpp)
```

### target_include_directories()

```cmake
# 为目标添加头文件搜索路径
target_include_directories(mylib PUBLIC include/)
target_include_directories(mylib PRIVATE src/)
target_include_directories(mylib INTERFACE include/)

# 作用域说明:
# PUBLIC    - 当前目标和链接它的目标都使用
# PRIVATE   - 仅当前目标使用
# INTERFACE - 仅链接它的目标使用
```

### target_link_libraries()

```cmake
# 链接库
target_link_libraries(myapp PRIVATE mylib)
target_link_libraries(myapp PUBLIC lib1 lib2)

# 链接系统库
target_link_libraries(myapp PRIVATE pthread m)

# 链接导入的目标
find_package(Boost REQUIRED)
target_link_libraries(myapp PRIVATE Boost::filesystem)
```

### target_compile_definitions()

```cmake
# 添加编译宏定义
target_compile_definitions(myapp PRIVATE DEBUG_MODE)
target_compile_definitions(myapp PRIVATE VERSION="1.0")

# 等价于 -DDEBUG_MODE -DVERSION="1.0"
```

### target_compile_options()

```cmake
# 添加编译选项
target_compile_options(myapp PRIVATE -Wall -Wextra)
target_compile_options(myapp PRIVATE $<$<CONFIG:Debug>:-O0 -g>)

# MSVC
target_compile_options(myapp PRIVATE /W4)
```

### target_sources()

```cmake
# 为目标添加源文件
add_library(mylib)
target_sources(mylib
    PRIVATE
        src/file1.cpp
        src/file2.cpp
    PUBLIC
        include/header.h
)
```

### set_target_properties()

```cmake
# 设置目标属性
set_target_properties(mylib PROPERTIES
    VERSION 1.2.3
    SOVERSION 1
    OUTPUT_NAME "my_library"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)
```

---

## 文件操作

### file()命令

```cmake
# 读取文件
file(READ "file.txt" CONTENT)
file(STRINGS "file.txt" LINES)  # 按行读取

# 写入文件
file(WRITE "output.txt" "内容")
file(APPEND "output.txt" "追加内容")

# 文件操作
file(COPY src/ DESTINATION dst/)
file(REMOVE file1.txt file2.txt)
file(RENAME old.txt new.txt)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# 文件查找(GLOB)
file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")  # 递归查找

# 注意: GLOB不推荐用于源文件,因为新增文件不会自动重新配置

# 下载文件
file(DOWNLOAD 
    "https://example.com/file.zip"
    "${CMAKE_BINARY_DIR}/file.zip"
)
```

### configure_file()

```cmake
# 配置文件(替换变量)
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# config.h.in内容:
# #define VERSION "@PROJECT_VERSION@"
# #define NAME "@PROJECT_NAME@"

# 生成的config.h:
# #define VERSION "1.0.0"
# #define NAME "MyProject"
```

---

## 实用函数

### list()操作

```cmake
set(MY_LIST a b c)

# 长度
list(LENGTH MY_LIST len)

# 获取元素
list(GET MY_LIST 0 first)
list(GET MY_LIST 0 1 first_two)

# 添加元素
list(APPEND MY_LIST d e)
list(PREPEND MY_LIST x y)
list(INSERT MY_LIST 1 new_item)

# 删除元素
list(REMOVE_ITEM MY_LIST b)
list(REMOVE_AT MY_LIST 0)
list(REMOVE_DUPLICATES MY_LIST)

# 查找
list(FIND MY_LIST "b" index)  # 返回索引,未找到返回-1

# 排序和反转
list(SORT MY_LIST)
list(REVERSE MY_LIST)

# 连接
list(JOIN MY_LIST "," result)  # "a,b,c"
```

### string()操作

```cmake
set(STR "Hello World")

# 长度
string(LENGTH "${STR}" len)

# 大小写转换
string(TOUPPER "${STR}" upper)  # "HELLO WORLD"
string(TOLOWER "${STR}" lower)  # "hello world"

# 子串
string(SUBSTRING "${STR}" 0 5 sub)  # "Hello"

# 查找和替换
string(FIND "${STR}" "World" pos)
string(REPLACE "World" "CMake" result "${STR}")

# 正则表达式
string(REGEX MATCH "[0-9]+" numbers "${STR}")
string(REGEX REPLACE "[0-9]+" "X" result "${STR}")

# 去除空白
string(STRIP "  text  " result)  # "text"

# 比较
string(COMPARE EQUAL "${STR1}" "${STR2}" is_equal)
```

### math()运算

```cmake
# 数学运算
math(EXPR result "1 + 2")        # 3
math(EXPR result "10 * 5")       # 50
math(EXPR result "(3 + 4) * 2")  # 14

# 支持的运算符: + - * / % | & ^ ~ << >> 
```

### find_package()

```cmake
# 查找包(Config模式)
find_package(Boost 1.70 REQUIRED COMPONENTS filesystem)

# 查找包(Module模式)
find_package(OpenGL REQUIRED)

# 可选组件
find_package(Qt5 COMPONENTS Core Gui OPTIONAL_COMPONENTS Network)

# 使用找到的包
if(Boost_FOUND)
    target_link_libraries(myapp PRIVATE Boost::filesystem)
endif()
```

### find_program/library/file/path()

```cmake
# 查找程序
find_program(GIT_EXECUTABLE git)

# 查找库
find_library(MATH_LIB m)

# 查找文件
find_file(CONFIG_FILE config.txt PATHS /etc /usr/local/etc)

# 查找路径
find_path(INCLUDE_DIR header.h PATHS /usr/include /usr/local/include)
```

### install()

```cmake
# 安装目标
install(TARGETS myapp mylib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# 安装文件
install(FILES file1.txt file2.txt
    DESTINATION share/myapp
)

# 安装目录
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# 安装脚本
install(SCRIPT deploy.cmake)
```

### enable_testing()和add_test()

```cmake
# 启用测试
enable_testing()

# 添加测试
add_test(NAME test1 COMMAND test_executable)
add_test(NAME test2 COMMAND test_executable arg1 arg2)

# 设置测试属性
set_tests_properties(test1 PROPERTIES
    TIMEOUT 30
    PASS_REGULAR_EXPRESSION "PASSED"
)
```

---

## 生成器表达式

```cmake
# 根据配置类型
$<$<CONFIG:Debug>:-O0 -g>
$<$<CONFIG:Release>:-O3>

# 根据编译器
$<$<CXX_COMPILER_ID:GNU>:-Wall>
$<$<CXX_COMPILER_ID:MSVC>:/W4>

# 根据平台
$<$<PLATFORM_ID:Windows>:WIN32_DEFINE>
$<$<PLATFORM_ID:Linux>:LINUX_DEFINE>

# 目标属性
$<TARGET_FILE:myapp>              # 目标文件完整路径
$<TARGET_FILE_DIR:myapp>          # 目标文件目录
$<TARGET_PROPERTY:myapp,PROP>     # 目标属性

# 逻辑运算
$<AND:cond1,cond2>
$<OR:cond1,cond2>
$<NOT:cond>

# 示例
target_compile_definitions(myapp PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE>
    $<$<CONFIG:Release>:RELEASE_MODE>
)
```

---

## 实用技巧

### 打印所有变量

```cmake
get_cmake_property(_vars VARIABLES)
foreach(_var ${_vars})
    message("${_var} = ${${_var}}")
endforeach()
```

### 检查编译器特性

```cmake
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++17 HAS_CPP17)

if(HAS_CPP17)
    target_compile_options(myapp PRIVATE -std=c++17)
endif()
```

### 平台特定代码

```cmake
if(WIN32)
    target_sources(myapp PRIVATE windows_impl.cpp)
elseif(UNIX)
    target_sources(myapp PRIVATE unix_impl.cpp)
endif()
```

### 调试CMake

```cmake
# 打印变量
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# 打印所有目标
get_property(targets DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
message("Targets: ${targets}")

# 命令行调试
# cmake --trace ..
# cmake --debug-output ..
```

---

## 完整示例

```cmake
cmake_minimum_required(VERSION 3.10)

project(MyApp VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 选项
option(BUILD_TESTS "构建测试" ON)
option(BUILD_SHARED_LIBS "构建共享库" OFF)

# 查找依赖
find_package(Threads REQUIRED)

# 创建库
add_library(mylib
    src/lib.cpp
    src/utils.cpp
)

target_include_directories(mylib
    PUBLIC include
    PRIVATE src
)

target_compile_definitions(mylib
    PRIVATE $<$<CONFIG:Debug>:DEBUG_MODE>
)

# 创建可执行文件
add_executable(myapp src/main.cpp)

target_link_libraries(myapp
    PRIVATE mylib
    PRIVATE Threads::Threads
)

# 测试
if(BUILD_TESTS)
    enable_testing()
    add_executable(test_mylib tests/test.cpp)
    target_link_libraries(test_mylib PRIVATE mylib)
    add_test(NAME test_mylib COMMAND test_mylib)
endif()

# 安装
install(TARGETS myapp mylib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
```

---

## 常见错误和解决方案

### 错误1: 找不到头文件

```cmake
# 错误
add_executable(myapp main.cpp)
# 解决
target_include_directories(myapp PRIVATE include/)
```

### 错误2: 链接错误

```cmake
# 错误
add_executable(myapp main.cpp)
# 解决
target_link_libraries(myapp PRIVATE mylib)
```

### 错误3: 变量未定义

```cmake
# 检查变量是否定义
if(DEFINED MY_VAR)
    message("MY_VAR = ${MY_VAR}")
else()
    message("MY_VAR未定义")
endif()
```

---

## 学习建议

1. **从简单开始** - 先掌握基本命令
2. **多看示例** - 参考本项目的CMakeLists.txt
3. **查阅文档** - 使用 `cmake --help-command <命令名>`
4. **实践为主** - 在项目中尝试不同的写法
5. **理解概念** - 理解目标、属性、作用域等核心概念

---

**快速查询**: 使用 Ctrl+F 搜索你需要的命令或概念!
