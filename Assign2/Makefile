#
# Assignment #2
# AUTHOR:  Matt Borek
#

CXX = g++
CXXFLAGS = -g -Wall -Werror -pedantic -std=c++20
PROGS = nfa
TESTS = nfa-in.1 nfa-in.2 nfa-in.3 nfa-in.4

all: $(PROGS) 

$(PROGS): $(PROGS).o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(PROGS).o: $(PROGS).cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean TESTS

test: all
	@for input in $(TESTS); do \
		echo "Testing $$input:"; \
		./$(PROGS) < $$input > $$input.out; \
		./$(PROGS).key < $$input > $$input.key; \
		diff $$input.key $$input.out > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "Pass"; \
		else \
			echo "Fail"; \
		fi; \
	done

clean:
	rm -rf *.o *.key *.out $(PROGS)
