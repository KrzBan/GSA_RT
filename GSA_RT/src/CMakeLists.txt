add_library (GSA_RT_lib)
target_sources(GSA_RT_lib PRIVATE 
				"Core.hpp" "Core.cpp" "Renderer.hpp" "Renderer.cpp" "stb_impl.cpp")

set_target_properties(GSA_RT_lib PROPERTIES CXX_STANDARD 20)

target_precompile_headers(GSA_RT_lib PRIVATE <iostream> <array> <vector>)

find_package(stb REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(GSA_RT_lib spdlog::spdlog stb::stb)
