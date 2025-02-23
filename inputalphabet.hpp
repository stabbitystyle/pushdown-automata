// Input Alphabet class
// Rev0 7/4/18 by William Frank

#ifndef INPUTALPHABET_HPP
#define INPUTALPHABET_HPP

#include <vector>
#include <fstream>
#include <string>

#include "stackalphabet.hpp"

using namespace std;

// The class InputAlphabet is a class which is responsible for storing the input alphabet and providing information about the input alphabet.
class InputAlphabet
{
    private:
        vector<char> alphabet;
    public:
        void load(ifstream& definition, string& value, bool& valid);
        void view() const;
        bool isElement(const char value) const;
};

#endif