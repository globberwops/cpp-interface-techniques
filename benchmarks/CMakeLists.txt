include(FetchContent)

FetchContent_Declare(
  Benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG 344117638c8ff7e239044fd0fa7085839fc03021 # v1.8.3
  FIND_PACKAGE_ARGS NAMES benchmark)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(Benchmark)

add_executable(CppInterfaceTechniquesBenchmark)

target_sources(CppInterfaceTechniquesBenchmark PRIVATE benchmark.cpp)

target_link_libraries(CppInterfaceTechniquesBenchmark PRIVATE benchmark::benchmark
                                                              CppInterfaceTechniques::CrtpAdaptersExceptionsMap)

add_compiler_warnings(CppInterfaceTechniquesBenchmark)
