# 测试程序的 CMakeLists.txt

# Calculator 测试
add_executable(test_calculator test_calculator.cpp)
target_link_libraries(test_calculator PRIVATE mathlib)
add_test(NAME CalculatorTest COMMAND test_calculator)

# Statistics 测试
add_executable(test_statistics test_statistics.cpp)
target_link_libraries(test_statistics PRIVATE mathlib)
add_test(NAME StatisticsTest COMMAND test_statistics)

# StringUtils 测试
add_executable(test_stringutils test_stringutils.cpp)
target_link_libraries(test_stringutils PRIVATE stringlib)
add_test(NAME StringUtilsTest COMMAND test_stringutils)

# 打印信息
message(STATUS "配置测试程序")
