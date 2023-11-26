add_library(InheritanceAdaptersExceptionsMap INTERFACE)
add_library(CppInterfaceTechniques::InheritanceAdaptersExceptionsMap ALIAS InheritanceAdaptersExceptionsMap)

target_include_directories(InheritanceAdaptersExceptionsMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                                      $<INSTALL_INTERFACE:include>)

target_link_libraries(InheritanceAdaptersExceptionsMap INTERFACE CppInterfaceTechniques::InheritanceInterfaces
                                                                 CppInterfaceTechniques::ExceptionsMap)
