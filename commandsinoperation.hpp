// commandsinoperation class
// rev0 7/12/18 by Ryan Breitenfeldt

#ifndef COMMANDSINOPERATION_HPP
#define COMMANDSINOPERATION_HPP

#include <iostream>
#include "commands.hpp"
#include "inputstrings.hpp"
#include "configurationsettings.hpp"

using namespace std;

// needed to forward declare PushdownAutomata for stuff to work
class PushdownAutomata;

// The class CommandsInOperation is inherited from the class Commands.
// This class is responsible for handling the user input and then performing the requested actions while in the recursion of the running the Pushdown Automation.
// Some of the methods in this class must unwind from the recursion.
class CommandsInOperation : public Commands
{
    private:
        static CommandsPointer commandsPointer;
    public:
        void link(Commands& linker);
        string inputCommand();
};

#endif
