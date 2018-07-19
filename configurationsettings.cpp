// configurationsetting class
// rev0 7/06/18 by Ryan Breitenfeldt

#include<string>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<ctype.h>
#include"configurationsettings.hpp"
#include"uppercase.hpp"

using namespace std;

int ConfigurationSettings::getMaximumNumberOfTransitions(){
    return maximumNumberOfTransitions;
};
int ConfigurationSettings::getMaximumNumberOfCells(){
    return maximumNumberOfCells;
};
string ConfigurationSettings::getDisplayFullPath(){
    return displayFullPath;
};
void ConfigurationSettings::setMaximumNumberOfTransitions(int maximumNumberOfTransitionsInput){
    if(maximumNumberOfTransitionsInput>0){
        maximumNumberOfTransitions = maximumNumberOfTransitionsInput;
    }
};
void ConfigurationSettings::setMaximumNumberOfCells(int maximumNumberOfCellsInput){
    if(maximumNumberOfCellsInput>0){
        maximumNumberOfCells = maximumNumberOfCellsInput;
    }
};
void ConfigurationSettings::toggleDisplayFullPath(){
    if(displayFullPath.compare("yes"))
    {
        displayFullPath = "no";
    }else{
        displayFullPath = "yes";
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

    //set the defaults
    maximumNumberOfCells=32;
    maximumNumberOfTransitions=1;
    displayFullPath="no";

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

                //checks for the number of transitins setting

                found = configline.find("MAXIMUM_TRANSITIONS");
                if(found != string::npos){
                    //configline.erase(remove(configline.begin(), configline.end(), ' '), configline.end());
                    found = configline.find("=");
                    if(found+1 != configline.length()){

                        //gives you a string of everything after the = sign
                        configline = configline.substr(found+1,configline.length()-1);
                        //cheaks if there are any letters mixed with the numbers
                        if(configline.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos){
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
                        //skips the  line
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
                        //gives you a string of everything after the = sign
                        configline = configline.substr(found+1,configline.length()-1);

                        //cheaks if there are any letters mixed with the numbers
                        if(configline.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos){
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
                        //skips the  line
                        if(invalidString){
                            invalidString = false;
                            continue;
                        }

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
                        displayFullPath="yes";
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
void ConfigurationSettings::writeFile(){
    ofstream configFile("pda.cfg");

    if(configFile.is_open()){
        configFile << "MAXIMUM_TRANSITIONS=" << maximumNumberOfTransitions << endl;
        configFile << "MAXIMUM_CHARACTERS=" << maximumNumberOfCells << endl;
        configFile << "COMPLETE_PATHS=" << displayFullPath << endl;
    }
};