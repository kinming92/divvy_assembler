# A simple makefile for this program
#use g++ for everything

CC= g++

# include debugging symbols in object files,
# and enable all warnings

FLAGS= -g -Wall -std=c++11

HEADERS= somecode.h

all: sub_8bit

sub: sub_8bit.o
        $(CC) $(FLAGS) -o sub_8bit sub_8bit.o

main: main.o $($HEADERS)
        $(CC) $(FLAGS) -o main main.o $(HEADERS)

main.o: $(BSTHPP)
        $(CC) $(FLAGS) -c main.cpp

sub_8bit.o: sub_8bit.cpp
        $(CC) $(FLAGS) -c sub_8bit.cpp

clean:
        $(RM) main sub_8bit *.o
