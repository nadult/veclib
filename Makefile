CC=/usr/local/gcc-4.3-20080215/bin/g++
FLAGS=-O3

all: vecliball_pp31.h vecliball_pp30.h vecliball_pp20.h vecliball_pp10.h vecliball_pp00.h

vecliball_pp31.h: Makefile *.h
	$(CC) $(FLAGS) -mssse3 -include veclib_conf.h vecliball.h -o vecliball_pp.tmp1 -E
	grep vecliball_pp.tmp1 -e ^[^#] > vecliball_pp.tmp2
	uncrustify -f vecliball_pp.tmp2 -l CPP -o vecliball_pp31.h
	rm vecliball_pp.tmp1 vecliball_pp.tmp2

vecliball_pp30.h: Makefile *.h
	$(CC) $(FLAGS) -msse3 -include veclib_conf.h vecliball.h -o vecliball_pp.tmp1 -E
	grep vecliball_pp.tmp1 -e ^[^#] > vecliball_pp.tmp2
	uncrustify -f vecliball_pp.tmp2 -l CPP -o vecliball_pp30.h
	rm vecliball_pp.tmp1 vecliball_pp.tmp2

vecliball_pp20.h: Makefile *.h
	$(CC) $(FLAGS) -msse2 -include veclib_conf.h vecliball.h -o vecliball_pp.tmp1 -E
	grep vecliball_pp.tmp1 -e ^[^#] > vecliball_pp.tmp2
	uncrustify -f vecliball_pp.tmp2 -l CPP -o vecliball_pp20.h
	rm vecliball_pp.tmp1 vecliball_pp.tmp2

vecliball_pp10.h: Makefile *.h
	$(CC) $(FLAGS) -msse -include veclib_conf.h vecliball.h -o vecliball_pp.tmp1 -E
	grep vecliball_pp.tmp1 -e ^[^#] > vecliball_pp.tmp2
	uncrustify -f vecliball_pp.tmp2 -l CPP -o vecliball_pp10.h
	rm vecliball_pp.tmp1 vecliball_pp.tmp2

vecliball_pp00.h: Makefile *.h
	$(CC) $(FLAGS) -include veclib_conf.h vecliball.h -o vecliball_pp.tmp1 -E
	grep vecliball_pp.tmp1 -e ^[^#] > vecliball_pp.tmp2
	uncrustify -f vecliball_pp.tmp2 -l CPP -o vecliball_pp00.h
	rm vecliball_pp.tmp1 vecliball_pp.tmp2

clean:
	rm vecliball_pp*.h

