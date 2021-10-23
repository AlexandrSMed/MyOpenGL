#CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

add_library(stb STATIC
	src/stb_imp.cpp)

target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")