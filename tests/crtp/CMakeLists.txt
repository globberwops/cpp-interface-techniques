add_executable(CrtpTest)

target_sources(CrtpTest PRIVATE crtp_exceptions_map.cpp crtp_optional_map.cpp)

target_link_libraries(CrtpTest PRIVATE GTest::gtest_main CppInterfaceTechniques::CrtpAdaptersExceptionsMap)

target_compile_features(CrtpTest PRIVATE cxx_std_17)

add_compiler_warnings(CrtpTest)

gtest_discover_tests(CrtpTest)
