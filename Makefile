#			#
#	Makefile	#
#			#

export SHELL = /bin/bash
export CC = cc
export WFLAGS = -ansi -pedantic -Wall \
       -Wmissing-prototypes -Wstrict-prototypes \
       -Wshadow \
       -Wpointer-arith -Wcast-qual -Wcast-align \
       -Wwrite-strings -Wnested-externs \
       -fshort-enums -fno-common -Dinline=

export CFLAGS = $(WFLAGS)
       # -Wpointer-arith -Wcast-qual -Wcast-align\
       # -Wwrite-strings -Wnested-externs\
       # -fshort-enums -fno-common
       # -Wmissing-prototypes -Wstrict-prototypes
       # -Wconversion -Wshadow
export OFLAGS = -O2 # left empty for debuggin reasons
export GDBFLAGS = -ggdb
export FLAGS = $(CFLAGS) $(OFLAGS) $(GDBFLAGS)
export LIBS = -lm -lgsl -lgslcblas # -lfftw3
export ARCHIVE = $(PWD)/libyapdes.a
export MAKEFILES = $(PWD)/Makefile.common
export INCLUDES = $(PWD)/solver
DIRS = solver
# $(patsubst %/,%,$(wildcard */))

.PHONY : clean $(DIRS) #project test

project: CLEAR_AR $(DIRS)

test: project test.o $(DIRS)
	$(CC) $(FLAGS) $(LIBS) -I $(INCLUDES) test.o $(ARCHIVE) -o $@

test.o: test.c test.h
	$(CC) $(FLAGS) -I $(INCLUDES) -c -o $@ $<

CLEAR_AR:
	@rm -f libyapdes.a
	@ar rs libyapdes.a

$(DIRS):
	@$(MAKE) --no-print-directory -eC $@ project

clean:
	@rm -f *.o libyapdes.a
	@for d in $(DIRS); do $(MAKE) -eC "$${d}" $@; done
