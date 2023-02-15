#include <iostream>
#include "Exception.hpp"

// Constructor
Exception::Exception(std::string tagString, std::string probString){
    mTag = tagString;
    mProblem = probString;
}

// Printing debug information
void Exception::PrintDebug() const{
    std::cerr << "** Error ("<<mTag<<") **\n";
    std::cerr << "Problem: " << mProblem << "\n\n";
}


void Exception::setProb(std::string prob)
{
    mProblem = prob;
}

std::string Exception::getProb() const
{
    return mProblem;
}

void Exception::setTag(std::string tag)
{
    mTag = tag;
}

std::string Exception::getTag() const
{
    return mTag;
}