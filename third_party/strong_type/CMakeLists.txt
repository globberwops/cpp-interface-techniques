add_library(StrongType INTERFACE)
add_library(Gw::StrongType ALIAS StrongType)

target_include_directories(StrongType INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party>
                                                $<INSTALL_INTERFACE:include>)
