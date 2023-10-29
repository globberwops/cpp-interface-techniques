add_library(CrtpAdaptersOptionalMap INTERFACE)
add_library(CppInterfaceTechniques::CrtpAdaptersOptionalMap ALIAS CrtpAdaptersOptionalMap)

target_include_directories(CrtpAdaptersOptionalMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                             $<INSTALL_INTERFACE:include>)

target_link_libraries(CrtpAdaptersOptionalMap INTERFACE CppInterfaceTechniques::CrtpInterfaces
                                                        CppInterfaceTechniques::OptionalMap)
