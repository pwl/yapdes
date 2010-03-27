project(yapdes C)
cmake_minimum_required(VERSION 2.6)

include_directories(solver)
include_directories(error)
include_directories(marcher)

file(GLOB_RECURSE solver_src solver/*.c)
file(GLOB_RECURSE error_src error/*.c)
file(GLOB_RECURSE marcher_src marcher/*.c)

set(w_flags "-ansi -pedantic -Wall -Wshadow -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -fshort-enums -fno-common -Dinline=")

set(o_flags "-O2")
set(d_flags "-ggdb")

# message(${d_flags})

set_source_files_properties(${solver_src}
	PROPERTIES
	COMPILE_FLAGS
	"${w_flags} ${o_flags} ${d_flags}")

add_library(yapdes SHARED ${solver_src} ${marcher_src} ${error_src})

# yapdes independent part

add_executable(test test.c)

target_link_libraries(test yapdes m)
