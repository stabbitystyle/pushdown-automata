// Final States class
// Rev0 7/4/18 by William Frank

#ifndef FINALSTATES_HPP
#define FINALSTATES_HPP

#include <string>
#include <vector>
#include <fstream>

#include "states.hpp"

using namespace std;

// The class FinalStates is a class which is responsible for storing all of the final states for the pushdown automata.
class FinalStates
{
    private:
        vector<string> names;
    public:
        void load(ifstream& definition, bool& valid);
        void validate(const States& states, bool& valid) const;
        void view() const;
        bool isElement(const string value) const;
};

#endif