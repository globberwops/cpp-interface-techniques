add_library(OptionalMap INTERFACE)
add_library(CppInterfaceTechniques::OptionalMap ALIAS OptionalMap)

target_include_directories(OptionalMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party>
                                                 $<INSTALL_INTERFACE:include>)
