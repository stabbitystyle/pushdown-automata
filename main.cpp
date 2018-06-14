#include <iostream>
#include <iomanip>
#include <string>

int main(int argc, char* argv[])
{
    std::string lineInput;
    char commandInput;
    // Needs to be 2 in final version
    if(argc == 1)
    {
        // File verification check
        // PDA definition check
        std::cout << "Pushdown automata definition loaded correctly" << std::endl;
        std::cout << std::endl;
        while(commandInput != 'x' && commandInput != 'X')
        {
            std::cout << "Command: ";
            std::getline(std::cin, lineInput);
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
                    std::cout << std::endl;
                    // error if no PDA currently loaded
                    // if running on a string, end operation
                    // if definition is loaded, unload it
                    std::cout << "The pushdown automaton has been successfully closed" << std::endl;
                    // if string list has been modified, write to file
                    std::cout << "The string list file has been successfully modified" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Delete
                case 'D':
                case 'd':
                {
                    std::cout << std::endl;
                    std::cout << "Select a string number from the string list to delete: " << "2" << std::endl;
                    //std::cout << std::endl;
                    std::cout << "String number " << "2" << " which was " << "ABA" << " was successfully deleted." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Display
                case 'P':
                case 'p':
                {
                    // Need error message if input not n, N, y, or Y
                    std::cout << std::endl;
                    std::cout << "The display complete path setting is yes" << "." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Exit
                case 'X':
                case 'x':
                {
                    std::cout << std::endl;
                    //std::cout << "The program checks if the input string list was modified in any way (probably a bool check)" << std::endl;
                    //std::cout << "If it was, the new list is written over the old string list file (or a new one is made if an old one didn't exist)" << std::endl;
                    //std::cout << "If the string list file had to be made/modified, a message will output for success or failure" << std::endl;
                    //std::cout << "Then the program exists" << std::endl;
                    std::cout << "The string list file has been successfully modified" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Help
                // commands in alphabetical order
                case 'H':
                case 'h':
                {
                    const int helpWidth = 12;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(C)lose  " << "Close a pushdown automata definition" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(D)elete  " << "Delete input string from list" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "Dis(p)lay  " << "Display the complete paths through the pushdown automaton" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "E(x)it  " << "Exit application" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(H)elp  " << "Help user" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(I)nsert  " << "Insert input string into list" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(L)ist  " << "List input strings" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(O)pen  " << "Open a pushdown automata definition" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(Q)uit  " << "Quit operation of pushdown automata on input string" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(R)un  " << "Run pushdown automata on input string" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "S(e)t  " << "Set maximum number of transitions to perform" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "Sho(w)  " << "Show status of application" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(S)ort  " << "Sort the strings in the input string list" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(T)runcate  " << "Truncate instantaneous descriptions" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(V)iew  " << "View pushdown automata" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Insert
                case 'I':
                case 'i':
                {
                    // Output for success (shown) and also one for failure if string is not in language or already on list
                    std::cout << std::endl;
                    std::cout << "Input a string to be added to the string list: " << "ABBA" << std::endl;
                    std::cout << "String " << "ABBA" << " was added to the string list." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // List
                case 'L':
                case 'l':
                {
                    const int listWidth = 8;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(listWidth) << "1. " << "ABA" << std::endl;
                    std::cout << std::right << std::setw(listWidth) << "2. " << "ABBA" << std::endl;
                    std::cout << std::right << std::setw(listWidth) << "3. " << "ABBAB" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Open
                case 'O':
                case 'o':
                {
                    std::cout << std::endl;
                    // if no input, skip and go back to Command: prompt, still close
                    // if running on a string, end operation
                    // if definition is loaded, unload it, no message?
                    // if string list has been modified, write to file
                    std::cout << "The string list file has been successfully modified" << std::endl;
                    std::cout << std::endl;
                    // attempt to load definition file
                    std::cout << "File: " << "pda2" << std::endl;
                    std::cout << std::endl;
                    // error message if failure but stay in application
                    std::cout << "Pushdown automata definition loaded correctly" << std::endl;
                    // if loaded, attempt to load string file associated with definition file, no message?
                    std::cout << std::endl;
                    break;
                }
                // Quit
                case 'Q':
                case 'q':
                {
                    // Also have an error message if TM was not currently running
                    std::cout << std::endl;
                    std::cout << "String " << "ABBA" << " was neither accepted nor rejected in " << "20" << " transitions and " << "3" << " crashes." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Run
                case 'R':
                case 'r':
                {
                    // Need message if string accepted by PDA
                    // Need message if string rejected by PDA
                    const int runWidth = 8;
                    std::cout << std::endl;
                    std::cout << "Input number of string in string file to run: " << "1" << std::endl;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "0. " << "[0] " << "(s0, ABA, Z)" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "1. " << "[1] " << "(s0, BA, XZ)" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "2. " << "[2] " << "(s0, A, YXZ)" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "3. " << "[3] " << "(s0, \\, XYXZ)" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "Crash " << "1" << " occurred." << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "4. " << "[3] " << "(s1, \\, YXZ)" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "Crash " << "2" << " occurred." << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "5. " << "[2] " << "(s1, A, XZ)" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Set
                case 'E':
                case 'e':
                {
                    // Need error message if input less than 1
                    std::cout << std::endl;
                    std::cout << "Set the maximum number of transitions[1]: " << "2" << std::endl;
                    //std::cout << std::endl;
                    std::cout << "Maximum number of transitions set to " << "2" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Show
                case 'W':
                case 'w':
                {
                    // Only things that will need to be changed here are version number as I build the program, transition and truncate settings (can just pull the value)
                    // Name of Turing Machine (which will be set at successful launch), and status of turing machine (will have a 3 state value to keep track)
                    const int showWidth = 34;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Course:  " << "CptS 422" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Semester:  " << "Summer" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Year:  " << "2018" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Instructor:  " << "Neil B. Corrigan" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Authors:  " << "Emmanuel Bonilla, Ryan Breitenfeldt, William Robert Frank," << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "  " << "Carlos Martinez, Mike Snyder, Cole Woodford" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Version:  " << "Prototype 1.0" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Maximum Transitions Setting:  " << "2" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Truncate Width Setting:  " << "3" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Display Setting:  " << "Yes" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Name of Pushdown Automata:  " << "AnBn" << std::endl;
                    // If currently running, need to output input string and # of transitions performed so far
                    // If completed, need to output input string, result, and # of transitions performed
                    std::cout << std::right << std::setw(showWidth) << "Current Input String:  " << "AAAAAAABBBBBBB" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Status of Pushdown Automata:  " << "Completed Operation" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Result of Test:  " << "Neither Accepted nor Rejected" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Number of Transitions Performed:  " << "15" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Number of Crashes:  " << "2" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Sort
                // sorts first by length (shortest first) then ascii value (lowest first)
                case 'S':
                case 's':
                {
                    // if already in order, display message saying so
                    // if not in order, sort.  display message saying list sorted.  show list?
                    std::cout << std::endl;
                    std::cout << "The string list has been successfully sorted." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Truncate
                case 'T':
                case 't':
                {
                    // Need error message if input less than 1
                    std::cout << std::endl;
                    std::cout << "Set the width to truncate the ID[3]: " << "4" << std::endl;
                    //std::cout << std::endl;
                    std::cout << "Width to truncate the ID set to " << "4" << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // View
                case 'V':
                case 'v':
                {   
                    std::cout << std::endl;
                    // Description pulled from TM source file
                    std::cout << "A pushdown automata which accepts the language of odd palindromes over {a, b} is shown below" << std::endl;
                    std::cout << std::endl;
                    // Q is finite set of states
                    std::cout << "Q = {" << "s0, s1, s2" << "}" << std::endl;
                    std::cout << std::endl;
                    // Sigma is finite input alphabet
                    std::cout << "\u03A3 = {" << "A, B" << "}" << std::endl;
                    std::cout << std::endl;
                    // Gamma is finite tape alphabet
                    std::cout << "\u0393 = {" << "X, Y, Z" << "}" << std::endl;
                    std::cout << std::endl;
                    // Delta are the transition functions
                    std::cout << "\u03B4(s0, A, X)" << " = " << "(s0, XX)" << std::endl;
                    std::cout << "\u03B4(s0, A, X)" << " = " << "(s1, X)" << std::endl;
                    std::cout << "\u03B4(s0, A, Y)" << " = " << "(s0, XY)" << std::endl;
                    std::cout << "\u03B4(s0, A, Y)" << " = " << "(s1, Y)" << std::endl;
                    std::cout << "\u03B4(s0, A, Z)" << " = " << "(s0, XZ)" << std::endl;
                    std::cout << "\u03B4(s0, A, Z)" << " = " << "(s1, Z)" << std::endl;
                    std::cout << "\u03B4(s0, B, X)" << " = " << "(s0, YX)" << std::endl;
                    std::cout << "\u03B4(s0, B, X)" << " = " << "(s1, X)" << std::endl;
                    std::cout << "\u03B4(s0, B, Y)" << " = " << "(s0, YY)" << std::endl;
                    std::cout << "\u03B4(s0, B, Y)" << " = " << "(s1, Y)" << std::endl;
                    std::cout << "\u03B4(s0, B, Z)" << " = " << "(s0, YZ)" << std::endl;
                    std::cout << "\u03B4(s0, B, Z)" << " = " << "(s1, Z)" << std::endl;
                    std::cout << "\u03B4(s1, A, X)" << " = " << "(s1, \\)" << std::endl;
                    std::cout << "\u03B4(s1, B, Y)" << " = " << "(s1, \\)" << std::endl;
                    std::cout << "\u03B4(s1, \\, Z)" << " = " << "(s2, \\)" << std::endl;
                    std::cout << std::endl;
                    // q0 is the initial state
                    std::cout << "q0 = " << "s0" << std::endl;
                    std::cout << std::endl;
                    // Z0 is the ??????
                    std::cout << "Z0 = " << "Z" << std::endl;
                    std::cout << std::endl;
                    // F is the set of final states
                    std::cout << "F = {" << "s2" << "}" << std::endl;
                    std::cout << std::endl;
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

    return 0;
}
