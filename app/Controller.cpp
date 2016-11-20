#include "Controller.h"

//---Controller---
//----------------
string Controller::viewInputFormat = "@input-";
string Controller::viewOutputFormat = "@output-";

void Controller::prepareView()
{
	cout << this->viewChunk.c_str()
		<< endl;

	// Show for now
	// TODO use the input/output format to parse the chunk
}

void Controller::prepareViewInput()
{
	// Prompt the user for input
}

string &Controller::getViewInputFormat()
{
	return Controller::viewInputFormat;
}

string & Controller::getViewOutputFormat()
{
	return Controller::viewOutputFormat;
}

Controller::Controller()
{
	this->controllerName = new char[strlen("NO_CONTROLLER") + 1];
	strcpy(this->controllerName, "NO_CONTROLLER");
	this->viewChunk = "";
	this->controllerAttributions = {};
}

Controller::Controller(char *viewName, string &viewChunk, string &ViewExtension)
{
	string controllerName = viewName;
	controllerName.erase(controllerName.find(ViewExtension), ViewExtension.size()).append("Controller");

	this->controllerName = new char[strlen(controllerName.c_str()) + 1];
	strcpy(this->controllerName, controllerName.c_str());
	this->viewChunk = viewChunk;
	this->controllerAttributions = {};

	this->prepareView();
}

vector<string>& Controller::getControllerAttributions()
{
	return this->controllerAttributions;
}

char *Controller::getControllerName()
{
	return this->controllerName;
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
	return raw.find(Controller::getViewInputFormat()) != string::npos;
}

Controller::~Controller()
{
	delete[] this->controllerName;
}
