#CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

set(PROJ_NAME MyOpenGL)
project(${PROJ_NAME})
# =======================================================#
# Source Files Settings
# =======================================================#
list(APPEND SOURCE_FILES
	src/main.cpp)
add_executable(${PROJ_NAME} ${SOURCE_FILES})
# source_group("Source Files\\api" REGULAR_EXPRESSION "src\/api\/.+")
if (MSVC) 
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME})
endif()

add_subdirectory(lib)

# =======================================================#
# Compiler Settings
# =======================================================#
target_compile_options(${PROJ_NAME} PRIVATE -Wall
	$<$<CXX_COMPILER_ID:MSVC>:-Zc:__cplusplus>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-c++98-compat>
)
target_include_directories(${PROJ_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src/")
