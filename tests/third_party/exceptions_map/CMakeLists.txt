add_executable(ExceptionsMapTest)

target_sources(ExceptionsMapTest PRIVATE exceptions_map_test.cpp)

target_link_libraries(ExceptionsMapTest PRIVATE GTest::gtest_main CppInterfaceTechniques::ExceptionsMap)

gtest_discover_tests(ExceptionsMapTest)
