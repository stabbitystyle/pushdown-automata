// commands class
// rev0 7/08/18 by Ryan Breitenfeldt

#include<string>
#include<iostream>
#include<iomanip>
#include<ctype.h>

#include"pushdownautomata.hpp"
#include"inputstrings.hpp"
#include"commands.hpp"
#include "intinput.hpp"
using namespace std;

Commands::Commands(){
    pda = 0;
    pdaLoaded = false;
    config.load(configFileName);
}


Commands::Commands(string fileName){
    pda = 0;
    pdaLoaded = false;
    config.load(configFileName);

    pdaName = fileName;
    definitionFileName = fileName + ".def";
    stringFileName = fileName + ".str";
    configFileName = fileName + ".cfg";
    pda = new PushdownAutomata(definitionFileName);
    if(pda->isValidDefinition()){
        pdaLoaded = true;
        strings.load(stringFileName, *pda);
        pda->link(config);
    }else{
		delete pda;
    }


}
void Commands::help(){
    const int helpWidth = 12;
    cout << endl;
    cout << right << setw(helpWidth) << "(C)lose  " << "Close a pushdown automata definition" << endl;
    cout << right << setw(helpWidth) << "(D)elete  " << "Delete input string from list" << endl;
    cout << right << setw(helpWidth) << "Dis(p)lay  " << "Display the complete paths through the pushdown automaton" << endl;
    cout << right << setw(helpWidth) << "E(x)it  " << "Exit application" << endl;
    cout << right << setw(helpWidth) << "(H)elp  " << "Help user" << endl;
    cout << right << setw(helpWidth) << "(I)nsert  " << "Insert input string into list" << endl;
    cout << right << setw(helpWidth) << "(L)ist  " << "List input strings" << endl;
    cout << right << setw(helpWidth) << "(O)pen  " << "Open a pushdown automata definition" << endl;
    cout << right << setw(helpWidth) << "(Q)uit  " << "Quit operation of pushdown automata on input string" << endl;
    cout << right << setw(helpWidth) << "(R)un  " << "Run pushdown automata on input string" << endl;
    cout << right << setw(helpWidth) << "S(e)t  " << "Set maximum number of transitions to perform" << endl;
    cout << right << setw(helpWidth) << "Sho(w)  " << "Show status of application" << endl;
    cout << right << setw(helpWidth) << "(S)ort  " << "Sort the strings in the input string list" << endl;
    cout << right << setw(helpWidth) << "(T)runcate  " << "Truncate instantaneous descriptions" << endl;
    cout << right << setw(helpWidth) << "(V)iew  " << "View pushdown automata" << endl;
    cout << endl;
}
void Commands::show(){
    const int showWidth = 34;
    cout << endl;
    cout << right << setw(showWidth) << "Course:  " << "CptS 422" << endl;
    cout << right << setw(showWidth) << "Semester:  " << "Summer" << endl;
    cout << right << setw(showWidth) << "Year:  " << "2018" << endl;
    cout << right << setw(showWidth) << "Instructor:  " << "Neil B. Corrigan" << endl;
    cout << right << setw(showWidth) << "Authors:  " << "Emmanuel Bonilla, Ryan Breitenfeldt, William Robert Frank," << endl;
    cout << right << setw(showWidth) << "  " << "Carlos Martinez, Mike Snyder, Cole Woodford" << endl;
    cout << right << setw(showWidth) << "Version:  " << "1.0" << endl;
    cout << endl;
    cout << right << setw(showWidth) << "Maximum Transitions Setting:  " << config.getMaximumNumberOfTransitions() << endl;
    cout << right << setw(showWidth) << "Truncate Width Setting:  " << config.getMaximumNumberOfCells() << endl;
    cout << right << setw(showWidth) << "Display Setting:  " << config.getDisplayFullPath() << endl;
    cout << endl;

    if(pdaLoaded){
        cout << right << setw(showWidth) << "Name of Pushdown Automata:  " << pdaName << endl;
        // If currently running, need to output input string and # of transitions performed so far
        // If completed, need to output input string, result, and # of transitions performed
        if(!pda->isUsed()){
            cout << right << setw(showWidth) << "The pushdown automata hasn’t been tested on a string yet." << endl;
        }else if(pda->isOperating()){
            cout << right << setw(showWidth) << "Current Input String:  " << pda->inputString() << endl;
            cout << right << setw(showWidth) << "Result of Test:  " << "currently running" << endl;
            cout << right << setw(showWidth) << "Number of Transitions Performed:  " << pda->totalNumberOfTransitions() << endl;
            cout << right << setw(showWidth) << "Number of Crashes:  " << pda->totalNumberOfCrashes() << endl;

        }else if(pda->isAcceptedInputString()){
            cout << right << setw(showWidth) << "Result of Test:  " << "Accepted" << endl;
            cout << right << setw(showWidth) << "Number of Transitions Performed:  " << pda->totalNumberOfTransitions() << endl;
            cout << right << setw(showWidth) << "Number of Crashes:  " << pda->totalNumberOfCrashes() << endl;

        }else if(pda->isRejectedInputString()){
            cout << right << setw(showWidth) << "Result of Test:  " << "Rejected" << endl;
            cout << right << setw(showWidth) << "Number of Transitions Performed:  " << pda->totalNumberOfTransitions() << endl;
            cout << right << setw(showWidth) << "Number of Crashes:  " << pda->totalNumberOfCrashes() << endl;

        }else if(pda->isUsed() && !pda->isOperating() && !pda->isAcceptedInputString() && !pda->isRejectedInputString()){
            cout << right << setw(showWidth) << "Result of Test:  " << "Neither Accepted nor Rejected" << endl;
            cout << right << setw(showWidth) << "Number of Transitions Performed:  " << pda->totalNumberOfTransitions() << endl;
            cout << right << setw(showWidth) << "Number of Crashes:  " << pda->totalNumberOfCrashes() << endl;
        }        
    }else{
        cout << "No pushdown automata definition is currently loaded." << endl;
    }
    cout << endl;
}
void Commands::view(){
    cout << endl;

    if (pdaLoaded)
    {
        pda->viewDefinition();
    }
    else
    {
        cout << "Error: No pushdown automata definition is currently loaded." << endl;
        cout << endl;
    }
}
void Commands::list(){
    cout << endl;
    if(pdaLoaded){
        strings.view();
    }
    else
    {
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    cout << endl;
}
void Commands::insert(){
    string stringToAdd;
    std::cout << std::endl;
    if(pdaLoaded){
        cout << "Enter string to be added: ";
        getline(cin,stringToAdd);
        if(pda->isValidInputString(stringToAdd) && !strings.isElement(stringToAdd)){
            strings.addToStrings(stringToAdd);
        }else if(strings.isElement(stringToAdd)){
            cout << "Error: String was already in the string list." << endl;
        }
        else
        {
            cout << "Error: String contained symbols not found in the input alphabet." << endl;
        }
    }else{
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    cout << endl;
}
void Commands::deleteString(){
    string input;
    bool validString = true;

    std::cout << std::endl;

    if(pdaLoaded){
        cout << "Enter number of string in string file to be removed: ";
        getline(cin,input);

        for(string::size_type i = 0;i <input.length()-1;i++){
            if(!isdigit(input.at(i))){
                validString = false;
            }
        }

        if(validString && stoi(input,nullptr) <= strings.numberOfStrings() && stoi(input,nullptr) > 0){
            strings.removeFromStrings(stoi(input,nullptr));
        }else{
            cout << "Error: Invalid string number." << endl;
            cout << endl;
        }
    }else{
        cout << "Error: No pushdown automata definition currently loaded." << endl;
        cout << endl;
    }
}
void Commands::set(){
    int input;
    std::cout << std::endl;
    std::cout << "Set the maximum number of transitions[" << config.getMaximumNumberOfTransitions() << "]: ";
    if (intInput(input))
    {
        cout << endl;
        if (input < 1)
        {
            cout << "Error: Input was less than 1." << endl;
        }
        else
        {
            config.setMaximumNumberOfTransitions(input);
            cout << "Maximum number of transitions set to " << config.getMaximumNumberOfTransitions() << endl;
        }
    }
    cout << endl;
}
void Commands::truncate(){
    int input;
    std::cout << std::endl;
    std::cout << "Set the maximum number of characters to truncate[" << config.getMaximumNumberOfCells() << "]: ";
    if (intInput(input))
    {
        cout << endl;
        if (input < 1)
        {
            cout << "Error: Input was less than 1." << endl;
        }
        else
        {
            config.setMaximumNumberOfCells(input);
            cout << "Width to truncate the ID set to " << config.getMaximumNumberOfCells() << endl;
        }
    }
    cout << endl;
}
void Commands::run(){
    string input;
    bool validString = true;
    if(pdaLoaded){
        // int input needed here
        cout <<  "Enter number of string in string file to run: ";
        getline(cin,input);

        for(string::size_type i = 0;i <input.length()-1;i++){
                if(!isdigit(input.at(i))){
                    validString = false;
            }
        }

        if(validString && stoi(input,nullptr) <= strings.numberOfStrings() && stoi(input,nullptr) > 0){

            pda->initialize(strings.getInputString(stoi(input,nullptr)));

        }else{
            cout << "Error: Invalid input string" << endl;
        }
    }else{
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }

}
void Commands::quit(){
    cout << endl;
    if (!pdaLoaded)
    {
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    else if (pda->isOperating())
    {
        cout << "When we get run working, we can then do this part. :| :|" << endl;
    }
    else
    {
        cout << "Error: The pushdown automaton is not currently operating on an input string." << endl;
    }
    cout << endl;
}
void Commands::exit(){
    config.writeFile(configFileName);
    if(pdaLoaded){
        strings.saveToFile(stringFileName);
        delete pda;
    }
}
void Commands::open(){
    if(pdaLoaded){
        pdaLoaded = false;
        delete pda;
        pda = 0;
        strings.saveToFile(stringFileName);
        stringFileName = "";
        definitionFileName = "";
        pdaName = "";
    }

    
    std::cout << std::endl;
    cout << "Enter the name of the pushdown automata: ";
    getline(cin,pdaName);
    definitionFileName = pdaName + ".def";
    stringFileName = pdaName + ".str";

    pda = new PushdownAutomata(definitionFileName);
    if(pda->isValidDefinition()){
        pdaLoaded = true;
        strings.load(stringFileName, *pda);
    }else{
        delete pda;
        pda = 0;
    }
}
void Commands::close(){
    if(pdaLoaded){
        pdaLoaded = false;
        delete pda;
        pda = 0;
        strings.saveToFile(stringFileName);
        stringFileName = "";
        definitionFileName = "";
        pdaName = "";
    }
    else
    {
        cout << endl;
        cout << "Error: No pushdown automata definition currently loaded." << endl;
        cout << endl;
    }
}
void Commands::display(){
    config.toggleDisplayFullPath();
    std::cout << std::endl;
    cout << "The Display Path setting is " << config.getDisplayFullPath() << endl;
    cout << endl;
}
void Commands::sort(){
    cout << endl;
    if(pdaLoaded){
        strings.sort();
    }
    else
    {
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    cout << endl;
}
void Commands::inputCommand(){

    string lineInput;
    char commandInput = 'z';
    
    
    
        
        
    cout << endl;
    while(commandInput != 'x' && commandInput != 'X')
    {
        cout << "Command: ";
        getline(std::cin, lineInput);
        // Only accept single character inputs
        if(lineInput.length() == 1)
        {
            commandInput = lineInput[0];
        }
        else
        {
            // Dummy character, unused in program, change if z becomes used
            commandInput = 'z';
        }
        switch(commandInput)
        {
            // Close
            case 'C':
            case 'c':
            {
                close();
               
                break;
            }
            // Delete
            case 'D':
            case 'd':
            {
                deleteString();
                    
                break;
            }
            // Display
            case 'P':
            case 'p':
            {
                display();
                
                break;
            }
            // Exit
            case 'X':
            case 'x':
            {
                exit();
                   
                break;
            }
            // Help
            // commands in alphabetical order
            case 'H':
            case 'h':
            {
                help();
                    
                break;
            }
            // Insert
            case 'I':
            case 'i':
            {
                insert();
                    
                break;
            }
            // List
            case 'L':
            case 'l':
            {
                list();
                    
                break;
            }
            // Open
            case 'O':
            case 'o':
            {
                open();
                    
                break;
            }
            // Quit
            case 'Q':
            case 'q':
            {
                quit();
                   
                break;
            }
            // Run
            case 'R':
            case 'r':
            {
                run();
                    
                break;
            }
            // Set
            case 'E':
            case 'e':
            {
                set();
                    
                break;
            }
            // Show
            case 'W':
            case 'w':
            {
                show();
                
                break;
            }
            // Sort
            // sorts first by length (shortest first) then ascii value (lowest first)
            case 'S':
            case 's':
            {
                sort();
                    
                break;
            }
            // Truncate
            case 'T':
            case 't':
            {
                   truncate();
                break;
            }
            // View
            case 'V':
            case 'v':
            {   
                view();
                   
                break;
            }
                // Invalid character, multiple characters, or no characters
            default:
            {
                break;
            }
         }
    }
}

