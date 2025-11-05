# CMake 学习项目

这是一个用于学习 CMake 的综合示例项目,包含多个库、应用程序和测试。

## 项目结构

```
cmake_learning_project/
├── CMakeLists.txt              # 根 CMake 配置文件
├── config.h.in                 # 配置头文件模板
├── README.md                   # 项目说明
├── include/                    # 头文件目录
│   ├── mathlib/               # 数学库头文件
│   │   ├── calculator.h
│   │   └── statistics.h
│   └── stringlib/             # 字符串库头文件
│       └── stringutils.h
├── src/                        # 源代码目录
│   ├── mathlib/               # 数学库实现
│   │   ├── CMakeLists.txt
│   │   ├── calculator.cpp
│   │   └── statistics.cpp
│   └── stringlib/             # 字符串库实现
│       ├── CMakeLists.txt
│       └── stringutils.cpp
├── apps/                       # 应用程序
│   ├── CMakeLists.txt
│   ├── calculator_app.cpp     # 交互式计算器
│   └── simple_demo.cpp        # 简单演示
└── tests/                      # 测试程序
    ├── CMakeLists.txt
    ├── test_calculator.cpp
    ├── test_statistics.cpp
    └── test_stringutils.cpp
```

## 构建项目

### 基本构建

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 编译
cmake --build .

# 运行测试
ctest

# 运行应用程序
./bin/simple_demo
./bin/calculator_app
```

### 高级构建选项

```bash
# 构建共享库
cmake -DBUILD_SHARED_LIBS=ON ..

# 指定构建类型
cmake -DCMAKE_BUILD_TYPE=Release ..

# 禁用测试
cmake -DBUILD_TESTS=OFF ..

# 禁用应用程序
cmake -DBUILD_APPS=OFF ..

# 安装到指定目录
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
cmake --build .
cmake --install .
```

## 功能特性

### MathLib 数学库
- 基本运算:加、减、乘、除
- 高级运算:幂运算、平方根
- 统计分析:平均值、中位数、方差、标准差

### StringLib 字符串库
- 大小写转换
- 去除空格
- 字符串分割与连接
- 前缀/后缀检查
- 字符串反转

## 学习要点

本项目展示了以下 CMake 概念:

1. **项目组织**: 多目录、多库的项目结构
2. **库管理**: 静态库和共享库的创建
3. **目标链接**: 可执行文件与库的链接
4. **选项控制**: 使用 option() 控制构建行为
5. **测试集成**: 使用 CTest 进行单元测试
6. **配置文件**: 使用 configure_file() 生成配置
7. **安装规则**: 定义安装目标和路径

## 许可证

MIT License
