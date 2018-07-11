// commands class
// rev0 7/08/18 by Ryan Breitenfeldt

#include<string>
#include<iostream>

#include"pushdownautomata.hpp"
#include"inputstrings.hpp"
#include"configurationsettings.hpp"

using namespace std;


class Commands{

    private:
        char command;
        string pdaName;
        string definitionFileName;
        string stringFileName;
        bool valid;
        bool pdaLoaded;

        PushdownAutomata pda;
        InputStrings strings;
        ConfigurationSettings config;
        

    public:
        Commands(string fileName);
        void help();
        void show();
        void view();
        void list();
        void insert();
        void deleteString();
        void set();
        void truncate();
        void run();
        void quit();
        void exit();
        void open();
        void close();
        void display();
        void sort();
        void inputCommand();

};