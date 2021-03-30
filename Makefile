CXX = g++
LD = g++

IFLAGS = -Iinclude
WFLAGS = -Wall -Wextra -Wpedantic -Wshadow
CXXFLAGS = -std=c++20 $(IFLAGS) $(WFLAGS)

headers = include/range.hpp include/zip.hpp

default: test

test: range_test.out zip_test.out
	./range_test.out
	./zip_test.out

range_test.out: test/range.cpp $(headers)
	$(CXX) -o $@ $(CXXFLAGS) $<

zip_test.out: test/zip.cpp $(headers)
	$(CXX) -o $@ $(CXXFLAGS) $<

benchmark: range_benchmark.out
	./range_benchmark.out

range_benchmark.out: benchmarks/range.cpp $(headers)
	$(CXX) -o $@ $(CXXFLAGS) -O3 $< -lbenchmark

clean:
	rm -f *.o *.out

.PHONY: default test benchmark clean
