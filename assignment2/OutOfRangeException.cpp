#include "OutOfRangeException.hpp"

// Overridden default constructor [see book p. 131]
// The tag is set in the default parent class constructor, 
// the problemstring is set to unspecified, and afterwards overridden with the input
OutOfRangeException::OutOfRangeException(std::string probString) : Exception("RANGE", "unspecified") {
    setProb(probString);
}

