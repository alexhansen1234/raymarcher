cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project (raymarcher VERSION 0.1 LANGUAGES C)

set(PROJECT_BINARY_DIR, ../build)

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
	message(FATAL_ERROR "In source builds are not allowed. Please run CMake from build directory." )	
endif()

add_subdirectory("src/lib")

add_executable(raymarcher src/app/main.c)

target_link_libraries(raymarcher
	Raymarcher
	m
	pthread
	)

target_compile_options(raymarcher
	PUBLIC
	-Wall
	-O3
	)
