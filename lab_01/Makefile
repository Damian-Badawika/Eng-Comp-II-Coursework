# file: lecture_10/GNUMakefile
#
# Note that this make file uses "-g" to compile and link "debug".
#

# define a target for the application
#
all: lab_01.exe

# define a target to link the application
#
lab_01.exe: lab_01.o 
	g++ -g -lm lab_01.o -o lab_01.exe

# define targets to compile the source code
#
lab_01.o: lab_01.cpp Makefile
	g++ -g -c lab_01.cpp -o lab_01.o

# define a target to clean the directory
#
clean:
	rm -f lab_01.o lab_01.exe

#
# end of file


