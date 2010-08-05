CXX=g++
SXX=spu-g++
CXXFLAGS=-O3 -ffast-math -I ../ 

all: test_int test_float
	
test_float: test_float10 test_float20 test_float30 test_float31

test_int: test_int20 test_int30 test_int31

#tests: tests.cpp test_ivec.cpp
#	$(CXX) $(CXXFLAGS) tests.cpp -o tests -lboost_unit_test_framework-gcc42-mt-1_34_1


test_float_sse2: test_float.cpp ../*.h
	$(CXX) $(CXXFLAGS) -msse2 $< -o $@

test_float_sse: test_float.cpp ../*.h
	$(CXX) $(CXXFLAGS) -m32 -msse $< -o $@

test_float_scalar: test_float.cpp ../*.h
	$(CXX) $(CXXFLAGS) -m32 $< -o $@

test_float_altivec: test_float.cpp ../*.h
	$(CXX) $(CXXFLAGS) -mabi=altivec -maltivec $< -o $@

test_float_spu: test_float.cpp ../*.h
	$(SXX) $(CXXFLAGS) $< -o $@

test_int_sse2: test_int.cpp ../*.h
	$(CXX) $(CXXFLAGS) -msse2 $< -o $@

test_int_scalar: test_int.cpp ../*.h
	$(CXX) $(CXXFLAGS) -m32 $< -o $@

test_int_altivec: test_int.cpp ../*.h
	$(CXX) $(CXXFLAGS) -mabi=altivec -maltivec $< -o $@

temp: temp.cpp ../*.h
	$(CXX) $(CXXFLAGS) temp.cpp -o temp


clean:
	-rm *.gch *.o temp tests \
		test_float_sse test_float_sse2 test_float_scalar test_float_altivec \
		test_int_sse2 test_int_scalar test_int_altivec

.PHONY: clean test_int test_float all

