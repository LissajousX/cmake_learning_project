# MathLib 库的 CMakeLists.txt

# 创建库
add_library(mathlib)

target_sources(mathlib
    PRIVATE
        calculator.cpp
        statistics.cpp
        geometry.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
            ${PROJECT_SOURCE_DIR}/include/mathlib/calculator.h
            ${PROJECT_SOURCE_DIR}/include/mathlib/statistics.h
            ${PROJECT_SOURCE_DIR}/include/mathlib/geometry.h
)

# 继承通用编译告警
target_link_libraries(mathlib PRIVATE compiler_warnings)

# 设置库的包含目录
target_include_directories(mathlib
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 设置库的属性
set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "math"
)

# 安装库
install(TARGETS mathlib
    FILE_SET HEADERS DESTINATION include
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# 打印信息
message(STATUS "配置 MathLib 库")
