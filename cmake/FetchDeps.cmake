include_guard()

include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG 344117638c8ff7e239044fd0fa7085839fc03021 # v1.8.3
  SYSTEM FIND_PACKAGE_ARGS 1.8)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
  SYSTEM FIND_PACKAGE_ARGS NAMES GTest 1.14)
set(INSTALL_GTEST OFF)

FetchContent_MakeAvailable(benchmark googletest)
