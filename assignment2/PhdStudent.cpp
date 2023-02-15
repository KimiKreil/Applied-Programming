#include "PhdStudent.hpp"

// Constructor that specifies all elements, assumes full-time
PhdStudent::PhdStudent(std::string name, double fines, double fees, bool fullTime){
    (*this).name = name;
    tuition_fees = fees;
    (*this).fullTime = true;

    SetLibraryFines(fines);
}

// Function that returns the amount of money owed
double PhdStudent::MoneyOwed() const{
    // phd students dont owe anything
    return 0;
}

// Extra
void PhdStudent::print() const{
    std::cout << "Phd Student."
              << "\nname: " << name
              << "\ntuition fees: " << tuition_fees
              << "\nlibrary fines: " << GetLibraryFines()
              << "\ntotal amount owed: " << MoneyOwed()
              << "\nfull time: " << fullTime
              << "\n\n";
}
