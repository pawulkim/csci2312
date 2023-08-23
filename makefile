# Make file for CSCI 2312

# In very simple terms, we are setting up aliases, and simple scripts that can quickly referenced and executed from the terminal.
# -------------------------------------------------------------------

# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target. A target is a keyword setup on the left side of a colon.
#   make clean  - removes all files generated by make.

# Flags passed to the preprocessor.
CPPFLAGS += -isystem

# Flags passed to the C++ compiler.
CXXFLAGS += --std=c++1414 -g -Wall -Wextra -pthread

INPUT = src/main.cpp


# House-keeping build targets.
all : main

main : $(INPUT)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


clean :
	# Cleaning intermediate and output files
	rm main
