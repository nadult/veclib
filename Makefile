PREFIX=/usr/local
CROSS=

CXX=$(CROSS)g++ -std=gnu++0x -Wall
SXX=spu-g++ -Wall
FLAGS=-O3 -I ./ -D VECLIB_PREPROCESS

all: vecliball_scalar.h vecliball_sse2.h vecliball_sse.h

vecliball_sse2.h: Makefile *.h
	$(CXX) -msse2 $(FLAGS) -include veclib_conf.h vecliball.h -o - -E | \
		grep -e ^[^#] > $@

vecliball_sse.h: Makefile *.h
	$(CXX) -m32 -msse $(FLAGS) -include veclib_conf.h vecliball.h -o - -E | \
		grep -e ^[^#] > $@

vecliball_scalar.h: Makefile *.h
	$(CXX) $(FLAGS) -include veclib_conf.h vecliball.h -o - -E | \
		grep -e ^[^#] > $@

#vecliball_altivec.h: Makefile *.h
#	$(CXX) -maltivec $(FLAGS) -include veclib_conf.h vecliball.h -o - -E | \
#		grep -e ^[^#] > $@

#vecliball_spu.h: Makefile *.h
#	$(SXX) $(FLAGS) -include veclib_conf.h vecliball.h -o - -E | \
#		grep -e ^[^#] > $@

clean:
	-rm vecliball_*.h

install:
	install -m 644 vecliball_*.h $(PREFIX)/include/
	install -m 644 veclib.h $(PREFIX)/include/
	install -m 644 veclib_conf.h $(PREFIX)/include/

uninstall:
	rm $(PREFIX)/include/vecliball_*.h
	rm $(PREFIX)/include/veclib.h
	rm $(PREFIX)/include/veclib_conf.h

.PHONY: clean install uninstall

