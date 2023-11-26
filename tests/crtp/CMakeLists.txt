add_executable(CrtpTest)

target_sources(CrtpTest PRIVATE crtp_exceptions_map_test.cpp crtp_optional_map_test.cpp)

target_link_libraries(CrtpTest PRIVATE GTest::gtest_main CppInterfaceTechniques::CrtpAdaptersExceptionsMap
                                       CppInterfaceTechniques::CrtpAdaptersOptionalMap)

add_compiler_warnings(CrtpTest)

gtest_discover_tests(CrtpTest)
