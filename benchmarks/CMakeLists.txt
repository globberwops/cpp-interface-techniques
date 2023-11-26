add_executable(CppInterfaceTechniquesBenchmark)

target_sources(CppInterfaceTechniquesBenchmark PRIVATE benchmark.cpp)

target_link_libraries(CppInterfaceTechniquesBenchmark PRIVATE benchmark::benchmark
                                                              CppInterfaceTechniques::CrtpAdaptersExceptionsMap)

add_compiler_warnings(CppInterfaceTechniquesBenchmark)
