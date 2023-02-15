// Include the header file
#include "5_3.h"

// Define function to swap pointers
void swap_pointer(double *a, double *b){

    // Create a temporary variable to store a's pointer in
    double temp = *a;

    // Swap a for b
    *a = *b;

    // Swap b for a
    *b = temp;

    return;

}


// Define function to swap references
void swap_ref(double &a, double &b){

    // Create a temporary new variable
    double temp;

    // Swap values for the adresses given
    temp = a;
    a = b;
    b = temp;

    return;
}