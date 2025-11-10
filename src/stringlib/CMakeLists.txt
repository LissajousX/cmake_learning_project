# StringLib 库的 CMakeLists.txt

# 创建库
add_library(stringlib)

target_sources(stringlib
    PRIVATE
        stringutils.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
            ${PROJECT_SOURCE_DIR}/include/stringlib/stringutils.h
)

# 继承通用编译告警
target_link_libraries(stringlib PRIVATE compiler_warnings)

# 设置库的包含目录
target_include_directories(stringlib
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 设置库的属性
set_target_properties(stringlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "string"
)

# 安装库
install(TARGETS stringlib
    FILE_SET HEADERS DESTINATION include
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# 打印信息
message(STATUS "配置 StringLib 库")
