// configurationsetting class
// rev0 7/06/18 by Ryan Breitenfeldt

#ifndef CONFIGURATIONSETTINGS_HPP
#define CONFIGURATIONSETTINGS_HPP

#include<string>
#include<fstream>
#include<iostream>

using namespace std;

//class ConfigurationSettings
class ConfigurationSettings
{
    private:
        int maximumNumberOfTransitions;
        int maximumNumberOfCells;
        string displayFullPath;

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