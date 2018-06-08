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
        // TM definition check
        std::cout << "Turing Machine definition loaded correctly" << std::endl;
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
                // Delete
                case 'D':
                case 'd':
                {
                    std::cout << std::endl;
                    std::cout << "Select a string from the string list to delete: " << "2" << std::endl;
                    std::cout << std::endl;
                    std::cout << "String number " << "2" << " which was " << "ABA" << " was successfully deleted." << std::endl;
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
                case 'H':
                case 'h':
                {
                    const int helpWidth = 12;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(D)elete  " << "Delete input string from list" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "E(x)it  " << "Exit application" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(H)elp  " << "Help user" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(I)nsert  " << "Insert input string into list" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(L)ist  " << "List input strings" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(Q)uit  " << "Quit operation of Turing machine on input string" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(R)un  " << "Run Turing machine on input string" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "S(e)t  " << "Set maximum number of transitions to perform" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "Sho(w)  " << "Show status of application" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(T)runcate  " << "Truncate instantaneous descriptions" << std::endl;
                    std::cout << std::right << std::setw(helpWidth) << "(V)iew  " << "View Turing machine" << std::endl;
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
                    std::cout << std::endl;
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
                // Quit
                case 'Q':
                case 'q':
                {
                    // Also have an error message if TM was not currently running
                    std::cout << std::endl;
                    std::cout << "String " << "ABBA" << " was neither accepted nor rejected in " << "20" << " transitions." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                // Run
                case 'R':
                case 'r':
                {
                    // Need message if string accepted by TM
                    // Need message if string rejected by TM
                    const int runWidth = 8;
                    std::cout << std::endl;
                    std::cout << "Input number of string in string file to run: " << "2" << std::endl;
                    std::cout << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "0. " << "" << "[s0]" << "AAB>" << std::endl;
                    std::cout << std::right << std::setw(runWidth) << "10. " << "<ABB" << "[s10]" << "BB" << std::endl;
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
                    std::cout << std::endl;
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
                    std::cout << std::right << std::setw(showWidth) << "Course:  " << "CptS 322" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Semester:  " << "Spring" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Year:  " << "2018" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Instructor:  " << "Neil B. Corrigan" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Author:  " << "William Robert Frank" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Version:  " << "Prototype 1.0" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Maximum Transitions Setting:  " << "2" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Truncate Width Setting:  " << "3" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Name of Turing Machine:  " << "AnBn" << std::endl;
                    // If currently running, need to output input string and # of transitions performed so far
                    // If completed, need to output input string, result, and # of transitions performed
                    std::cout << std::right << std::setw(showWidth) << "Status of Turing Machine:  " << "Currently Running" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Current Input String:  " << "AAAAAAABBBBBBB" << std::endl;
                    std::cout << std::right << std::setw(showWidth) << "Number of Transitions Performed:  " << "15" << std::endl;
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
                    std::cout << std::endl;
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
                    std::cout << "This file contains a Turing machine which accepts a number of A's followed by an equal number of B's" << std::endl;
                    std::cout << "For example:  AABB or AAABBB or AB" << std::endl;
                    std::cout << std::endl;
                    // Q is finite set of states
                    std::cout << "Q = {" << "s0, s1, s2, s3" << "}" << std::endl;
                    // Epsilon is finite input alphabet
                    std::cout << "\u03A3 = {" << "A, B" << "}" << std::endl;
                    // Gamma is finite tape alphabet
                    std::cout << "\u0393 = {" << "A, B, X, Y, -" << "}" << std::endl;
                    // Delta are the transition functions
                    std::cout << "\u03B4(s0, A)" << " = " << "(s1, X, R)" << std::endl;
                    std::cout << "\u03B4(s0, Y)" << " = " << "(s3, Y, R)" << std::endl;
                    std::cout << "\u03B4(s1, A)" << " = " << "(s1, A, R)" << std::endl;
                    std::cout << "\u03B4(s1, B)" << " = " << "(s2, Y, L)" << std::endl;
                    std::cout << "\u03B4(s1, Y)" << " = " << "(s1, Y, R)" << std::endl;
                    std::cout << "\u03B4(s2, A)" << " = " << "(s2, A, L)" << std::endl;
                    std::cout << "\u03B4(s2, X)" << " = " << "(s0, X, R)" << std::endl;
                    std::cout << "\u03B4(s2, Y)" << " = " << "(s2, Y, L)" << std::endl;
                    std::cout << "\u03B4(s3, Y)" << " = " << "(s3, Y, R)" << std::endl;
                    std::cout << "\u03B4(s3, -)" << " = " << "(s4, -, R)" << std::endl;
                    // q0 is the initial state
                    std::cout << "q0 = " << "s0" << std::endl;
                    // B is the blank symbol
                    std::cout << "B = " << "-" << std::endl;
                    // F is the set of final states
                    std::cout << "F = {" << "s4" << "}" << std::endl;
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
