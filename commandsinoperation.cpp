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

void CommandsInOperation::run(){
    //dont know what this should do
}
void CommandsInOperation::quit(){
    //CommandsInOperation::pda->endRecrustion("quit");

    //CommandsInOperation::pda->terminateOperation();
    //CommandsInOperation::pda->setCalledCommand("quit");


}
void CommandsInOperation::exit(){
    //CommandsInOperation::pda->endRecrustion("exit");

    //CommandsInOperation::pda->terminateOperation();
    //CommandsInOperation::pda->setCalledCommand("exit");

}
void CommandsInOperation::open(){
    //CommandsInOperation::pda->endRecrustion("open");

    //CommandsInOperation::pda->terminateOperation();
    //CommandsInOperation::pda->setCalledCommand("open");
} 
void CommandsInOperation::close(){
    //CommandsInOperation::pda->endRecrustion("close");

    //CommandsInOperation::pda->terminateOperation();
    //CommandsInOperation::pda->setCalledCommand("close");

}
 void CommandsInOperation::link(Commands& linker){
     commandsPointer = &linker; 
 }
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
                CommandsInOperation::close();
                keeplooping = false;
                return "close";
               
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
                CommandsInOperation::exit();
                keeplooping = false;
                return "exit";
                   
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
                CommandsInOperation::open();
                keeplooping = false;
                return "open";
                    
                break;
            }
            // Quit
            case 'Q':
            case 'q':
            {
                CommandsInOperation::quit();
                keeplooping = false;
                return "quit";

                   
                break;
            }
            // Run
            case 'R':
            case 'r':
            {
                CommandsInOperation::run();
                keeplooping = false;
                return "run";
                    
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
    return "";
}





