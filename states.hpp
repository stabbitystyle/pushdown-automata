// States class
// Rev0 7/4/18 by William Frank

#ifndef STATES_HPP
#define STATES_HPP

#include <string>
#include <vector>
#include <fstream>

using namespace std;

// The class States is a class which is responsible for storing all of the possible states for the pushdown automaton.
class States
{
    private:
        vector<string> names;
    public:
        void load(ifstream& definition, bool& valid);
        void view() const;
        bool isElement(const string value) const;
};

#endif