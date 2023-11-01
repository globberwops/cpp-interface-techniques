add_library(StrongTypeStatic)
target_sources(StrongTypeStatic PRIVATE strong_type_static.cpp)
target_link_libraries(StrongTypeStatic PUBLIC gw::StrongType)
