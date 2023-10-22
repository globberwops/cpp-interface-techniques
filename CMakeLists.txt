cmake_minimum_required(VERSION 3.24)

project(CppInterfaceTechniques CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_subdirectory(third_party)
add_subdirectory(tests)
add_subdirectory(docs)
