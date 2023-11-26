add_library(InheritanceInterfaces INTERFACE)
add_library(CppInterfaceTechniques::InheritanceInterfaces ALIAS InheritanceInterfaces)

target_include_directories(InheritanceInterfaces INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                           $<INSTALL_INTERFACE:include>)

target_link_libraries(InheritanceInterfaces INTERFACE gw::StrongType)
