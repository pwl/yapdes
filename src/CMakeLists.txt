include_directories( . )

# Search for the source files recursively and add them to yapdes_src
file( GLOB_RECURSE yapdes_src [^.]*.c )

# set the additional compile flags
set_source_files_properties(${yapdes_src}
  PROPERTIES
  COMPILE_FLAGS
  "${w_flags} ${w_flags_disable} ${o_flags} ${d_flags}")

set_source_files_properties(${yapdes_src}
  PROPERTIES
  LANGUAGE
  CXX)


# SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})
# SET_TARGET_PROPERTIES(f0main${DEBUGEXT} PROPERTIES LINKER_LANGUAGE CXX)

add_library(yapdes SHARED ${yapdes_src})
