CXX = g++
LD = g++

IFLAGS = -Iinclude
WFLAGS = -Wall -Wextra -Wpedantic -Wshadow
CXXFLAGS = -std=c++20 $(IFLAGS) $(WFLAGS) -g

headers = include/range.hpp

default: test

test: range_test.out
	./range_test.out

range_test.out: test/range.cpp $(headers)
	$(CXX) -o $@ $(CXXFLAGS) $< -lfmt

.PHONY: default test
