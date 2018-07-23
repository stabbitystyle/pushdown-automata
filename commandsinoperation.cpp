// commandsinoperation class
// rev0 7/12/18 by Ryan Breitenfeldt

#include<iostream>
#include"commands.hpp"
#include"pushdownautomata.hpp"
#include"inputstrings.hpp"
#include"configurationsettings.hpp"
#include"commandsinoperation.hpp"

using namespace std;

CommandsPointer CommandsInOperation::commandsPointer = 0;

//this method link the commands class to commandsinoperation.
// this is done so we can get access to method that have access to the needed data.
 void CommandsInOperation::link(Commands& linker){
     commandsPointer = &linker;
 }


 //this method is the the command loop while the pda is running 
 // this will be called from inside isAccepted method in pushdown automata class
string CommandsInOperation::inputCommand(){

    string lineInput;
    char commandInput;
    bool keeplooping = true;

    cout << endl;
    while(keeplooping){
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
                
                keeplooping = false;
                return "close";
                break;
            }
            // Delete
            case 'D':
            case 'd':
            {
                commandsPointer->deleteString(); 
                break;
            }
            // Display
            case 'P':
            case 'p':
            {
                commandsPointer->display();
                break;
            }
            // Exit
            case 'X':
            case 'x':
            {
                
                keeplooping = false;
                return "exit";
                break;
            }
            // Help
            // commands in alphabetical order
            case 'H':
            case 'h':
            {
                commandsPointer->help();
                break;
            }
            // Insert
            case 'I':
            case 'i':
            {
                commandsPointer->insert();
                break;
            }
            // List
            case 'L':
            case 'l':
            {
                commandsPointer->list();
                break;
            }
            // Open
            case 'O':
            case 'o':
            {
                
                keeplooping = false;
                return "open";
                break;
            }
            // Quit
            case 'Q':
            case 'q':
            {
                
                keeplooping = false;
                return "quit";
                break;
            }
            // Run
            case 'R':
            case 'r':
            {
                
                keeplooping = false;
                return "run";
                break;
            }
            // Set
            case 'E':
            case 'e':
            {
                commandsPointer->set();  
                break;
            }
            // Show
            case 'W':
            case 'w':
            {
                commandsPointer->show();
                break;
            }
            // Sort
            // sorts first by length (shortest first) then ascii value (lowest first)
            case 'S':
            case 's':
            {
                commandsPointer->sort();   
                break;
            }
            // Truncate
            case 'T':
            case 't':
            {
                commandsPointer->truncate();
                break;
            }
            // View
            case 'V':
            case 'v':
            {   
                commandsPointer->view();
                break;
            }
                // Invalid character, multiple characters, or no characters
            default:
            {
                break;
            }
         }
    }
    return "";
}





