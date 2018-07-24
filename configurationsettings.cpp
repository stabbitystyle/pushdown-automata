// configurationsetting class
// rev0 7/06/18 by Ryan Breitenfeldt

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include "configurationsettings.hpp"
#include "uppercase.hpp"

using namespace std;

// The method getMaximumNumberOfTransitions returns the maxiumumNumberOfTransitions attribute.
int ConfigurationSettings::getMaximumNumberOfTransitions(){
    return maximumNumberOfTransitions;
};

// The method getMaximumNumberOfCells returns the maximumNumberOfCells attribute.
int ConfigurationSettings::getMaximumNumberOfCells(){
    return maximumNumberOfCells;
};

// The method getDisplayFullPath returns the displayFullPath attribute.
string ConfigurationSettings::getDisplayFullPath(){
    if (displayFullPath)
    {
        return "Yes";
    }
    else
    {
        return "No";
    }
};

// The method setMaximumNumberOfTransitions accepts an integer maximumNumberOfTransitionsInput and sets the attribute maximumNumberOfTransitions equal to it.
void ConfigurationSettings::setMaximumNumberOfTransitions(int maximumNumberOfTransitionsInput){
    if(maximumNumberOfTransitionsInput>0){
        maximumNumberOfTransitions = maximumNumberOfTransitionsInput;
    }
};

// The method setMaximumNumberOfCells accepts an integer maximumNumberOfCellsInput and sets the attribute maximumNumberOfCells equal to it.
void ConfigurationSettings::setMaximumNumberOfCells(int maximumNumberOfCellsInput){
    if(maximumNumberOfCellsInput>0){
        maximumNumberOfCells = maximumNumberOfCellsInput;
    }
};

// The method toggleDisplayFullPath sets the attribute displayFullPath depending on what it is currently. If it is "yes" then it will set it to "no" and vis-versa.
void ConfigurationSettings::toggleDisplayFullPath(){
    if(displayFullPath)
    {
        displayFullPath = false;
    }else{
        displayFullPath = true;
    }
};

