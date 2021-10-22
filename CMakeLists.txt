#CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

project(OpenGL)
# =======================================================#
# Source Files Settings
# =======================================================#
list(APPEND SOURCE_FILES
	src/main.cpp)
add_executable(OpenGL ${SOURCE_FILES})
# source_group("Source Files\\api" REGULAR_EXPRESSION "src\/api\/.+")
if (MSVC) 
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenGL)
endif()

add_subdirectory(libs)

# =======================================================#
# Compiler Settings
# =======================================================#
target_compile_options(OpenGL PRIVATE -Wall
	$<$<CXX_COMPILER_ID:MSVC>:-Zc:__cplusplus>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-c++98-compat>
)
target_include_directories(OpenGL PUBLIC "${PROJECT_SOURCE_DIR}/src/")
