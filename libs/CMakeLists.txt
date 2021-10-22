cmake_policy(SET CMP0079 NEW)
add_compile_options(-w)

# Add SleepyDiscord library
# add_subdirectory(sleepy-discord)
# list(APPEND LIB_TARGETS sleepy-discord)
# list(APPEND LIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/sleepy-discord/include")

if(LIB_INCLUDE_DIRS)
	list(REMOVE_DUPLICATES LIB_INCLUDE_DIRS)
	target_include_directories(Grenadine PUBLIC ${LIB_INCLUDE_DIRS})
	if(MSVC)
		target_compile_options(Grenadine PRIVATE
			"$<$<CXX_COMPILER_ID:Clang>:SHELL:-Xclang -isystem$<JOIN:${LIB_INCLUDE_DIRS}, -Xclang -isystem>>"
	 		"$<$<CXX_COMPILER_ID:MSVC>:SHELL:-experimental:external -external:w -external:I$<JOIN:${LIB_INCLUDE_DIRS}, -external:I>>")
	else()
		target_compile_options(Grenadine PRIVATE "SHELL:-isystem $<JOIN:${LIB_INCLUDE_DIRS}, -isystem>")
	endif()
endif()

target_link_libraries(OpenGL PUBLIC ${LIB_TARGETS})
