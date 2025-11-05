# 应用程序的 CMakeLists.txt

# 计算器应用程序
add_executable(calculator_app calculator_app.cpp)
target_link_libraries(calculator_app PRIVATE mathlib stringlib)

# 简单演示程序
add_executable(simple_demo simple_demo.cpp)
target_link_libraries(simple_demo PRIVATE mathlib stringlib)

# 安装可执行文件
install(TARGETS calculator_app simple_demo
    RUNTIME DESTINATION bin
)

# 打印信息
message(STATUS "配置应用程序")
