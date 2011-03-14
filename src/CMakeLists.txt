include_directories( . )

# Search for the source files recursively and add them to yapdes_src
file( GLOB_RECURSE yapdes_src *.c )

set_source_files_properties(${yapdes_src}
	PROPERTIES
	COMPILE_FLAGS
	"${w_flags} ${o_flags} ${d_flags}")

add_library(yapdes SHARED ${yapdes_src})
