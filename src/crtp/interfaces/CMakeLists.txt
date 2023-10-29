add_library(CrtpInterfaces INTERFACE)
add_library(CppInterfaceTechniques::CrtpInterfaces ALIAS CrtpInterfaces)

target_include_directories(CrtpInterfaces INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                    $<INSTALL_INTERFACE:include>)

target_link_libraries(CrtpInterfaces INTERFACE Gw::StrongType)
