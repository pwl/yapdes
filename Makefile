#			#
#	Makefile	#
#			#

export SHELL = /bin/bash
export CC = cc
export CFLAGS = -ansi -pedantic -Wall
       # -Wpointer-arith -Wcast-qual -Wcast-align\
       # -Wwrite-strings -Wnested-externs\
       # -fshort-enums -fno-common
       # -Wmissing-prototypes -Wstrict-prototypes
       # -Wconversion -Wshadow
export OFLAGS = # -O3 # left empty for debuggin reasons
export GDBFLAGS = #-ggdb
export FLAGS = $(CFLAGS) $(OFLAGS) $(GDBFLAGS)
export LIBS = -lm -lgsl -lgslcblas # -lfftw3
export ARCHIVE = $(PWD)/libyapdes.a
export MAKEFILES = $(PWD)/Makefile.common
export INCLUDES = $(PWD)/solver
DIRS = solver
# $(patsubst %/,%,$(wildcard */))

.PHONY : clean $(DIRS) project

project: CLEAR_AR $(DIRS)

CLEAR_AR:
	@rm libyapdes.a
	@ar rs libyapdes.a

$(DIRS):
	@$(MAKE) --no-print-directory -eC $@ project

clean:
	@rm -f *.o libyapdes.a
	@for d in $(DIRS); do $(MAKE) -eC "$${d}" $@; done
