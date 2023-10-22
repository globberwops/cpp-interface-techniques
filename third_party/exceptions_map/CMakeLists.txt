add_library(ExceptionsMap INTERFACE)
add_library(CppInterfaceTechniques::ExceptionsMap ALIAS ExceptionsMap)

target_include_directories(ExceptionsMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party>
                                                   $<INSTALL_INTERFACE:include>)
