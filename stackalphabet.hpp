// Stack Alphabet class
// Rev0 7/4/18 by William Frank

#ifndef STACKALPHABET_HPP
#define STACKALPHABET_HPP

#include <vector>
#include <fstream>

using namespace std;

// The class StackAlphabet is a class which is responsible for storing the tape alphabet and providing information about the tape alphabet.
class StackAlphabet
{
    private:
        vector<char> alphabet;
    public:
        void load(ifstream& definition, bool& valid);
        void view() const;
        bool isElement(const char value) const;
};

#endif