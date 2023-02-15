#include "ComplexNumber.hpp"
#include <cmath>

///////////////////////////////////////////////
// Code from the book, Listings 6.10, p. 120 //
///////////////////////////////////////////////

// Override default constructor
// Set real and imaginary parts to zero
ComplexNumber::ComplexNumber()
{
   mRealPart = 0.0;
   mImaginaryPart = 0.0;
}

// Constructor that sets complex number z=x+iy
ComplexNumber::ComplexNumber(double x, double y)
{
   mRealPart = x;
   mImaginaryPart = y;
}

// Method for computing the modulus of a
// complex number
double ComplexNumber::CalculateModulus() const
{
   return sqrt(mRealPart*mRealPart+
               mImaginaryPart*mImaginaryPart);
}

// Method for computing the argument of a
// complex number
double ComplexNumber::CalculateArgument() const
{
   return atan2(mImaginaryPart, mRealPart);
}

// Method for raising complex number to the power n
// using De Moivre's theorem - first complex
// number must be converted to polar form
ComplexNumber ComplexNumber::CalculatePower(double n) const
{
   double modulus = CalculateModulus();
   double argument = CalculateArgument();
   double mod_of_result = pow(modulus, n);
   double arg_of_result = argument*n;
   double real_part = mod_of_result*cos(arg_of_result);
   double imag_part = mod_of_result*sin(arg_of_result);
   ComplexNumber z(real_part, imag_part); 
   return z; 
}

// Overloading the = (assignment) operator
ComplexNumber& ComplexNumber::operator=(const ComplexNumber& z)
{
   mRealPart = z.mRealPart;
   mImaginaryPart = z.mImaginaryPart;
   return *this;
}

// Overloading the unary - operator
ComplexNumber ComplexNumber::operator-() const
{
   ComplexNumber w;
   w.mRealPart = -mRealPart;
   w.mImaginaryPart = -mImaginaryPart;
   return w;
}

// Overloading the binary + operator
ComplexNumber ComplexNumber::operator+(const ComplexNumber& z) const
{
   ComplexNumber w;
   w.mRealPart = mRealPart + z.mRealPart;
   w.mImaginaryPart = mImaginaryPart + z.mImaginaryPart;
   return w;
}

// Overloading the binary - operator
ComplexNumber ComplexNumber::operator-(const ComplexNumber& z) const
{
   ComplexNumber w;
   w.mRealPart = mRealPart - z.mRealPart;
   w.mImaginaryPart = mImaginaryPart - z.mImaginaryPart;
   return w;
}

// Overloading the insertion << operator
std::ostream& operator<<(std::ostream& output, const ComplexNumber& z)
{
   // Format as "(a + bi)" or as "(a - bi)"
   output << "(" << z.mRealPart << " ";
   if (z.mImaginaryPart >= 0.0)
   {
      output << "+ " << z.mImaginaryPart << "i)";
   }
   else
   {
      // z.mImaginaryPart < 0.0
      // Replace + with minus sign 
      output << "- " << -z.mImaginaryPart << "i)";
   }
   return output;
}


//////////////////////////////
//       The Exercise       //
//////////////////////////////

// --- Exercise 6.1.1: allow acces to the private members real part and imaginary part --- //
double ComplexNumber::GetRealPart() const{
    return mRealPart;
}

double ComplexNumber::GetImaginaryPart() const{
    return mImaginaryPart;
}


// --- Exercise 6.1.2: Friend functions RealPart and ImaginaryPart --- //
double RealPart(const ComplexNumber &z){
    return z.mRealPart;
}

double ImaginaryPart(const ComplexNumber &z){
    return z.mImaginaryPart;
}


// --- Exercise 6.1.3 + 6.1.4: An overidden copy constructor --- //
// See the book p. 112 for notes on a copy constructor

// Overridden copy constructor (mimics system version)
ComplexNumber::ComplexNumber(const ComplexNumber& z){
    mRealPart = z.GetRealPart();
    mImaginaryPart = z.GetImaginaryPart();
}

// Specialised constructor, that initilises as with a real number
ComplexNumber::ComplexNumber(double real){
    mRealPart = real;
    mImaginaryPart = 0.0;
}


// --- Exercise 6.1.5: the method CalculateConjugate --- //
ComplexNumber ComplexNumber::CalculateConjugate() const{
    return ComplexNumber(mRealPart, -mImaginaryPart);
}


// --- Exercise 6.1.6: the method SetToConjugate with a void type --- //
// THE NAME WAS CHANGED FROM SETTOCONJUGATE IN THE BOOK DESCRIPTION TO SETCONJUGATE HERE --> POTENTIAL ERROR
void ComplexNumber::SetConjugate(){
    mImaginaryPart = -mImaginaryPart;
}

// --- Not mandatory (Helper function for Exercise 6.1.7) --- //
ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const{
    /* 
    Following the rule: (a+ib)(c+id) = (ac-bd) + i(ad+bc), where w=(a+ib) and z=(c+id)
    z can be accesed through z.method and w has the members mRealPart and mImaginaryPart 
    */

    // Real part = (ac-bd)
    double NewRealPart = mRealPart * z.GetRealPart() - mImaginaryPart * z.GetImaginaryPart();
    
    // Imaginary part = (ad+bc)
    double NewImaginaryPart = mRealPart * z.GetImaginaryPart() + mImaginaryPart * z.GetRealPart();

    return ComplexNumber(NewRealPart, NewImaginaryPart);
}

// --- Not mandatory (Helper function for Exercise 6.1.7) --- //
ComplexNumber ComplexNumber::operator/(const ComplexNumber& z) const{
   /* 
   Following the rule in https://www.cuemath.com/numbers/division-of-complex-numbers/
   (a+ib)/(c+id) = (ac+bd)/(c^2+d^2) + i * (bc-ad)/(c^2+d^2)
   w = (a+ib) and z=(c+id). z can be accesed through z.method and w has the members mRealPart and mImaginaryPart
   */

   // Denominator = (c^2+d^2)
   double denom = pow(z.GetRealPart(),2) + pow(z.GetImaginaryPart(),2);

   // Real part = (ac+bd)/(c^2+d^2)
   double NewRealPart = ( mRealPart * z.GetRealPart() + mImaginaryPart * z.GetImaginaryPart() ) / denom;

   // Imaginary part = (bc-ad)/(c^2+d^2)
   double NewImaginaryPart = ( mImaginaryPart * z.GetRealPart() - mRealPart * z.GetImaginaryPart() ) / denom;

   return ComplexNumber(NewRealPart, NewImaginaryPart);
}
