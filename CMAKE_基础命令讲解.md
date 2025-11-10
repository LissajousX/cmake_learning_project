# CMake 基础命令讲解

## 目录

1. [cmake_minimum_required](#cmake_minimum_required)
2. [project](#project)
3. [add_executable](#add_executable)
4. [add_library](#add_library)
5. [target_link_libraries](#target_link_libraries)
6. [target_include_directories](#target_include_directories)
7. [option](#option)
8. [set](#set)
9. [include](#include)

---

## cmake_minimum_required

```cmake
cmake_minimum_required(VERSION 3.14)
```

- **命令名**: `cmake_minimum_required`
- **关键字**: `VERSION` 指定所需的最低 CMake 版本
- **作用**: 确保工程在过低版本的 CMake 上会直接提示不兼容，避免后续构建失败。

---

## project

```cmake
project(MyProject VERSION 1.2.3 DESCRIPTION "项目描述" LANGUAGES CXX)
```

- **命令名**: `project`
- **位置参数**: 项目名称 `MyProject`
- **关键字参数**:
  - `VERSION`：设置项目版本，并自动生成 `PROJECT_VERSION_MAJOR` 等变量
  - `DESCRIPTION`：项目描述信息
  - `LANGUAGES`：指定使用的编程语言，如 `C`、`CXX`
- **作用**: 初始化项目上下文，定义一系列项目相关变量供后续命令使用。

---

## add_executable

```cmake
add_executable(calculator_app calculator_app.cpp)
```

- **命令名**: `add_executable`
- **位置参数**:
  - 目标名称 `calculator_app`
  - 源文件列表 `calculator_app.cpp`
- **作用**: 定义一个可执行目标，后续会编译并生成对应的二进制程序。

---

## add_library

```cmake
add_library(mathlib STATIC calculator.cpp statistics.cpp)
```

- **命令名**: `add_library`
- **位置参数**:
  - 目标名称 `mathlib`
  - 源文件列表
- **可选关键字**:
  - `STATIC`：生成静态库（默认值受 `BUILD_SHARED_LIBS` 影响）
  - `SHARED`：生成共享库
  - `INTERFACE`：仅导出头文件，不编译源文件
- **作用**: 定义静态/共享/接口库，为其他目标提供可链接的模块。

---

## target_link_libraries

```cmake
target_link_libraries(calculator_app PRIVATE mathlib)
```

- **命令名**: `target_link_libraries`
- **位置参数**: 需要链接库的目标 `calculator_app`
- **关键字**:
  - `PRIVATE`：只对当前目标生效
  - `PUBLIC`：当前目标和依赖它的目标都会链接
  - `INTERFACE`：仅由依赖者链接，当前目标不使用
- **后续参数**: 需要链接的库或目标名，例如 `mathlib`
- **作用**: 指定链接依赖，确保在构建阶段找到所需库。

---

## target_include_directories

```cmake
target_include_directories(mathlib PUBLIC include/)
```

- **命令名**: `target_include_directories`
- **位置参数**: 目标名称 `mathlib`
- **关键字**: 同样使用 `PUBLIC`、`PRIVATE`、`INTERFACE` 控制头文件路径传播范围
- **后续参数**: 需要添加的头文件目录
- **作用**: 把头文件搜索路径附加到目标及其依赖者的编译选项中。

---

## option

```cmake
option(BUILD_TESTS "构建测试程序" ON)
```

- **命令名**: `option`
- **位置参数**:
  - 变量名 `BUILD_TESTS`
  - 描述字符串
  - 默认值 `ON` 或 `OFF`
- **作用**: 提供布尔型开关，用户可通过 `-D` 覆盖，用于控制条件编译和子目录启用。

---

## set

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
```

- **命令名**: `set`
- **位置参数**:
  - 变量名，例如 `CMAKE_RUNTIME_OUTPUT_DIRECTORY`
  - 变量值，可是字符串、列表或变量
- **可选关键字**:
  - `CACHE`：写入 CMake 缓存，供用户配置
  - `PARENT_SCOPE`：将值传回父作用域
- **作用**: 设置普通变量或缓存变量，控制编译参数、输出目录等。

---

## include

```cmake
include(FetchContent)
```

- **命令名**: `include`
- **位置参数**: 模块名 `FetchContent`
- **作用**: 加载指定的 CMake 模块文件，从而获得额外的函数、宏或配置逻辑。

---

> 更多基础语法可参考 `CMAKE_语法速查手册.md`。
