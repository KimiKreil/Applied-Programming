#include "Student.hpp"
#include <cassert>

// Default constructor
Student::Student(){
    
    name = "unassigned";
    tuition_fees = 0;
    library_fines = 0;
}

// Constructor, assigning all members
Student::Student(std::string name, double fines, double fees){
    // use (*this) to refer to a given instance of the class. Then we can
    // differentiate between the class member "name" and the argument of the
    // constructor "name".
    (*this).name = name;
    tuition_fees = fees;
    library_fines = fines;
}

// Function to specify the library fine, only accepts a positive amount, 
void Student::SetLibraryFines(double amount){

    // Set amount to zero, if negative
    if (amount < 0.0){
        return;
    }

    library_fines = amount;
}

// Function to acces private member, library fines
double Student::GetLibraryFines() const{
    return library_fines;
}

// Function that returns the amount of money owed
double Student::MoneyOwed() const{
    return library_fines + tuition_fees;
}

// Extra - more convenient to test behaviour
void Student::print() const{
    std::cout << "Student."
              << "\nname: " << name
              << "\ntuition fees: " << tuition_fees
              << "\nlibrary fines: " << library_fines
              << "\ntotal amount owed: " << MoneyOwed()
              << "\n\n";
}
