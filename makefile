# Author: Drew Hans (github.com/drewhans555)
# Description: This is a make file for C-AwayWithExtendedASCII

# CC variable holds our choosen C-Compiler
CC=gcc

# src variable collects all source files in the current directory
src = $(wildcard *.c)

# FLAGS holds the flags we want to pass into CC
FLAGS = -Wall

# @ is a built-in make variable containing the target of each rule (cawayextendedascii in this case)
# ^ is another built-in variable containing all the dependencies of each rule (src variable in this case)
# We substitute the value of any variable (built-in or not) by prepending $ to its name (in make, unlike 
# BASH, only the first character following $ is considered to be the variable name. If you want to use
# longer names, we have to parenthesize the name before applying the dollar sign to extract its value).
cawayextendedascii: $(src)
	$(CC) $(FLAGS) $(^) -o $(@)

# adds a rule for cleaning up every target, in order to rebuild the whole program from scratch
.PHONY: clean
clean:
	rm -f cawayextendedascii

# the clean rule is marked as phony because its target is not an actual file that will be generated, it's
# just an arbitrary name that we wish to use for executing this rule. To clean everything in this example
# just type: make clean
