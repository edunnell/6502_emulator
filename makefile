#
# A minimal g++ Makefile
# for more info see: https://www.gnu.org/software/make/manual/
#

all : cpu

run: all
	./cpu

CPPFLAGS=-std=c++11

tablegen : tablegen.o
	g++ -o $@ $^

# build the source code file for 6502 instructions
# by parsing the txt file
# we are dependent on tablegen, so if it's not build
# it will build first
instructions.cpp : 6502-opcodes.txt tablegen
	./tablegen < 6502-opcodes.txt > $@

cpu : cpu.o instructions.o
	g++ -o $@ $^

clean:
	rm -f *.o tablegen cpu

# manual dependencies
cpu.cpp : cpu.h
instructions.cpp : instructions.h
