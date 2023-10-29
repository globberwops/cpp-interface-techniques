add_executable(OptionalMapTest)

target_sources(OptionalMapTest PRIVATE optional_map_test.cpp)

target_link_libraries(OptionalMapTest PRIVATE GTest::gtest_main CppInterfaceTechniques::OptionalMap)

add_compiler_warnings(OptionalMapTest)

gtest_discover_tests(OptionalMapTest)
