add_executable (GSA_RT)
target_sources(GSA_RT PRIVATE "GSA_RT.cpp" "GSA_RT.hpp" )

target_link_libraries(GSA_RT GSA_RT_lib)

add_subdirectory(src)