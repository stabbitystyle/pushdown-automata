// main function
// Rev0 7/16/18 by William Frank

#include <iostream>

#include "commands.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		Commands commands(argv[1]);
		commands.inputCommand();
	}
	else
	{
		// too few arguments
		if (argc == 1)
		{
			cout << endl;
			cout << "Error: Too few arguments." << endl;
			cout << "Expected ./pda [name]" << endl;
			cout << endl;
		}
		// too many arguments
		else if (argc > 2)
		{
			cout << endl;
			cout << "Error: Too many arguments." << endl;
			cout << "Expected ./pda [name]" << endl;
			cout << endl;
		}
		Commands commands;
		commands.inputCommand();
	}

	return 0;
}