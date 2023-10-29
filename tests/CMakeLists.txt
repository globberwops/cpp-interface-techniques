include(FetchContent)

FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
  FIND_PACKAGE_ARGS NAMES GTest)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(GoogleTest)

include(GoogleTest)

add_subdirectory(exceptions_map)
add_subdirectory(optional_map)
add_subdirectory(pointers_map)

add_subdirectory(crtp)
