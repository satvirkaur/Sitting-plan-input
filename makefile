expand = expand_main.o input.o
sort_rollno = sort_main.o input.o

CC = g++									# compiler variable
DEBUG = -g									# debugging flag 
CFLAGS = -Wall -c $(DEBUG)							# linking flag
LFLAGS = -Wall $(DEBUG)					  	  # flag used in compiling and creating object files	

all : expand sort_rollno




expand : $(expand)
	$(CC) $(LFLAGS) $(expand) -o expand
	
sort_rollno : $(sort_rollno)
	$(CC) $(LFLAGS) $(sort_rollno) -o sort_roll_no
 
expand_main.o : expand_main.cpp input.h input.in
	$(CC) $(CFLAGS) expand_main.cpp

input.o : input.cpp input.h 
	$(CC) $(CFLAGS) input.cpp
	
sort_main.o : sort_main.cpp input.h input_expand.out
	$(CC) $(CFLAGS) sort_main.cpp
