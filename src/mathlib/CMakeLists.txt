# MathLib 库的 CMakeLists.txt

# 收集源文件
set(MATHLIB_SOURCES
    calculator.cpp
    statistics.cpp
)

# 创建库
add_library(mathlib ${MATHLIB_SOURCES})

# 设置库的包含目录
target_include_directories(mathlib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 设置库的属性
set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "math"
)

# 安装库
install(TARGETS mathlib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# 打印信息
message(STATUS "配置 MathLib 库")
