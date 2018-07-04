// Tape Alphabet class
// Rev0 7/4/18 by William Frank

#ifndef TAPEALPHABET_HPP
#define TAPEALPHABET_HPP

#include <vector>
#include <fstream>

using namespace std;

// The class TapeAlphabet is a class which is responsible for storing the tape alphabet and providing information about the tape alphabet.
class TapeAlphabet
{
    private:
        vector<char> alphabet;
    public:
        void load(ifstream& definition, bool& valid);
        void view() const;
        bool isElement(const char value) const;
};

#endif