// commands class
// rev0 7/08/18 by Ryan Breitenfeldt

#include<string>
#include<iostream>
#include<iomanip>
#include<ctype.h>
#include<stdlib.h>

#include"pushdownautomata.hpp"
#include"inputstrings.hpp"
#include"commands.hpp"
#include "intinput.hpp"
using namespace std;

// The method Commands is the defualt constructor for the Commands class.
// It loads in the configuration settings.
Commands::Commands(){
    pda = 0;
    pdaLoaded = false;
    config.load();
}

// The method Commands is the constructor for the Commands class.
// It accepts passedFileName String as a parameter.
// It appends the “.def” and “.str” strings to the file to put into the definitionFileName and stringFileName attributes respectively.
// It then goes about initializing the pushdown automata and checking that the definition file is valid through other class’ methods.
// Finally, it passes the stringFileName file to the InputStrings class to be parsed.
// It loads in the configuration settings.
Commands::Commands(string fileName){
    pda = 0;
    pdaLoaded = false;
    config.load();

    pdaName = fileName;
    definitionFileName = fileName + ".def";
    stringFileName = fileName + ".str";
    //configFileName = fileName + ".cfg";
    pda = new PushdownAutomata(definitionFileName, *this);
    if(pda->isValidDefinition()){
        pdaLoaded = true;
        strings.load(stringFileName, *pda);
        pda->link(config);
    }else{
		delete pda;
    }
}

// The method help displays help text for the user.
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

// The method shows displays program information for the user including configuration settings and Pushdown Automaton status.
void Commands::show(){
    const int showWidth = 34;
    cout << endl;
    cout << right << setw(showWidth) << "Course:  " << "CptS 422" << endl;
    cout << right << setw(showWidth) << "Semester:  " << "Summer" << endl;
    cout << right << setw(showWidth) << "Year:  " << "2018" << endl;
    cout << right << setw(showWidth) << "Instructor:  " << "Neil B. Corrigan" << endl;
    cout << right << setw(showWidth) << "Team Name:  " << "Nicolas Cage Fan Society" << endl;
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

// The method view displays the Pushdown Automaton definition and description for the user.
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

// The method list lists the strings stored in the InputStrings object.
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

// The method insert accepts a string from the user and then checks whether it’s a valid string.
// If it’s valid, then it’s given to the InputStrings object to store in the list.
// Otherwise, it’s rejected, and the user is informed of the error.
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

// The method delete accepts an integer from the user, which is the index + 1 of a string on the input string list.
// This is then passed to InputStrings to deal with. Depending on the result, a success or failure message is displayed.
void Commands::deleteString(){
    int input;

    std::cout << std::endl;

    if(pdaLoaded){
        cout << "Enter number of string in string file to be removed: ";
        if (intInput(input))
        {
            if ((input <= strings.numberOfStrings()) && (input > 0) && (strings.numberOfStrings() > 0))
            {
                cout << "String number " << input << " which was " << strings.getInputString(input) << " was successfully deleted." << std::endl;
                strings.removeFromStrings(input);
            }
            else
            {
                cout << "Error:  String number " << input << " does not exist." << endl;
            }
        }
        else
        {
            cout << "Error: Invalid string number." << endl;
        }
        cout << endl;
    }else{
        cout << "Error: No pushdown automata definition currently loaded." << endl;
        cout << endl;
    }
}

// The method set accepts an integer from the user, which is then used as the number of transitions to perform by the pushdown automata.
// If the number given is invalid, then an error message is displayed.
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

// The method truncate accepts an integer from the user,
// which is then used as the number of characters to display on either side of the current character in the instantaneous description of the pushdown automata.
// If the number given is invalid, then an error message is displayed.
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

// The method run runs the Pushdown Automaton as many times as indicated by the configuration setting.
// If the string is accepted or rejected, then operation stops on the Pushdown Automaton and the user is informed of the result.
string Commands::run(){
    int input;
    cout << endl;
    if(pdaLoaded){
        cout <<  "Enter number of string in string file to run: ";
        if (intInput(input))
        {
            cout << endl;
            if (input == 0)
            {
                cout << "Error: Input was less than 1." << endl;
            }
            else if (input > strings.numberOfStrings())
            {
                cout << "Error:  String number " << input << " does not exist." << endl;
            }
            else
            {
                return pda->initialize(strings.getInputString(input));
            }
        }
    }else{
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    cout << endl;
    return "";
}

// The method quit stops the pushdown automata from running anymore on the current string.
// If it wasn’t running on a string, an error message is produced for the user.
void Commands::quit(){
    cout << endl;
    if (!pdaLoaded)
    {
        cout << "Error: No pushdown automata definition currently loaded." << endl;
    }
    else if (pda->isOperating())
    {
        //Change the current status of the pda for the show command
        pda->terminateOperation();
    }
    else
    {
        cout << "Error: The pushdown automaton is not currently operating on an input string." << endl;
    }
    cout << endl;
}

// The method exit lets the user exit the program.
// It performs any cleanup operations which are necessary and then lets the InputStrings object write the string list to the file if necessary.
void Commands::exit(){
    config.writeFile();
    if(pdaLoaded){
        strings.saveToFile(stringFileName);
        delete pda;
    }
    std::exit(EXIT_SUCCESS);
}

// The method open lets the user enter a new Pushdown Automaton definition file.
// It will destroy the current Pushdown Automaton and attempt to load a new one. 
void Commands::open(){
    if(pdaLoaded){
        pdaLoaded = false;
        delete pda;
        pda = 0;
        strings.saveToFile(stringFileName);
        strings.clearAllStrings();
        stringFileName = "";
        definitionFileName = "";
        pdaName = "";
    }
    std::cout << std::endl;
    cout << "Enter the name of the pushdown automata: ";
    getline(cin,pdaName);
    definitionFileName = pdaName + ".def";
    stringFileName = pdaName + ".str";

    pda = new PushdownAutomata(definitionFileName, *this);
    if(pda->isValidDefinition()){
        pdaLoaded = true;
        strings.load(stringFileName, *pda);
    }else{
        delete pda;
        pda = 0;
    }
}

// The method close lets the user to remove the loaded Pushdown Automaton from the program.
// It will destroy the current Pushdown Automaton.
void Commands::close(){
    if(pdaLoaded){
        pdaLoaded = false;
        delete pda;
        pda = 0;
        strings.saveToFile(stringFileName);
        strings.clearAllStrings();
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

// The method display will toggle, "yes" or "no", whether the Pushdown Automaton will show all the Full path though the Pushdown Automaton.
void Commands::display(){
    config.toggleDisplayFullPath();
    std::cout << std::endl;
    cout << "The Display Path setting is " << config.getDisplayFullPath() << endl;
    cout << endl;
}

// The method sort will sort the list of input strings in canonical order.
// If the list is already sorted it will show on screen that is already sorted. 
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

// The method inputCommand lets the user input a command.
// If the command is invalid, the user is given, and error message and the command attribute is set to a dummy character.
// Otherwise, the correct command is stored in the command attribute and the appropriate command method is called.
// This is where the Command: loop exists and where most of the user-interaction is implemented.
void Commands::inputCommand(){
    string lineInput;
    char commandInput = 'z';
    string command = "";
    
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
                command = run();
                if(command == "open"){
                    open();
                }
                if(command == "exit"){
                    commandInput = 'x';
                    exit();
                }
                if(command == "close"){
                    close();
                }
                if(command == "quit"){
                    quit();
                }
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

