#ifndef SUBMISSION_STUDENT_HPP_
#define SUBMISSION_STUDENT_HPP_

#include <string>
#include <iostream>

class Student {
public:
	Student();
	Student(std::string name, double fines, double fees);

	std::string name;
	double tuition_fees;
	// Virtual keyword is a signal to the compiler that a method has the potential to be overridden by a derived class [p. 134 in book]
	virtual double MoneyOwed() const; 
	void SetLibraryFines(double amount);
	double GetLibraryFines() const;
	// I added the print function for convenience
	virtual void print() const;

private:
	double library_fines;
};



#endif /* SUBMISSION_STUDENT_HPP_ */
