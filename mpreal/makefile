LDIR=/usr/lib/
IDIR=/usr/include/

example: example.o mpreal.o dlmalloc.o
	g++ example.o mpreal.o dlmalloc.o $(LDIR)libmpfr.a $(LDIR)libgmp.a -o example

mpreal.o: mpreal.cpp mpreal.h
	g++ -fPIC -c mpreal.cpp

example.o: example.cpp mpreal.h
	g++ -c example.cpp

dlmalloc.o: dlmalloc.c dlmalloc.h
	g++ -fPIC -c dlmalloc.c


clean:
	rm -f *.o *.so*

shared: mpreal.o dlmalloc.o
	g++ -shared -o libdlmalloc.so.2.8.0 dlmalloc.o
	g++ -shared -o libmpreal.so.1 -lmpfr -lgmp -ldlmalloc mpreal.o

install: shared
	rm -f $(LDIR)lib{dlmalloc,mpreal}*
	cp libmpreal.so.1 libdlmalloc.so.2.8.0 $(LDIR)
	ldconfig
	cp mpreal.h $(IDIR)

example_link: install example.o
	g++ example.o -ldlmalloc -lmpreal -o example
