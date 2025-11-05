# CMake 快速入门指南

## 5分钟快速开始

### 第一步:构建项目

```bash
cd cmake_learning_project
mkdir build && cd build
cmake ..
cmake --build .
```

### 第二步:运行测试

```bash
ctest
```

预期输出:
```
Test project /path/to/build
    Start 1: CalculatorTest
1/3 Test #1: CalculatorTest ...................   Passed    0.01 sec
    Start 2: StatisticsTest
2/3 Test #2: StatisticsTest ...................   Passed    0.01 sec
    Start 3: StringUtilsTest
3/3 Test #3: StringUtilsTest ..................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3
```

### 第三步:运行应用程序

```bash
# 简单演示
./bin/simple_demo

# 交互式计算器
./bin/calculator_app
```

## 项目文件说明

### 核心文件

- **CMakeLists.txt**: 项目的主配置文件
- **config.h.in**: 配置头文件模板
- **README.md**: 项目说明文档
- **CMAKE_TUTORIAL.md**: 详细的CMake学习教程

### 源代码

- **include/**: 所有头文件(.h)
- **src/**: 库的实现文件(.cpp)
- **apps/**: 可执行程序源码
- **tests/**: 测试程序源码

### 构建输出

构建后会生成 `build/` 目录,包含:

- **build/bin/**: 可执行文件
- **build/lib/**: 库文件
- **build/config.h**: 生成的配置文件

## 常用命令

### 配置选项

```bash
# 构建共享库
cmake -DBUILD_SHARED_LIBS=ON ..

# Release 模式
cmake -DCMAKE_BUILD_TYPE=Release ..

# 禁用测试
cmake -DBUILD_TESTS=OFF ..

# 组合使用
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON ..
```

### 清理和重建

```bash
# 清理构建文件
cd build
make clean  # 或 cmake --build . --target clean

# 完全重新开始
cd ..
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
```

### 安装

```bash
# 安装到默认位置(/usr/local)
sudo cmake --install .

# 安装到自定义位置
cmake -DCMAKE_INSTALL_PREFIX=$HOME/mylibs ..
cmake --build .
cmake --install .
```

## 学习路径

1. **初级**: 阅读 README.md,理解项目结构
2. **中级**: 阅读 CMAKE_TUTORIAL.md 的前半部分
3. **高级**: 完成教程中的实战练习
4. **进阶**: 学习高级特性和最佳实践

## 下一步

- 📖 阅读 [CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md) 深入学习
- 🔧 尝试修改代码并重新编译
- ✅ 编写自己的测试用例
- 📦 尝试添加新的库或模块

## 常见问题

**Q: 找不到 cmake 命令?**

A: 需要先安装 CMake:
```bash
# Ubuntu/Debian
sudo apt-get install cmake

# macOS
brew install cmake

# 检查版本
cmake --version
```

**Q: 编译失败?**

A: 确保有 C++ 编译器:
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
xcode-select --install
```

**Q: 如何查看详细的编译过程?**

A: 使用 verbose 模式:
```bash
cmake --build . --verbose
# 或
make VERBOSE=1
```
