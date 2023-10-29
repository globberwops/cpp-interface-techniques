add_executable(OptionalMapTest)

target_sources(OptionalMapTest PRIVATE optional_map_test.cpp)

target_link_libraries(OptionalMapTest PRIVATE GTest::gtest_main CppInterfaceTechniques::OptionalMap)

target_compile_features(OptionalMapTest PRIVATE cxx_std_23)

add_compiler_warnings(OptionalMapTest)

gtest_discover_tests(OptionalMapTest)
