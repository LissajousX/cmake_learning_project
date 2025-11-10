# 测试程序的 CMakeLists.txt

find_package(Threads REQUIRED)

# Calculator 测试
add_executable(test_calculator test_calculator.cpp)
target_link_libraries(test_calculator PRIVATE mathlib gtest_main gtest Threads::Threads)

# Statistics 测试
add_executable(test_statistics test_statistics.cpp)
target_link_libraries(test_statistics PRIVATE mathlib gtest_main gtest Threads::Threads)

# StringUtils 测试
add_executable(test_stringutils test_stringutils.cpp)
target_link_libraries(test_stringutils PRIVATE stringlib gtest_main gtest Threads::Threads)

include(GoogleTest)
gtest_discover_tests(test_calculator)
gtest_discover_tests(test_statistics)
gtest_discover_tests(test_stringutils)

# 打印信息
message(STATUS "配置测试程序")
