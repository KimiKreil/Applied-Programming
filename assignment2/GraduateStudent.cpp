#include "GraduateStudent.hpp"

// Default constructor
GraduateStudent::GraduateStudent(){
    name = "unassigned";
    tuition_fees = 0;
    fullTime = true;

    // Library fines are private in the parent class (Student), so we set it through a method
    SetLibraryFines(0);
}

// Constructor assigning all members
GraduateStudent::GraduateStudent(std::string name, double fines, double fees, bool fullTime){
    (*this).name = name;
    SetLibraryFines(fines);
    tuition_fees = fees;
    (*this).fullTime = fullTime;

}

// Function that returns the amount of money owed
double GraduateStudent::MoneyOwed() const{
    // Override function of parent class since graduate students don't pay tuition fees
    return GetLibraryFines();
}

// Extra for convenience
void GraduateStudent::print() const{
    std::cout << "Graduate Student."
              << "\nname: " << name
              << "\ntuition fees: " << tuition_fees
              << "\nlibrary fines: " << GetLibraryFines()
              << "\ntotal amount owed: " << MoneyOwed()
              << "\nfull time: " << fullTime
              << "\n\n";
}