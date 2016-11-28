#include "Controller.h"

//---Controller---
//----------------
// Well, just a general controller... not much to see here.
string Controller::userInputString = "@input-";
string Controller::outputString = "@output-";
string Controller::actionString = "@action-";

vector<string> Controller::errorBag = {};

void Controller::justShow()
{
	addstr(this->viewChunk.c_str());
	printString("\n\n");
}

// Determine the order of the input/output from the user.
void Controller::prepareView()
{
	string copyChunk = this->viewChunk;

	if (this->hasInput(copyChunk))
	{
		this->controllerAttributions.push_back("input");

		// Pass the corresposing action to userInputs.
		this->prepareAction(copyChunk);
	}
	if (this->hasOutput(copyChunk))
	{
		this->controllerAttributions.push_back("output");
	}

	while (this->hasInput(copyChunk) || this->hasOutput(copyChunk))
	{
		if (!this->hasOutput(copyChunk))
		{
			this->chopChunkAndGetAlias(copyChunk);
		}
		else if (!this->hasInput(copyChunk))
		{
			// To avoid the type issue, let the model to the outputting via a method, 
			// same way as getting the input, chopping the chunk.
		}
		else if (this->hasInput(copyChunk) || this->hasOutput(copyChunk))
		{
			if (copyChunk.find(Controller::userInputString) < copyChunk.find(Controller::outputString))
			{
				this->chopChunkAndGetAlias(copyChunk);
			}
			else
			{
				// this->bringDataOnceInChunk()
			}
		}
	}

	// Show the rest.
	if (copyChunk.size())
	{
		addstr((copyChunk + "\n\n").c_str());
	}

	// Send the payload to the accessor model to be passed to the according repository.
	if (isInVector(this->controllerAttributions, "input"))
	{
		this->model.confirmInput(this->userInputs);
	}
}

void Controller::prepareViewInput(const string &subChunk, const string &inputAlias)
{
	string userInput;
	map<string, string> currentInput;

	addstr((subChunk + " ").c_str());
	refresh();

	// Hide the input when typing any sensitive data.
	if (inputAlias.find("password") != string::npos)
	{
		const char carriage_return = 10;
		const char backspace = 8;

		unsigned char ch = 0;

		noecho();
		while ((ch = getch()) != carriage_return)
		{
			if (ch == backspace && userInput.size())
			{
				// Otherwise the previous character will still remain on the screen if not replaced with a whitespace.
				printString("\b \b");
				userInput.resize(userInput.size() - 1);
			}
			else if (ch != backspace)
			{
				userInput += ch;
				printString("*");
			}
		}
		echo();
	}
	else
	{
		getString(userInput);
	}

	this->userInputs[inputAlias] = userInput;
}

void Controller::prepareAction(string &chunk)
{
	this->userInputs["action"] = chunk.substr(chunk.find(Controller::actionString) + Controller::actionString.size(),
											  chunk.find("\n", chunk.find(Controller::actionString)) - chunk.find(Controller::actionString) - Controller::actionString.size());

	chunk.erase(chunk.find(Controller::actionString),
		(Controller::actionString + this->userInputs["action"]).size() + 1);
}

void Controller::pushError(string &error)
{
	if (error == "")
	{
		Controller::errorBag = vector<string>({});
	}
	else
	{
		Controller::errorBag.push_back(error);
	}
}

vector<string> Controller::getErrorBag()
{
	return Controller::errorBag;
}

Controller::Controller()
{
	this->controllerName = new char[strlen("NO_CONTROLLER") + 1];
	strcpy(this->controllerName, "NO_CONTROLLER");

	this->viewChunk = "";
	this->controllerAttributions = {};
	this->userInputs = {};
}

Controller::Controller(char *viewName, string &viewChunk, string &ViewExtension)
{
	string controllerName = viewName;
	controllerName.erase(controllerName.find(ViewExtension), ViewExtension.size()).append("Controller");

	// Enable input echoing when typing.
	echo();

	this->controllerName = new char[controllerName.size() + 1];
	strcpy(this->controllerName, controllerName.c_str());

	this->viewChunk = viewChunk;
	this->controllerAttributions = {};
	this->userInputs = {};

	(this->hasInput(viewChunk) || this->hasOutput(viewChunk)) ? this->prepareView() : this->justShow();
}

vector<string>& Controller::getControllerAttributions()
{
	return this->controllerAttributions;
}

char *Controller::getControllerName()
{
	return this->controllerName;
}

void Controller::chopChunkAndGetAlias(string &chunk)
{
	// Splice the alias (take the part after the "-" in the template string).
	string inputAlias = chunk.substr(chunk.find(Controller::userInputString) + Controller::userInputString.size(),
									 chunk.find("\n", chunk.find(Controller::userInputString)) - (chunk.find(Controller::userInputString) + Controller::userInputString.size()));

	this->prepareViewInput(chunk.substr(0, chunk.find(Controller::userInputString) - 1), inputAlias);

	chunk.erase(0, chunk.find(inputAlias) + inputAlias.size() + 1);
}

// Don't assign it multiple times, stupid.
void Controller::operator=(const Controller &controller)
{
	delete[] this->controllerName;
	this->controllerName = new char[strlen(controller.controllerName) + 1];
	strcpy(this->controllerName, controller.controllerName);

	this->viewChunk = controller.viewChunk;
	this->controllerAttributions = controller.controllerAttributions;
}

bool Controller::hasInput(const string &raw)
{
	return raw.find(Controller::userInputString) != string::npos;
}

bool Controller::hasOutput(const string &raw)
{
	return raw.find(Controller::outputString) != string::npos;
}

Controller::~Controller()
{
	delete[] this->controllerName;

	noecho();
}