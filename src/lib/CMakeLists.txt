# Library Definition, add source files here
add_library(Raymarcher
	src/matrix.c
	src/ppm.c
	src/sdfs.c
	src/vector.c
	)
# Includes Definitions, add header files here
target_include_directories(Raymarcher PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	)
