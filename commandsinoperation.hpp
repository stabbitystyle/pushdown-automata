// commandsinoperation class
// rev0 7/12/18 by Ryan Breitenfeldt


#ifndef COMMANDSINOPERATION_HPP
#define COMMANDSINOPERATION_HPP

#include<iostream>
#include"commands.hpp"
#include"pushdownautomata.hpp"
#include"inputstrings.hpp"
#include"configurationsettings.hpp"

using namespace std;

class CommandsInOperation : public Commands
{
    private:
        PushdownAutomata * pda;

    public:
        void run(); 
        void quit(); 
        void exit(); 
        void open(); 
        void close(); 
};


#endif
