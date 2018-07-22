// commandsinoperation class
// rev0 7/12/18 by Ryan Breitenfeldt


#ifndef COMMANDSINOPERATION_HPP
#define COMMANDSINOPERATION_HPP

#include<iostream>
#include"commands.hpp"
#include"inputstrings.hpp"
#include"configurationsettings.hpp"

using namespace std;

class PushdownAutomata;

class CommandsInOperation : public Commands
{
    private:
        PushdownAutomata * pda;

    public:
        void link(PushdownAutomata * linker);
        void run(); 
        void quit(); 
        void exit(); 
        void open(); 
        void close(); 
        void inputCommand();
};


#endif
