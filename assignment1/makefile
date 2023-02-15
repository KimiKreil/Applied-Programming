# Define variables, standard things used for the compilation
.SUFFIXES: .cpp .o
CC = clang++
CFLAGS = -I. #did not work with -g here
EXEC = test
OBJS = 2_6.o 3_3.o 5_3.o 5_4.o 5_6.o 5_9.o 5_10.o test.o # List of object files needed to build the executable
HEADERS = 2_6.h 3_3.h 5_3.h 5_4.h 5_6.h 5_9.h 5_10.h # List of header files needed to build the executable

# Execute the cpp files
# More general way of doing test:
${EXEC}: ${OBJS}
	${CC} ${CFLAGS}-o ${EXEC} ${OBJS}

# Execute the cpp files, creating the exectuable .o files
# Allowing for not having to recompile everything since the abstract rule $< indicates the dependencies that changed
# More general way of doing test.o:
.cpp.o: # Abstract rule 
	${CC} ${CFLAGS}-c $<

# Still need to list the dependencies for object files
2_6.o: 2_6.cpp 2_6.h
3_3.o: 3_3.cpp 3_3.h
5_3.o: 5_3.cpp 5_3.h
5_4.o: 5_4.cpp 5_4.h
5_6.o: 5_6.cpp 5_6.h
5_9.o: 5_9.cpp 5_9.h
5_10.o: 5_10.cpp 5_10.h

test.o: test.cpp ${HEADERS}

# Command to undo any compilation made so far
clean:
	rm -f ${EXEC} ${OBJS}