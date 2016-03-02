cmake_minimum_required (VERSION 3.3)
project (ft_malloc)
include_directories(includes)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/nfs/2014/e/edelangh/work/malloc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
add_library(ft_malloc SHARED 
	malloc.c
	tools.c
	realloc.c
	reallocf.c
	calloc.c
	valloc.c
	free.c
	)
#add_library(ft_malloc MODULE malloc.c)
