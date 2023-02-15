#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF

#include <string>
class Exception	{
	private:
		std::string mTag, mProblem;
	public:
		Exception(std::string tagString, std::string probString);
		void PrintDebug() const;

		// Add methods to access the private members
		void setProb(std::string prob);
		void setTag(std::string tag);
		std::string getProb() const;
		std::string getTag() const;
};

#endif //EXCEPTIONDEF
