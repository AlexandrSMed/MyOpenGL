#CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

set(PROJ_NAME MyOpenGL)
project(${PROJ_NAME})
# =======================================================#
# Source Files Settings
# =======================================================#
list(APPEND SOURCE_FILES
    src/main.cpp
    src/WindowManager.cpp
    src/Utils.cpp
    src/Camera.cpp
    src/renderers/Renderer.cpp
    src/renderers/StaticRenderer.cpp
    src/renderers/StaticShaders.cpp
    src/renderers/BasicRenderer.cpp
    src/renderers/BasicShaders.cpp)

add_executable(${PROJ_NAME} ${SOURCE_FILES})
source_group("Source Files\\renderers" REGULAR_EXPRESSION "src\/renderers\/.+")
if (MSVC) 
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME})
endif()

# =======================================================#
# Library depdendencies
# =======================================================#
add_subdirectory(lib)

# Copying assets
set(ASSETS_DIR  ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(GLOB_RECURSE ASSETS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/assets/*")
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSETS_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSETS} ${ASSETS_DIR}
)
add_dependencies(${PROJ_NAME} copy_assets)

# =======================================================#
# Compiler Settings
# =======================================================#
target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wno-missing-prototypes -DLOG
    $<$<CXX_COMPILER_ID:MSVC>:-Zc:__cplusplus>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-c++98-compat>
)
target_include_directories(${PROJ_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src/")
