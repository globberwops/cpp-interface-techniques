cmake_minimum_required(VERSION 3.24)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(
  CppInterfaceTechniques
  VERSION 1.0.0
  DESCRIPTION "A review of C++ Interface Techniques"
  HOMEPAGE_URL "https://github.com/globberwops/cpp-interface-techniques"
  LANGUAGES CXX)

include(FetchDeps)
include(CompilerWarnings)

option(CPP_INTERFACE_TECHNIQUES_BUILD_BENCHMARKS "Build benchmarks" ${PROJECT_IS_TOP_LEVEL})
option(CPP_INTERFACE_TECHNIQUES_BUILD_DOCS "Build documentation" ${PROJECT_IS_TOP_LEVEL})
option(CPP_INTERFACE_TECHNIQUES_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src)
add_subdirectory(third_party)

if(CPP_INTERFACE_TECHNIQUES_BUILD_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if(CPP_INTERFACE_TECHNIQUES_BUILD_DOCS)
  add_subdirectory(docs)
endif()

if(CPP_INTERFACE_TECHNIQUES_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
