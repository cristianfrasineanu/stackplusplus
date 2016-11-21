#include "Controller.h"

//---Controller---
//----------------
string Controller::viewInputFormat = "@input-";
string Controller::viewOutputFormat = "@output-";

void Controller::justShow()
{
	cout << this->viewChunk
		<< endl;
}

void Controller::prepareView()
{
	// Preserve the original one
	string copyChunk = this->viewChunk;

	if (this->hasInput(copyChunk))
	{
		this->controllerAttributions.insert(this->controllerAttributions.begin(), "input");
	}
	if (this->hasOutput(copyChunk))
	{
		this->controllerAttributions.insert(this->controllerAttributions.begin(), "output");
	}

	// Determine the order of the input/output from the user.
	while (this->hasInput(copyChunk) || this->hasOutput(copyChunk))
	{
		if (!this->hasOutput(copyChunk))
		{
			this->chopChunkAndGetAlias(copyChunk);
		}
		if (!this->hasInput(copyChunk))
		{
			// Gather all the required variables from the model and replace them in chunk at once (no need to wait for input), thus discarding the dummy chunk
			// this->bringAllDataInChunk()
		}
		else
		{
			if (copyChunk.find(Controller::viewInputFormat) < copyChunk.find(Controller::viewOutputFormat))
			{
				this->chopChunkAndGetAlias(copyChunk);
			}
			else
			{
				// this->bringDataOnceInChunk()
			}
		}
	}

	// Show the rest
	if (copyChunk.size())
	{
		cout << copyChunk
			<< endl;
	}
}

void Controller::prepareViewInput(string &subChunk, string &inputAlias)
{
	string userInput;
	
	cout << subChunk << " ";
	cin >> userInput;
	cout << endl;

	this->userInputs[inputAlias] = userInput;
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

	this->controllerName = new char[strlen(controllerName.c_str()) + 1];
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
	string inputAlias = chunk.substr(chunk.find(Controller::viewInputFormat) + Controller::viewInputFormat.size(), 
									 chunk.find("\n", chunk.find(Controller::viewInputFormat)) - (chunk.find(Controller::viewInputFormat) + Controller::viewInputFormat.size()));

	this->prepareViewInput(chunk.substr(0, chunk.find(Controller::viewInputFormat) - 1), inputAlias);

	chunk.erase(0, chunk.find(inputAlias) + inputAlias.size() + 2);
}

// One Controller at a time, you expected more?
void Controller::operator=(const Controller &controller)
{
	if (controller.controllerName != NULL)
	{
		delete[] this->controllerName;
		this->controllerName = new char[strlen(controller.controllerName) + 1];
		strcpy(this->controllerName, controller.controllerName);
	}
	this->viewChunk = controller.viewChunk;
	this->controllerAttributions = controller.controllerAttributions;
}

bool Controller::hasInput(string &raw)
{
	return raw.find(Controller::viewInputFormat) != string::npos;
}

bool Controller::hasOutput(string &raw)
{
	return raw.find(Controller::viewOutputFormat) != string::npos;
}

Controller::~Controller()
{
	log(this->userInputs, "userInput", "destroying the controller");
	delete[] this->controllerName;
}
