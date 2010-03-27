project(yapdes C)

cmake_minimum_required(VERSION 2.6)

include_directories(solver)
include_directories(error)
include_directories(marcher)

file(GLOB_RECURSE src solver/*.c error/*.c marcher/*.c)

set(w_flags "-ansi -pedantic -Wall -Wshadow -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -fshort-enums -fno-common -Dinline=")

set(o_flags "-O2")
set(d_flags "-ggdb")

set_source_files_properties(${solver_src}
	PROPERTIES
	COMPILE_FLAGS
	"${w_flags} ${o_flags} ${d_flags}")

add_library(yapdes SHARED ${src})

# yapdes independent part

# find all files with .c extension and compile them to the ./bin
file(GLOB bin_list RELATIVE ${PROJECT_BINARY_DIR} *.c)

foreach(bin ${bin_list})
  string(REPLACE ".c" "" bin ${bin})
  add_executable(${bin} ${bin}.c)
  set_target_properties(${bin}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    bin)
  target_link_libraries(${bin} yapdes m)
endforeach(bin)
