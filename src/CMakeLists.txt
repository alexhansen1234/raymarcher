cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project (raymarcher VERSION 0.1 LANGUAGES C)

add_subdirectory("lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../build)

add_executable(raymarcher app/main.c)
target_link_libraries(raymarcher
	Raymarcher
	m
	)

target_compile_options(raymarcher
	PUBLIC
	-Wall
	-O3
	)
