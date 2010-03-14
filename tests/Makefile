#CC=/usr/local/gcc-4.3-20080215/bin/g++
CC=g++
FLAGS=-O3 -ffast-math -I ../ 

all: test_int test_float
	
test_float: test_float10 test_float20 test_float30 test_float31

test_int: test_int20 test_int30 test_int31

#tests: tests.cpp test_ivec.cpp
#	$(CC) $(FLAGS) tests.cpp -o tests -lboost_unit_test_framework-gcc42-mt-1_34_1


test_float31: test_float.cpp ../*.h
	$(CC) $(FLAGS) -mssse3 test_float.cpp -o test_float31

test_float30: test_float.cpp ../*.h
	$(CC) $(FLAGS) -mssse3 test_float.cpp -o test_float30

test_float20: test_float.cpp ../*.h
	$(CC) $(FLAGS) -mssse3 test_float.cpp -o test_float20

test_float10: test_float.cpp ../*.h
	$(CC) $(FLAGS) -mssse3 test_float.cpp -o test_float10


test_int31: test_int.cpp ../*.h
	$(CC) $(FLAGS) -mssse3 test_int.cpp -o test_int31

test_int30: test_int.cpp ../*.h
	$(CC) $(FLAGS) -msse3 test_int.cpp -o test_int30

test_int20: test_int.cpp ../*.h
	$(CC) $(FLAGS) -msse2 test_int.cpp -o test_int20

temp: temp.cpp ../*.h
	$(CC) $(FLAGS) temp.cpp -o temp


clean:
	-rm *.gch *.o temp tests \
		test_float10 test_float20 test_float30 test_float31 \
		test_int20 test_int30 test_int31 

.PHONY: clean test_int test_float all

