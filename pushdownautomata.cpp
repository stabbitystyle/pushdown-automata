// Pushdown Automata class
// Rev0 7/4/18 by William Frank

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "states.hpp"
#include "finalstates.hpp"
#include "instantaneousdescription.hpp"
#include "pushdownautomata.hpp"
#include "stackalphabet.hpp"
#include "transitionfunction.hpp"
#include "inputalphabet.hpp"
#include "configurationsettings.hpp"
#include "uppercase.hpp"
#include "commandsinoperation.hpp"
#include "commands.hpp"

using namespace std;

ConfigurationSettingsPointer PushdownAutomata::configurationSettingsPointer = 0;

// The method PushdownAutomaton is the constructor for the class PushdownAutomaton.
// It accepts a definitionFileName string as a parameter.
// The constructor pulls out the description from the start of the definition file to the first keyword “States: ”, which is then puts in the description attribute.
// The constructor will also pull the initial state from the definition file and store it in the initialState attribute.
// The constructor then passes the definition file, along with the valid attribute, InputAlphabet object, StackAlphabet object, TransitionFunction object, States object, and FinalStates object.
// Each of those objects will parse their respective sections of the definition file and modify the valid attribute based on whether the definition was valid or not.
// The constructor will check that valid is still true between each of those checks by the respective objects and will continue to find errors.
PushdownAutomata::PushdownAutomata(string definitionFileName, Commands& cmd)
{
	valid = true;
	used = false;

    ifstream definition(definitionFileName.c_str(), ifstream::in);
    string value;

	commands = new CommandsInOperation();
	commands->link(cmd);

    cout << endl;
    if(definition.fail())
    {
        cout << "Error: failed to open file " << definitionFileName << endl;
        valid = false;
    }

	// Description
	while (definition >> value && uppercase(value) != "STATES:")
	{
		string uppercaseValue = uppercase(value);
		if ((uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STACK_ALPHABET:") || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "START_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
		{
			cout << "Error: Improper keyword used in definition: " << uppercaseValue << "." << endl;
			valid = false;
			break;
		}
		else
		{
			description.push_back(value);
		}
	}
	// States
	if (uppercase(value) == "STATES:")
	{
		states.load(definition, value, valid);
	}
	else
	{
		cout << "Error: STATES: keyword must come after definition section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Input Alphabet
	if (uppercase(value) == "INPUT_ALPHABET:")
	{
		inputAlphabet.load(definition, value, valid);
	}
	else
	{
		cout << "Error: INPUT_ALPHABET: keyword must come after States section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Stack Alphabet
	if (uppercase(value) == "STACK_ALPHABET:")
	{
		stackAlphabet.load(definition, value, valid);
	}
	else
	{
		cout << "Error: STACK_ALPHABET: keyword must come after Input Alphabet section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Transition Function
	if (uppercase(value) == "TRANSITION_FUNCTION:")
	{
		transitionFunction.load(definition, value, valid);
	}
	else
	{
		cout << "Error: TRANSITION_FUNCTION: keyword must come after Stack Alphabet section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Initial State
	if (uppercase(value) == "INITIAL_STATE:")
	{
		loadInitialState(definition, value, valid);
	}
	else
	{
		cout << "Error: INITIAL_STATE: keyword must come after Transition Function section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Start Character
	if (uppercase(value) == "START_CHARACTER:")
	{
		loadInitialStackCharacter(definition, value, valid);
	}
	else
	{
		cout << "Error: START_CHARACTER: keyword must come after Transition Function section.  Keyword used was: " << value << endl;
		valid = false;
	}
	// Final States
	if (uppercase(value) == "FINAL_STATES:")
	{
		finalStates.load(definition, value, valid);
	}
	else
	{
		cout << "Error: FINAL_STATES: keyword must come after Start Character section.  Keyword used was: " << value << endl;
		valid = false;
	}

	// Validate input
	if (valid != false)
	{
		finalStates.validate(states, valid);
		transitionFunction.validate(stackAlphabet, inputAlphabet, states, finalStates, valid);
		if (!states.isElement(initialState))
		{
			cout << "Error: Initial state " << initialState << " is not an element of States" << endl;
			valid = false;
		}
		if (!stackAlphabet.isElement(initialStackCharacter))
		{
			cout << "Error: Initial stack character " << initialStackCharacter << " is not an element of Stack Alphabet" << endl;
			valid = false;
		}
	}
	if (valid == true)
	{
		cout << "Pushdown Automata definition loaded correctly." << endl;
	}
	else
	{
		cout << "Pushdown Automata definition failed to load correctly." << endl;
	}
}

// loadInitialState is a local method used by PushdownAutomata to parse the initial state out of the ifstream.
// It also can modify the argument valid for use outside the method if the formatting is incorrect.
void PushdownAutomata::loadInitialState(ifstream& definition, string& value, bool& valid)
{
	if ((definition >> value))
	{
		string uppercaseValue = uppercase(value);
		if ((uppercaseValue == "STATES:") || (uppercaseValue == "INPUT_ALPHABET:") || (uppercaseValue == "STACK_ALPHABET:") || (uppercaseValue == "TRANSITION_FUNCTION:") || (uppercaseValue == "INITIAL_STATE:") || (uppercaseValue == "START_CHARACTER:") || (uppercaseValue == "FINAL_STATES:"))
		{
			cout << "Error: Improper keyword used in initial state: " << uppercaseValue << endl;
			valid = false;
		}
		else
		{
			for (string::iterator it = value.begin(); it != value.end(); ++it)
			{
				if ((!isalnum(*it)) && (*it != '_'))
				{
					cout << "Error: Illegal character used in initial state: " << value << endl;
					valid = false;
				}
			}
			initialState = value;
		}
	}
	else
	{
		cout << "Error: Failed to read initial state." << endl;
		valid = false;
	}
	if (definition.eof())
	{
		cout << "Error: End of file reached too soon." << endl;
		valid = false;
	}
	else
	{
		definition >> value;
		if (definition.eof())
		{
			cout << "Error: End of file reached too soon." << endl;
			valid = false;
		}
	}
}

// loadInitialStackCharacter is a local method used by PushdownAutomata to parse the initial stack character out of the ifstream.
// It also can modify the argument valid for use outside the method if the formatting is incorrect.
void PushdownAutomata::loadInitialStackCharacter(ifstream& definition, string& value, bool& valid)
{
	if ((definition >> value) && (value.length() == 1) && (value[0] != '\\') && (value[0] != '(') && (value[0] != ')') && (value[0] != '>') && (value[0] != ','))
	{
		initialStackCharacter = value[0];
	}
	else
	{
		cout << "Error: Illegal initial stack character: " << value << endl;
		valid = false;
	}
	if (definition.eof())
	{
		cout << "Error: End of file reached too soon." << endl;
		valid = false;
	}
	else
	{
		definition >> value;
		if (definition.eof())
		{
			cout << "Error: End of file reached too soon." << endl;
			valid = false;
		}
	}
}

// The method isAccepted is a recursive method that will find if a string is accepted by the Pushdown Automaton.
// It will check if the Pushdown Automaton is still operating.
// It will check the non-lambda transitions first and if none work it will then try the lambda transitions.
// If it goes though all possible transitions and not fined a path that leads to success, it will return false.
bool PushdownAutomata::isAccepted(InstantaneousDescription id, int numberInCurrentPath, bool& running, string& commandCalled)
{
	bool performedTransition = false;
	int index = 0;
	int count = 0;
	string destinationState;
	string pushString;
	InstantaneousDescription nextID;

	string pieceOfPath = std::to_string(numberOfTransitions) + std::string(". [") + std::to_string(numberInCurrentPath) + std::string("] ") + id.view(configurationSettingsPointer);
	pathContainer.push_back(pieceOfPath);
	
	if (configurationSettingsPointer->getDisplayFullPath() == "Yes" || numberOfTransitions == 0){
		cout << pieceOfPath;
		cout << endl;
	}

	if (numberOfTransitions != 0) {
		++transitionCount;
	}
	if(finalStates.isElement(id.state()) && id.isEmptyRemainingInputString())
	{
		if (configurationSettingsPointer->getDisplayFullPath() == "No"){
			cout << pieceOfPath;
			cout << endl;
		}
		return true;
	}

	if (transitionCount == configurationSettingsPointer->getMaximumNumberOfTransitions() && running) {
		if (configurationSettingsPointer->getDisplayFullPath() == "No"){
			cout << pieceOfPath;
			cout << endl;
		}
		resetTransitionCount();
		commandCalled = commands->inputCommand();

		if(commandCalled == "exit"){
			operating = false;
			running = false;
		}
		if(commandCalled == "close"){
			operating = false;
			running = false;
		}
		if(commandCalled == "open"){
			operating = false;
			running = false;
		}
		if(commandCalled == "quit"){
			running = false;
		}
	}

	if(running){
	    if(!id.isEmptyRemainingInputString() && !id.isEmptyStack())
	    {
		    count = transitionFunction.transitionCount(id.state(), id.inputCharacter(), id.topOfStack());
		    for(index = 0; index < count; ++index)
		    {
			    if(running){
				    transitionFunction.getTransition(index, id.state(), id.inputCharacter(), id.topOfStack(), destinationState, pushString);
				    id.performTransition(destinationState, pushString, nextID);
				    performedTransition = true;
				    ++numberOfTransitions;
				    if(isAccepted(nextID, numberInCurrentPath + 1, running, commandCalled))
				    {
					    return true;
				    }
			    }
		    }
	    }

	    if(!id.isEmptyStack())
	    {
		    count = transitionFunction.lambdaTransitionCount(id.state(), id.topOfStack());
		    for(index = 0; index < count; ++index)
		    {
			    if(running){
				    transitionFunction.getLambdaTransition(index, id.state(), id.topOfStack(), destinationState, pushString);
				    id.performLambdaTransition(destinationState, pushString, nextID);
				    performedTransition = true;
				    ++numberOfTransitions;
				    if(isAccepted(nextID, numberInCurrentPath + 1, running, commandCalled))
				    {
					    return true;
				    }
			    }
		    }
	    }
	    if(!performedTransition)
	    {
			++numberOfCrashes;
			if (configurationSettingsPointer->getDisplayFullPath() == "Yes"){
		    	cout << "Crash " << numberOfCrashes << " occured." << endl;
			}
	    }
		pathContainer.pop_back();
	    return false;
	}
	return false;
}

// points the configurationSettingsPointer at a configurationSettings object referenced by configurationSettings
void PushdownAutomata::link(ConfigurationSettings& configurationSettings)
{
    configurationSettingsPointer = &configurationSettings;
}

// The method viewDefinition prints out the description of the Pushdown Automaton as found in the definition file,
//		followed by the definition of the Pushdown Automaton.
// The definition for the Pushdown Automaton is printed using methods for the various classes which print their respective information,
//		after which the entire definition will have been printed.
void PushdownAutomata::viewDefinition() const
{
	for (vector<string>::const_iterator it = description.begin(); it != description.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl << endl;

	states.view();
	cout << endl;

	inputAlphabet.view();
	cout << endl;

	stackAlphabet.view();
	cout << endl;

	transitionFunction.view();
	cout << endl;

	cout << "q0 = " << initialState;
	cout << endl << endl;

	finalStates.view();
	cout << endl;
}

// The method initialize will accept inputString, which is the string to be tested on the Pushdown Automaton.
// It will store inputString in originalInputString, and then set the operating Boolean to true.
// It will also set numberOfTransitions, numberOfCrashes, and numberOfTransitionsInSuccessfulPath to 0, and the used Boolean to true.
string PushdownAutomata::initialize(string inputString)
{
	originalInputString = inputString;
	currentState = initialState;
	numberOfTransitions = 0;
	numberOfCrashes = 0;
	numberOfTransitionsInSuccessfulPath = 0;
	used = true;
	operating = true;
	accepted = false;
	rejected = false;
	//callededCommand = "";
	bool running = true;
	string command = "";
	
	InstantaneousDescription startingId(currentState, originalInputString, initialStackCharacter);
	accepted = this->isAccepted(startingId, numberOfTransitions, running, command);
	rejected = !accepted;
	resetTransitionCount();
	if(running){
		if (accepted)
		{
			cout << "Input string " << originalInputString << " accepted in " << numberOfTransitions << " transitions with " << numberOfCrashes << " crashes." << endl;
			if (configurationSettingsPointer->getDisplayFullPath() == "Yes"){
				int i = 0;
				for(vector<string>::const_iterator it = pathContainer.begin(); it != pathContainer.end(); ++it)
    			{
        			i++;
    			}
				cout << "Successful path of " + std::to_string(i - 1) + " transitions through the pda:" << endl;
				for(vector<string>::const_iterator it = pathContainer.begin(); it != pathContainer.end(); ++it)
    			{
        			cout << *it << endl;
    			}
			}
			operating = false;
		}
		if (rejected)
		{
			cout << "Input string " << originalInputString << " rejected in " << numberOfTransitions << " transitions with " << numberOfCrashes << " crashes." << endl;
			operating = false;
		}
	}else{
		cout << "Input string " << originalInputString << " neither accepted or rejected in " << numberOfTransitions << " transitions with " << numberOfCrashes << " crashes." << endl;
		rejected = false;

	}
	return command;
}

// The method terminateOperation terminates operation of the Pushdown Automaton.
// It sets operating attribute to false.
void PushdownAutomata::terminateOperation()
{
	operating = false;
}

// The method inputString returns the attribute originalInputString.
string PushdownAutomata::inputString() const
{
	return originalInputString;
}

// The method totalNumberOfTransitions returns the numberOfTransitions attribute.
int PushdownAutomata::totalNumberOfTransitions() const
{
    return numberOfTransitions;
}

// The method totalNumberOfCrashes returns the numberOfCrashes attribute.
int PushdownAutomata::totalNumberOfCrashes() const
{
	return numberOfCrashes;
}

// The method isValidDefinition returns the attribute valid.
bool PushdownAutomata::isValidDefinition() const
{
    return valid;
}

// The method isValidInputString accepts a String named value as a parameter, which it then checks against the Pushdown Automaton definition to determine whether it�s a valid string.
// It returns a Boolean value depending on the result.
bool PushdownAutomata::isValidInputString(string value) const
{
	bool isValid = true;
	for (string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		if (!inputAlphabet.isElement(*it))
		{
			isValid = false;
		}
	}
	return isValid;
}

// The method isUsed returns the attributed used.
bool PushdownAutomata::isUsed() const
{
    return used;
}

// The method isOperating returns the attribute operating.
bool PushdownAutomata::isOperating() const
{
    return operating;
}

// The method isAcceptedInputString returns the attribute accepted.
bool PushdownAutomata::isAcceptedInputString() const
{
    return accepted;
}

// The method isRejectedInputString returns the attribute rejected.
bool PushdownAutomata::isRejectedInputString() const
{
    return rejected;
}

void PushdownAutomata::resetTransitionCount()
{
	transitionCount = 0;
}

/*void PushdownAutomata::setCalledCommand(string value){
	callededCommand = value;

}*/