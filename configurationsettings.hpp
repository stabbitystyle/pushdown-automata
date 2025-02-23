// configurationsetting class
// rev0 7/06/18 by Ryan Breitenfeldt

#ifndef CONFIGURATIONSETTINGS_HPP
#define CONFIGURATIONSETTINGS_HPP

#include<string>
#include<fstream>
#include<iostream>

using namespace std;

// The class ConfigurationSettings is responsible for loading, storing, setting, and getting the three configuration values for the Pushdown Automaton.
class ConfigurationSettings
{
    private:
        int maximumNumberOfTransitions;
        int maximumNumberOfCells;
        bool displayFullPath;

    public:
        int getMaximumNumberOfTransitions();
        int getMaximumNumberOfCells();
        string getDisplayFullPath();
        void setMaximumNumberOfTransitions(int maximumNumberOfTransitionsInput);
        void setMaximumNumberOfCells(int maximumNumberOfCellsInput);
        void toggleDisplayFullPath();
        void load();
        void writeFile();
};
typedef ConfigurationSettings* ConfigurationSettingsPointer;

#endif