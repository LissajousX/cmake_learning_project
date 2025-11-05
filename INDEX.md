# CMake 学习项目 - 文档索引

欢迎来到 CMake 学习项目!这个索引将帮助你快速找到所需的文档。

## 📚 文档导航

### 🚀 新手入门

1. **[README.md](README.md)** - 从这里开始!
   - 项目概述
   - 项目结构说明
   - 功能特性介绍
   - 基本使用方法

2. **[QUICKSTART.md](QUICKSTART.md)** - 5分钟快速上手
   - 快速构建步骤
   - 常用命令速查
   - 常见问题解答

### 📖 深度学习

3. **[CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md)** - 完整教程(推荐!)
   - CMake 基础概念
   - 详细的语法讲解
   - 实战练习
   - 最佳实践
   - 高级特性

### 📊 项目参考

4. **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** - 项目总结
   - 完整的文件清单
   - 功能模块说明
   - CMake 知识点覆盖
   - 学习路径建议
   - 扩展建议

## 🎯 根据目标选择文档

### 我想快速运行项目

→ 阅读 [QUICKSTART.md](QUICKSTART.md)

```bash
./build.sh all
./build/bin/simple_demo
```

### 我想系统学习 CMake

→ 按顺序阅读:
1. [README.md](README.md) - 了解项目
2. [QUICKSTART.md](QUICKSTART.md) - 动手实践
3. [CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md) - 深入学习

### 我想查找特定的 CMake 功能

→ 使用 [CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md) 的目录导航

### 我想了解项目的整体情况

→ 阅读 [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)

## 📁 源代码导航

### 头文件 (API 接口)

```
include/
├── mathlib/
│   ├── calculator.h      # 基本数学运算
│   └── statistics.h      # 统计分析函数
└── stringlib/
    └── stringutils.h     # 字符串处理工具
```

### 实现文件

```
src/
├── mathlib/
│   ├── calculator.cpp
│   ├── statistics.cpp
│   └── CMakeLists.txt    # 数学库构建配置
└── stringlib/
    ├── stringutils.cpp
    └── CMakeLists.txt    # 字符串库构建配置
```

### 应用程序

```
apps/
├── calculator_app.cpp    # 交互式计算器(推荐运行!)
├── simple_demo.cpp       # 简单演示程序
└── CMakeLists.txt        # 应用程序构建配置
```

### 测试代码

```
tests/
├── test_calculator.cpp   # 计算器测试
├── test_statistics.cpp   # 统计函数测试
├── test_stringutils.cpp  # 字符串工具测试
└── CMakeLists.txt        # 测试构建配置
```

## 🔧 CMake 配置文件

| 文件 | 说明 | 关键知识点 |
|------|------|-----------|
| `CMakeLists.txt` | 根配置 | project(), option(), add_subdirectory() |
| `src/mathlib/CMakeLists.txt` | 数学库 | add_library(), target_include_directories() |
| `src/stringlib/CMakeLists.txt` | 字符串库 | add_library(), set_target_properties() |
| `apps/CMakeLists.txt` | 应用程序 | add_executable(), target_link_libraries() |
| `tests/CMakeLists.txt` | 测试 | add_test(), enable_testing() |
| `config.h.in` | 配置模板 | configure_file() |

## 🎓 学习路线图

```
第1天: 快速入门
├── 阅读 README.md
├── 运行 ./build.sh all
└── 体验演示程序

第2-3天: 基础学习
├── 阅读 CMAKE_TUTORIAL.md (前半部分)
├── 理解项目结构
└── 修改代码并重新编译

第4-5天: 实战练习
├── 完成教程中的练习
├── 添加新功能
└── 编写测试用例

第6-7天: 进阶学习
├── 学习高级特性
├── 添加外部依赖
└── 优化构建配置
```

## 💡 快速命令参考

### 构建项目

```bash
# 使用脚本(推荐)
./build.sh all

# 手动构建
mkdir build && cd build
cmake ..
cmake --build .
```

### 运行程序

```bash
# 简单演示
./build/bin/simple_demo

# 交互式计算器
./build/bin/calculator_app
```

### 运行测试

```bash
cd build
ctest
# 或
ctest -V  # 详细输出
```

### 清理项目

```bash
./build.sh clean
# 或
rm -rf build
```

## 🔍 关键概念速查

### CMake 基础

- **目标(Target)**: 库或可执行文件
- **属性(Property)**: 目标的配置选项
- **依赖(Dependency)**: 目标之间的关系
- **生成器(Generator)**: 生成平台特定的构建文件

### 作用域

- **PUBLIC**: 当前目标和依赖它的目标都使用
- **PRIVATE**: 仅当前目标使用
- **INTERFACE**: 仅依赖它的目标使用

### 常用命令

```cmake
project()                    # 定义项目
add_library()               # 创建库
add_executable()            # 创建可执行文件
target_link_libraries()     # 链接库
target_include_directories() # 设置包含目录
add_subdirectory()          # 添加子目录
install()                   # 安装规则
```

## 📞 获取帮助

### 遇到问题?

1. 查看 [QUICKSTART.md](QUICKSTART.md) 的常见问题部分
2. 查看 [CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md) 的常见问题部分
3. 查看 CMake 官方文档
4. 使用 `cmake --help` 查看帮助

### 想要更多示例?

- 修改现有代码
- 完成教程中的练习
- 查看 CMake 官方示例

## 🌟 推荐阅读顺序

**初学者路径**:
1. README.md (10分钟)
2. QUICKSTART.md (15分钟)
3. 动手构建和运行 (10分钟)
4. CMAKE_TUTORIAL.md 前3章 (1小时)
5. 实战练习 (2小时)

**快速参考路径**:
1. QUICKSTART.md
2. PROJECT_SUMMARY.md
3. 直接查看源代码

**深度学习路径**:
1. README.md
2. CMAKE_TUTORIAL.md (完整阅读)
3. 完成所有练习
4. 扩展项目功能

## 📈 项目统计

- **文档总数**: 5个 Markdown 文件
- **代码文件**: 15个 C++ 文件
- **CMake 配置**: 6个文件
- **总代码量**: ~2000行
- **学习时间**: 建议 10-20 小时

## 🎉 开始学习

准备好了吗?从这里开始:

1. **完全新手** → [QUICKSTART.md](QUICKSTART.md)
2. **想系统学习** → [CMAKE_TUTORIAL.md](CMAKE_TUTORIAL.md)
3. **快速查阅** → [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)

---

**祝你学习愉快!** 🚀

*最后更新: 2025年11月*
