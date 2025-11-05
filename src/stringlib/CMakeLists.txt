# StringLib 库的 CMakeLists.txt

# 收集源文件
set(STRINGLIB_SOURCES
    stringutils.cpp
)

# 创建库
add_library(stringlib ${STRINGLIB_SOURCES})

# 设置库的包含目录
target_include_directories(stringlib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 设置库的属性
set_target_properties(stringlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "string"
)

# 安装库
install(TARGETS stringlib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# 打印信息
message(STATUS "配置 StringLib 库")
