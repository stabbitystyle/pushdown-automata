// commands class
// rev0 7/08/18 by Ryan Breitenfeldt

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iostream>
#include <stdlib.h>

#include "inputstrings.hpp"
#include "configurationsettings.hpp"

using namespace std;

// needed to forward declare PushdownAutomata for stuff to work
class PushdownAutomata;

// The Commands class is a class which is responsible for handling the user input and then performing the requested actions through other classes.
class Commands{
    private:
        char command;
        string pdaName;
        string definitionFileName;
        string stringFileName;
        string configFileName;
        bool valid;
        bool pdaLoaded;

        PushdownAutomata * pda;
        InputStrings strings;
        ConfigurationSettings config;
    public:
        Commands();
        Commands(string fileName);
        void help();
        void show();
        void view();
        void list();
        void insert();
        void deleteString();
        void set();
        void truncate();
        string run();
        void quit();
        void exit();
        void open();
        void close();
        void display();
        void sort();
        void inputCommand();
};
typedef Commands* CommandsPointer;

#endif