add_executable(InheritanceTest)

target_sources(InheritanceTest PRIVATE inheritance_test.cpp)

target_link_libraries(
  InheritanceTest PRIVATE GTest::gtest_main CppInterfaceTechniques::InheritanceAdaptersExceptionsMap
                          CppInterfaceTechniques::InheritanceAdaptersOptionalMap)

add_compiler_warnings(InheritanceTest)

gtest_discover_tests(InheritanceTest)
