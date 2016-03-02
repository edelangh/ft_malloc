cmake_minimum_required (VERSION 2.6)
project (ft_malloc)
include_directories(includes)
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
