# Define variables, standard things used for the compilation
.SUFFIXES: .cpp .o
CC = clang++
CFLAGS = -I. #did not work with -g here
EXEC = test

# List of object files needed to build the executable
OBJS = ComplexNumber.o CalculateExponential.o Matrix2x2.o Student.o GraduateStudent.o PhdStudent.o Exception.o OutOfRangeException.o FileNotOpenException.o test.o 

# List of header files needed to build the executable
HEADERS = ComplexNumber.hpp CalculateExponential.hpp Matrix2x2.hpp Student.hpp GraduateStudent.hpp PhdStudent.hpp Exercise82.hpp Exception.hpp OutOfRangeException.hpp FileNotOpenException.hpp

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
ComplexNumber.o: ComplexNumber.cpp ComplexNumber.hpp
CalculateExponential.o: CalculateExponential.cpp CalculateExponential.hpp
Matrix2x2.o: Matrix2x2.cpp Matrix2x2.hpp
Student.o: Student.cpp Student.hpp
GraduateStudent.o: GraduateStudent.cpp GraduateStudent.hpp
PhdStudent.o: PhdStudent.cpp PhdStudent.hpp
Exception.o: Exception.cpp Exception.hpp
OutOfRangeException.o: OutOfRangeException.cpp OutOfRangeException.hpp
FileNotOpenException.o: FileNotOpenException.cpp FileNotOpenException.hpp

test.o: test.cpp ${HEADERS}

# Command to undo any compilation made so far
clean:
	rm -f ${EXEC} ${OBJS}