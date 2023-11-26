add_library(InheritanceAdaptersOptionalMap INTERFACE)
add_library(CppInterfaceTechniques::InheritanceAdaptersOptionalMap ALIAS InheritanceAdaptersOptionalMap)

target_include_directories(InheritanceAdaptersOptionalMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                                    $<INSTALL_INTERFACE:include>)

target_link_libraries(InheritanceAdaptersOptionalMap INTERFACE CppInterfaceTechniques::InheritanceInterfaces
                                                               CppInterfaceTechniques::OptionalMap)
