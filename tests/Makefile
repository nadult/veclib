#CC=/usr/local/gcc-4.3-20080215/bin/g++
CC=g++
FLAGS=-O3 -msse3 -I ../

tests: tests.cpp test_ivec.cpp
	$(CC) $(FLAGS) tests.cpp -o tests -lboost_unit_test_framework-gcc42-mt-1_34_1