//this method loads the config file for the pushdown automaton
//and sets defaults if any are wrong or missing 
void ConfigurationSettings::load(){

    //string filename = "pda.cfg";
    ifstream config("pda.cfg");
    string configline;
    size_t found;
    bool tranNotFound = true;
    bool displayNotFound = true;
    bool charNotFound = true;
    bool firstNumFound = false;
    bool spaceAfterNum = false;
    bool invalidString = false; 
    string chartest ="";
    string transtest = "";
    string maxChar = "MAXIMUM_CHARACTERS";
    string maxTrans = "MAXIMUM_TRANSITIONS";
    string test = "";

    //set the defaults
    maximumNumberOfCells=32;
    maximumNumberOfTransitions=1;
    displayFullPath=false;

    //config.open(filename.c_str());

    if(config.is_open()){
        while(!config.eof())
        {
            getline(config,configline);

            //convert to uppercase
            configline = uppercase(configline);

            // remove whitespace here
            //configline.erase(remove(configline.begin(), configline.end(), ' '), configline.end());


            found = configline.find("=");
            //cheak for a  = sign on the line
            if(found != string::npos){

                //checks for the number of transitions setting
                found = configline.find("MAXIMUM_TRANSITIONS");
                if(found != string::npos){
                    //configline.erase(remove(configline.begin(), configline.end(), ' '), configline.end());
                    found = configline.find("=");
                    if(found+1 != configline.length()){

                        test = configline.substr(0,found-1);
                        test.erase(remove(test.begin(), test.end(), ' '), test.end());
                        if(test.length() != maxTrans.length()-1){
                            test = "";
                            continue;
                        }


                        //gives you a string of everything after the = sign
                        configline = configline.substr(found+1,configline.length()-1);
                        //cheaks if there are any letters mixed with the numbers
                        if(configline.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ,./<>?;':\"[]{}\\!@#$^&*()_+-=%") != string::npos){
                            continue;
                        }

                        //reset cheack conditions 
                        firstNumFound = false;
                        spaceAfterNum = false;

                        // checks if any spaces or letters are mixed in with numbers
                        // if it finds a space in middle of the number it will invalidate the string
                        for(string::size_type i=0;i<(configline.length())-1;i++){
                            if(isdigit(configline[i])  && !firstNumFound){
                                firstNumFound = true;
                            
                            }
                            if(isdigit(configline[i]) && firstNumFound && spaceAfterNum){
                                invalidString = true;
                                break;
                            }
                            if(isspace(configline[i]) && firstNumFound){
                                spaceAfterNum = true;
                            }
                        }

                        /*for(int index = 0; index <(int)configline.length()-1;index++){
                            if(isdigit(configline[index])){
                                configline = configline.substr(index, configline.length()-1);
                                break;
                            }
                        }
                        for(int index =(int)configline.length(); index>0;index--){
                            if(isdigit(configline[index])){
                                configline = configline.substr(0, index);
                                break;
                            }
                        }
                        for(int index =0;index <(int)configline.length()-1;index++){
                            if(!isdigit(configline[index])){
                                invalidString = true;
                                break;
                            }
                        }
                        //configline = configline.substr(configline.find_first_of("1234567890"),configline.find_last_of("1234567890"));
                        if(configline.find_first_of(" ") != string::npos){
                            continue;
                        }*/

                        // skips the line
                        if(invalidString){
                            invalidString = false;
                            continue;
                        }
                        
                        if(tranNotFound && (stoi(configline,nullptr) > 0)){
                            maximumNumberOfTransitions= stoi(configline,nullptr);
                            tranNotFound = false;
                        }
                    }
                }

                //cheaks for the charaters to truncate setting
                found = configline.find("MAXIMUM_CHARACTERS");
                if(found != string::npos){
                    //configline.erase(remove(configline.begin(), configline.end(), ' '), configline.end());
                    found = configline.find("=");
                    if(found+1 != configline.length()){

                        test = configline.substr(0,found-1);
                        test.erase(remove(test.begin(), test.end(), ' '), test.end());
                        if(test.length() != maxChar.length()-1){
                            test = "";
                            continue;
                        }


                        //gives you a string of everything after the = sign
                        configline = configline.substr(found+1,configline.length()-1);

                        //checks if there are any letters mixed with the numbers
                        if(configline.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ,./<>?;':\"[]{}\\!@#$^&*()_+-=%") != string::npos){
                            continue;
                        }

                        //reset cheack conditions 
                        firstNumFound = false;
                        spaceAfterNum = false;

                        //cheaks if is any spaces or letters mixed in with numbers
                        // if it finds a space in middle of the number is will invalidate the string
                        for(string::size_type i=0;i<(configline.length())-1;i++){
                            if(isdigit(configline[i])  && !firstNumFound){
                                firstNumFound = true;
                            
                            }
                            if(isdigit(configline[i]) && firstNumFound && spaceAfterNum){
                                invalidString = true;
                                break;
                            }
                            if(isspace(configline[i]) && firstNumFound){
                                spaceAfterNum = true;
                            }
                        }


                        /*for(int index = 0; index < (int)configline.length()-1;index++){
                            if(isdigit(configline[index])){
                                configline = configline.substr(index, configline.length()-1);
                                break;
                            }
                        }
                        for(int index =(int)configline.length(); index>0;index--){
                            if(isdigit(configline[index])){
                                configline = configline.substr(0, index);
                                break;
                            }
                        }
                        for(int index =0;index <(int)configline.length()-1;index++){
                            if(!isdigit(configline[index])){
                                invalidString = true;
                                break;
                            }
                        }

                        //configline = configline.substr(configline.find_first_of("1234567890"),configline.find_last_of("1234567890"));

                        if(configline.find_first_of(" ") != string::npos){
                            continue;
                        }

                        //skips the  line
                        if(invalidString){
                            invalidString = false;
                            continue;
                        }*/

                        if(charNotFound && (stoi(configline,nullptr) > 0)){
                            maximumNumberOfCells= stoi(configline, nullptr);
                            charNotFound = false;
                        }
                    }
                }

                //cheaks for the display paths setting 
                found = configline.find("COMPLETE_PATHS");
                if(found != string::npos){
                    found = configline.find("YES");
                    if(found != string::npos && displayNotFound){
                        displayFullPath=true;
                        displayNotFound = false;
                        
                    }
                    found = configline.find("NO");
                    if(found != string::npos && displayNotFound){
                        displayNotFound = false;
                    }
                }
            }
        }
    }
};

// The method writeFile will write the configuration settings to a file.
// The name of the file is the name of the application with ".cfg" appended to it.
// It will put each setting on its own line with no whitespace.
// It will also overwrite any existing configuration file.  
void ConfigurationSettings::writeFile(){
    ofstream configFile("pda.cfg");

    if(configFile.is_open()){

        string yes ="yes";
        string no = "no";
        
        configFile << "MAXIMUM_TRANSITIONS=" << maximumNumberOfTransitions << endl;
        configFile << "MAXIMUM_CHARACTERS=" << maximumNumberOfCells << endl;
        if(displayFullPath){
            configFile << "COMPLETE_PATHS=" << yes << endl;
        }else{
            configFile << "COMPLETE_PATHS=" << no << endl;
        }
        
    }
};