#
# Assignment #1
# AUTHOR:  Matt Borek
#

CXX = g++
CXXFLAGS = -g -Wall -Werror -pedantic -std=c++20
PROGS = dfa
TESTS = dfa-in.1 dfa-in.2 dfa-in.3 dfa-in.4

all: $(PROGS) 

dfa: dfa.o
	$(CXX) $(CXXFLAGS) -o $@ $^

dfa.o: dfa.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean TESTS

test: all
	@for input in $(TESTS); do \
		echo "Testing $$input:"; \
		./dfa < $$input > $$input.out; \
		./dfa.key < $$input > $$input.key; \
		diff $$input.key $$input.out > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "Pass"; \
		else \
			echo "Fail"; \
		fi; \
	done

clean:
	rm -rf *.o *.key *.out $(PROGS)
