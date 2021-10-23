cmake_policy(SET CMP0079 NEW)
add_compile_options(-w)
# OpenGL
find_package(OpenGL REQUIRED)
list(APPEND LIB_TARGETS ${OPENGL_LIBRARIES})
list(APPEND LIB_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS})

# GLFW
add_subdirectory(glfw)
list(APPEND LIB_TARGETS glfw)
list(APPEND LIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")

# GLAD
add_subdirectory(glad)
list(APPEND LIB_TARGETS glad)
list(APPEND LIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glad/include")

# stb
add_subdirectory(stb)
list(APPEND LIB_TARGETS stb)
list(APPEND LIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/stb/include")

if(LIB_INCLUDE_DIRS)
	list(REMOVE_DUPLICATES LIB_INCLUDE_DIRS)
	target_include_directories(${PROJ_NAME} PRIVATE ${LIB_INCLUDE_DIRS})
	if(MSVC)
		target_compile_options(${PROJ_NAME} PRIVATE
			"$<$<CXX_COMPILER_ID:Clang>:SHELL:-Xclang -isystem$<JOIN:${LIB_INCLUDE_DIRS}, -Xclang -isystem>>"
	 		"$<$<CXX_COMPILER_ID:MSVC>:SHELL:-experimental:external -external:w -external:I$<JOIN:${LIB_INCLUDE_DIRS}, -external:I>>")
	else()
		target_compile_options(${PROJ_NAME} PRIVATE "SHELL:-isystem $<JOIN:${LIB_INCLUDE_DIRS}, -isystem>")
	endif()
endif()

target_link_libraries(${PROJ_NAME} PRIVATE ${LIB_TARGETS})
