# CMake 完整学习教程

## 目录

1. [CMake 简介](#cmake-简介)
2. [项目结构分析](#项目结构分析)
3. [根 CMakeLists.txt 详解](#根-cmakeliststxt-详解)
4. [库的构建](#库的构建)
5. [可执行文件的构建](#可执行文件的构建)
6. [测试集成](#测试集成)
7. [高级特性](#高级特性)
8. [实战练习](#实战练习)

---

## CMake 简介

### 什么是 CMake?

CMake 是一个跨平台的构建系统生成器。它不直接构建项目,而是生成特定平台的构建文件(如 Makefile、Visual Studio 项目文件等)。

### 为什么使用 CMake?

- **跨平台**: 一套配置文件可在 Windows、Linux、macOS 上使用
- **灵活**: 支持复杂的项目结构和依赖关系
- **现代化**: 支持现代 C++ 标准和最佳实践
- **生态系统**: 大量第三方库支持 CMake

### CMake 工作流程

```
源代码 + CMakeLists.txt → CMake → 构建文件 → 编译器 → 可执行文件/库
```

---

## 项目结构分析

本项目采用了标准的 CMake 项目布局:

```
cmake_learning_project/
├── CMakeLists.txt              # 根配置文件(入口点)
├── config.h.in                 # 配置模板
├── include/                    # 公共头文件
│   ├── mathlib/
│   └── stringlib/
├── src/                        # 源代码实现
│   ├── mathlib/
│   │   └── CMakeLists.txt     # 子项目配置
│   └── stringlib/
│       └── CMakeLists.txt
├── apps/                       # 应用程序
│   └── CMakeLists.txt
└── tests/                      # 测试代码
    └── CMakeLists.txt
```

### 设计原则

1. **头文件与实现分离**: `include/` 存放接口,`src/` 存放实现
2. **模块化**: 每个库有独立的 CMakeLists.txt
3. **清晰的依赖关系**: apps 依赖库,tests 测试库

---

## 根 CMakeLists.txt 详解

### 1. 版本要求和项目定义

```cmake
cmake_minimum_required(VERSION 3.10)
```

**作用**: 指定所需的最低 CMake 版本,确保使用的功能可用。

```cmake
project(CMakeLearningProject 
    VERSION 1.0.0
    DESCRIPTION "一个用于学习CMake的综合项目"
    LANGUAGES CXX)
```

**关键点**:
- `project()` 必须在 `cmake_minimum_required()` 之后
- `VERSION` 会自动定义 `PROJECT_VERSION` 等变量
- `LANGUAGES` 指定使用的编程语言(CXX = C++)

### 2. C++ 标准设置

```cmake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

**解释**:
- `CMAKE_CXX_STANDARD`: 设置 C++ 标准版本
- `CMAKE_CXX_STANDARD_REQUIRED`: 如果编译器不支持则报错
- `CMAKE_CXX_EXTENSIONS`: 禁用编译器特定扩展,保证可移植性

### 3. 编译选项

```cmake
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
```

**作用**: 根据编译器类型添加警告选项
- MSVC: `/W4` (Windows Visual Studio)
- GCC/Clang: `-Wall -Wextra -pedantic`

### 4. 构建选项

```cmake
option(BUILD_SHARED_LIBS "构建共享库而非静态库" OFF)
option(BUILD_TESTS "构建测试程序" ON)
option(BUILD_APPS "构建应用程序" ON)
```

**用法**: 用户可在配置时修改
```bash
cmake -DBUILD_SHARED_LIBS=ON ..
cmake -DBUILD_TESTS=OFF ..
```

### 5. 输出目录设置

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
```

**目的**: 统一管理输出文件位置
- `RUNTIME`: 可执行文件(.exe)
- `LIBRARY`: 共享库(.so, .dll)
- `ARCHIVE`: 静态库(.a, .lib)

### 6. 包含目录

```cmake
include_directories(${PROJECT_SOURCE_DIR}/include)
```

**注意**: 现代 CMake 推荐使用 `target_include_directories()`,但这里为了简单使用全局设置。

### 7. 添加子目录

```cmake
add_subdirectory(src/mathlib)
add_subdirectory(src/stringlib)

if(BUILD_APPS)
    add_subdirectory(apps)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
```

**流程**:
1. 先构建库(mathlib, stringlib)
2. 根据选项决定是否构建 apps 和 tests
3. `enable_testing()` 启用 CTest 支持

### 8. 配置文件生成

```cmake
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
```

**作用**: 将 `config.h.in` 中的 CMake 变量替换为实际值

**config.h.in 示例**:
```cpp
#define PROJECT_VERSION "@PROJECT_VERSION@"
```

**生成的 config.h**:
```cpp
#define PROJECT_VERSION "1.0.0"
```

---

## 库的构建

### MathLib 示例 (src/mathlib/CMakeLists.txt)

```cmake
# 1. 定义源文件
set(MATHLIB_SOURCES
    calculator.cpp
    statistics.cpp
)

# 2. 创建库目标
add_library(mathlib ${MATHLIB_SOURCES})

# 3. 设置包含目录
target_include_directories(mathlib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 4. 设置库属性
set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "math"
)

# 5. 安装规则
install(TARGETS mathlib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
```

### 关键概念解析

#### add_library()

```cmake
add_library(target_name [STATIC | SHARED | MODULE] sources...)
```

- 不指定类型时,由 `BUILD_SHARED_LIBS` 决定
- `STATIC`: 静态库(.a, .lib)
- `SHARED`: 共享库(.so, .dll)

#### target_include_directories()

```cmake
target_include_directories(target <INTERFACE|PUBLIC|PRIVATE> dirs...)
```

**作用域**:
- `PRIVATE`: 仅当前目标使用
- `PUBLIC`: 当前目标和链接它的目标都使用
- `INTERFACE`: 仅链接它的目标使用

**示例**:
```cmake
# mathlib 和链接 mathlib 的目标都能访问 include/
target_include_directories(mathlib PUBLIC ${PROJECT_SOURCE_DIR}/include)
```

#### set_target_properties()

设置目标的各种属性:
- `VERSION`: 库的完整版本号
- `SOVERSION`: 库的主版本号(用于符号链接)
- `OUTPUT_NAME`: 输出文件名(不含前缀和后缀)

**效果**:
```
libmath.so -> libmath.so.1 -> libmath.so.1.0.0
```

---

## 可执行文件的构建

### 应用程序示例 (apps/CMakeLists.txt)

```cmake
# 1. 创建可执行文件
add_executable(calculator_app calculator_app.cpp)

# 2. 链接库
target_link_libraries(calculator_app PRIVATE mathlib stringlib)

# 3. 安装
install(TARGETS calculator_app
    RUNTIME DESTINATION bin
)
```

### add_executable()

```cmake
add_executable(target_name sources...)
```

创建可执行文件目标。

### target_link_libraries()

```cmake
target_link_libraries(target <PRIVATE|PUBLIC|INTERFACE> libs...)
```

**链接作用域**:
- `PRIVATE`: 仅当前目标需要
- `PUBLIC`: 当前目标和依赖它的目标都需要
- `INTERFACE`: 仅依赖它的目标需要

**示例**:
```cmake
# calculator_app 需要 mathlib 和 stringlib
target_link_libraries(calculator_app PRIVATE mathlib stringlib)
```

---

## 测试集成

### 测试配置 (tests/CMakeLists.txt)

```cmake
# 1. 创建测试可执行文件
add_executable(test_calculator test_calculator.cpp)

# 2. 链接被测试的库
target_link_libraries(test_calculator PRIVATE mathlib)

# 3. 注册测试
add_test(NAME CalculatorTest COMMAND test_calculator)
```

### CTest 使用

#### 在根 CMakeLists.txt 中启用

```cmake
enable_testing()
```

#### 运行测试

```bash
# 在 build 目录中
ctest

# 详细输出
ctest -V

# 运行特定测试
ctest -R Calculator
```

### 高级测试配置

```cmake
# 设置测试属性
set_tests_properties(CalculatorTest PROPERTIES
    TIMEOUT 10
    PASS_REGULAR_EXPRESSION "所有.*测试通过"
)

# 设置环境变量
set_tests_properties(CalculatorTest PROPERTIES
    ENVIRONMENT "TEST_DATA_DIR=/path/to/data"
)
```

---

## 高级特性

### 1. 查找依赖包

```cmake
# 查找必需的包
find_package(Boost 1.70 REQUIRED COMPONENTS filesystem)

# 链接找到的包
target_link_libraries(myapp PRIVATE Boost::filesystem)
```

### 2. 生成器表达式

```cmake
# 根据构建类型添加不同的编译选项
target_compile_options(mylib PRIVATE
    $<$<CONFIG:Debug>:-O0 -g>
    $<$<CONFIG:Release>:-O3>
)

# 根据编译器添加选项
target_compile_options(mylib PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
```

### 3. 自定义命令

```cmake
# 在构建时运行自定义命令
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated.cpp
    COMMAND python ${CMAKE_SOURCE_DIR}/generate.py
    DEPENDS ${CMAKE_SOURCE_DIR}/template.txt
    COMMENT "生成源文件..."
)
```

### 4. 导出和安装

```cmake
# 导出目标供其他项目使用
install(TARGETS mathlib
    EXPORT MathLibTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

# 安装导出文件
install(EXPORT MathLibTargets
    FILE MathLibTargets.cmake
    NAMESPACE MathLib::
    DESTINATION lib/cmake/MathLib
)

# 生成配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    MathLibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MathLibConfig.cmake
    INSTALL_DESTINATION lib/cmake/MathLib
)
```

### 5. 条件编译

```cmake
# 检测平台
if(WIN32)
    target_compile_definitions(myapp PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(myapp PRIVATE PLATFORM_UNIX)
endif()

# 检测功能
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
    #include <filesystem>
    int main() { std::filesystem::path p; return 0; }
" HAS_FILESYSTEM)

if(HAS_FILESYSTEM)
    target_compile_definitions(myapp PRIVATE HAS_FILESYSTEM)
endif()
```

---

## 实战练习

### 练习 1: 构建项目

```bash
# 1. 进入项目目录
cd cmake_learning_project

# 2. 创建构建目录
mkdir build
cd build

# 3. 配置项目(生成构建文件)
cmake ..

# 4. 编译项目
cmake --build .

# 5. 运行测试
ctest

# 6. 运行程序
./bin/simple_demo
./bin/calculator_app
```

### 练习 2: 修改构建选项

```bash
# 构建共享库
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .

# 检查生成的库类型
ls -l lib/

# Release 模式构建
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### 练习 3: 添加新功能

**任务**: 在 MathLib 中添加一个新的几何计算类

1. **创建头文件** `include/mathlib/geometry.h`:
```cpp
#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace MathLib {
class Geometry {
public:
    static double circleArea(double radius);
    static double rectangleArea(double width, double height);
};
}

#endif
```

2. **创建实现文件** `src/mathlib/geometry.cpp`:
```cpp
#include "mathlib/geometry.h"
#include <cmath>

namespace MathLib {
double Geometry::circleArea(double radius) {
    return M_PI * radius * radius;
}

double Geometry::rectangleArea(double width, double height) {
    return width * height;
}
}
```

3. **修改** `src/mathlib/CMakeLists.txt`:
```cmake
set(MATHLIB_SOURCES
    calculator.cpp
    statistics.cpp
    geometry.cpp  # 添加新文件
)
```

4. **重新构建**:
```bash
cmake --build .
```

### 练习 4: 添加外部依赖

**任务**: 使用 JSON 库(如 nlohmann/json)

1. **下载库** (使用 FetchContent):
```cmake
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)
```

2. **链接库**:
```cmake
target_link_libraries(myapp PRIVATE nlohmann_json::nlohmann_json)
```

---

## CMake 最佳实践

### 1. 使用现代 CMake (3.10+)

**推荐**:
```cmake
target_include_directories(mylib PUBLIC include/)
target_link_libraries(myapp PRIVATE mylib)
```

**避免**:
```cmake
include_directories(include/)  # 全局污染
link_libraries(mylib)          # 全局污染
```

### 2. 明确作用域

始终使用 `PUBLIC`、`PRIVATE`、`INTERFACE` 明确依赖关系。

### 3. 使用目标而非变量

**推荐**:
```cmake
target_link_libraries(myapp PRIVATE Boost::filesystem)
```

**避免**:
```cmake
target_link_libraries(myapp PRIVATE ${Boost_LIBRARIES})
```

### 4. 避免全局命令

- 使用 `target_compile_definitions()` 而非 `add_definitions()`
- 使用 `target_compile_options()` 而非 `add_compile_options()`

### 5. 生成器表达式

用于处理配置相关的差异:
```cmake
target_compile_definitions(myapp PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE>
)
```

### 6. Out-of-Source 构建

**始终在单独的 build 目录中构建**:
```bash
mkdir build && cd build
cmake ..
```

### 7. 版本控制

在 `.gitignore` 中忽略 `build/` 目录。

---

## 常见问题

### Q1: 找不到头文件

**问题**: `fatal error: mathlib/calculator.h: No such file or directory`

**解决**:
```cmake
target_include_directories(mylib PUBLIC ${PROJECT_SOURCE_DIR}/include)
```

### Q2: 链接错误

**问题**: `undefined reference to 'MathLib::Calculator::add(double, double)'`

**解决**:
```cmake
target_link_libraries(myapp PRIVATE mathlib)
```

### Q3: 库找不到

**问题**: `CMake Error: Could not find a package configuration file provided by "XXX"`

**解决**:
```cmake
# 指定搜索路径
set(CMAKE_PREFIX_PATH "/path/to/package")
find_package(XXX REQUIRED)
```

### Q4: 重新配置

**问题**: 修改 CMakeLists.txt 后需要重新配置

**解决**:
```bash
cd build
cmake ..
cmake --build .
```

或者删除 build 目录重新开始:
```bash
rm -rf build
mkdir build && cd build
cmake ..
```

---

## 总结

### CMake 核心概念

1. **目标 (Targets)**: 库和可执行文件
2. **属性 (Properties)**: 目标的配置(编译选项、链接库等)
3. **依赖 (Dependencies)**: 目标之间的关系
4. **生成器 (Generators)**: 生成特定平台的构建文件

### 学习路径

1. ✅ 理解基本概念和工作流程
2. ✅ 掌握简单项目的配置
3. ✅ 学习库的创建和链接
4. ✅ 掌握测试集成
5. ⬜ 学习包管理和依赖处理
6. ⬜ 掌握跨平台构建技巧
7. ⬜ 学习高级特性(导出、安装、打包)

### 进阶资源

- [CMake 官方文档](https://cmake.org/documentation/)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Effective CMake](https://www.youtube.com/watch?v=bsXLMQ6WgIk)
- [CMake Cookbook](https://github.com/dev-cafe/cmake-cookbook)

---

## 附录: 常用 CMake 命令速查

### 项目配置

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)
```

### 变量操作

```cmake
set(VAR value)                    # 设置变量
set(VAR value CACHE STRING "")    # 缓存变量
option(VAR "description" ON)      # 布尔选项
```

### 目标创建

```cmake
add_executable(name sources...)
add_library(name [STATIC|SHARED] sources...)
```

### 目标配置

```cmake
target_include_directories(target <scope> dirs...)
target_link_libraries(target <scope> libs...)
target_compile_definitions(target <scope> defs...)
target_compile_options(target <scope> opts...)
```

### 查找和包含

```cmake
find_package(Package REQUIRED)
include(Module)
add_subdirectory(dir)
```

### 安装

```cmake
install(TARGETS target DESTINATION dir)
install(FILES files... DESTINATION dir)
install(DIRECTORY dirs... DESTINATION dir)
```

### 测试

```cmake
enable_testing()
add_test(NAME name COMMAND cmd)
```

### 消息输出

```cmake
message(STATUS "message")      # 普通消息
message(WARNING "message")     # 警告
message(FATAL_ERROR "message") # 错误并停止
```

---

**祝你学习愉快!** 🚀
