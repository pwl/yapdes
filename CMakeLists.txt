cmake_minimum_required( VERSION 2.6 )

project( yapdes )

# The macro below forces the build directory to be different from source directory:
# include(MacroOutOfSourceBuild)
# macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

set( LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib )

# define compile flags
set(w_flags "-ansi -pedantic -Wall -Wshadow -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -fshort-enums -fno-common -Dinline=")
set(w_flags "")
set(o_flags "-O2")
set(d_flags "-ggdb")

# message( ${LIBRARY_OUTPUT_PATH} )

add_subdirectory( src )

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)


# create targets out of all files from test, they will compile to the
# test directory

file(GLOB bin_list RELATIVE ${PROJECT_SOURCE_DIR}/test ${PROJECT_SOURCE_DIR}/test/*.c)
file(MAKE_DIRECTORY "bin/test")

include_directories( src )

foreach(bin ${bin_list})
  string(REPLACE ".c" "" bin ${bin})
  add_executable(${bin} ${PROJECT_SOURCE_DIR}/test/${bin}.c)
  set_target_properties(${bin}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/test)
  target_link_libraries(${bin} yapdes m)
endforeach(bin)
