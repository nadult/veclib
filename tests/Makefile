CC=/usr/local/gcc-4.3-20080215/bin/g++
#CC=g++
FLAGS=-O3 -mssse3 -I ../

all: test_float

tests: tests.cpp test_ivec.cpp
	$(CC) $(FLAGS) tests.cpp -o tests -lboost_unit_test_framework-gcc42-mt-1_34_1

test_float: test_float.cpp
	$(CC) $(FLAGS) test_float.cpp -o test_float

temp: temp.cpp
	$(CC) $(FLAGS) temp.cpp -o temp

clean:
	rm *.gch *.o temp tests
