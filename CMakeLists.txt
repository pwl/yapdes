cmake_minimum_required( VERSION 2.6 )

project( yapdes )

# The macro below forces the build directory to be different from source directory:
# include(MacroOutOfSourceBuild)
# macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

set( LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib )
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake )

# define compile flags
set(w_flags "-ansi -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings")
set(w_flags_c_only "-Wmissing-prototypes -Wstrict-prototypes -Wnested-externs" )
set(w_flags_disable "-Wno-multichar")
# set(o_flags "-O2")
set(d_flags "-ggdb")
set(flags "${w_flags} ${w_flags_disable} ${o_flags} ${d_flags}")
# add c-only flags
# set(flags "${flags} ${w_flags_c_only}")

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

# check if GMP is installed?
find_package(GMP)

# create targets out of all files from test, they will compile to the
# test directory

file(GLOB bin_list RELATIVE ${PROJECT_SOURCE_DIR}/test ${PROJECT_SOURCE_DIR}/test/*.c)
file(MAKE_DIRECTORY "bin/test")

include_directories( src )

foreach(bin ${bin_list})
  string(REPLACE ".c" "" bin ${bin})

  add_executable(${bin} ${PROJECT_SOURCE_DIR}/test/${bin}.c)

  set_source_files_properties(${PROJECT_SOURCE_DIR}/test/${bin}.c
    PROPERTIES
    LANGUAGE
    CXX)

  set_target_properties(${bin}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/test)

  # set the additional compile flags
  set_target_properties(${bin}
    PROPERTIES
    COMPILE_FLAGS
    ${flags})

  # compile sources with c++-compiler
  set_target_properties(${bin}
    PROPERTIES
    LINKER_LANGUAGE
    CXX)

  
  target_link_libraries(${bin} yapdes dlmalloc mpreal gmp mpfr)
endforeach(bin)

add_executable(example ${PROJECT_SOURCE_DIR}/test/example.cpp)

set_target_properties(example
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/test)

# set_target_properties(example
#   PROPERTIES
#   COMPILE_FLAGS
#   ${flags})

# set_target_properties(example
#   PROPERTIES
#   LINKER_LANGUAGE
#   CXX)

target_link_libraries(example dlmalloc mpreal gmp mpfr)
