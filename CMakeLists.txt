project(yapdes C)

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR}/yapdes)

file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR}/yapdes/*.c)

set(w_flags "-ansi -pedantic -Wall -Wshadow -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -fshort-enums -fno-common -Dinline=")
set(o_flags "-O2")
set(d_flags "-ggdb")

set_source_files_properties(${src}
	PROPERTIES
	COMPILE_FLAGS
	"${w_flags} ${o_flags} ${d_flags}")

add_library(yapdes SHARED ${src})

# yapdes independent part

# create targets out of all files from src/test, they will compile to
# the bin/test directory

file(GLOB bin_list RELATIVE ${PROJECT_SOURCE_DIR}/test ${PROJECT_SOURCE_DIR}/test/*.c)
file(MAKE_DIRECTORY "bin/test")

foreach(bin ${bin_list})
  string(REPLACE ".c" "" bin ${bin})
  add_executable(${bin} ${PROJECT_SOURCE_DIR}/test/${bin}.c)
  set_target_properties(${bin}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    bin/test/)
  target_link_libraries(${bin} yapdes m)
endforeach(bin)
