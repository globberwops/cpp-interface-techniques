add_library(CrtpAdaptersExceptionsMap INTERFACE)
add_library(CppInterfaceTechniques::CrtpAdaptersExceptionsMap ALIAS CrtpAdaptersExceptionsMap)

target_include_directories(CrtpAdaptersExceptionsMap INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                                               $<INSTALL_INTERFACE:include>)

target_link_libraries(CrtpAdaptersExceptionsMap INTERFACE CppInterfaceTechniques::CrtpInterfaces
                                                          CppInterfaceTechniques::ExceptionsMap)
