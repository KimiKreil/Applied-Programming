#include "FileNotOpenException.hpp"

// Overridden default constructor [see book p. 131]
// The tag is set in the default parent class constructor, 
// the problemstring is set to unspecified, and afterwards overridden with the input
FileNotOpenException::FileNotOpenException(std::string probString) : Exception("FILE", "unspecified") {
    setProb(probString);
}
