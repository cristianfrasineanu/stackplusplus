#include "Console.h"

//---Console---
//-------------
// We need an initial state, because we don't have any means like mapping views to HTTP routes.
// The Console class represents an entry point for all the other components, like View
string Console::initialView = "home.view";
string Console::viewsFolder = "..\\views";

Console::Console()
{
	this->mode = new char[strlen("live") + 1];
	this->lastInput = '\0';
	strcpy(this->mode, "live");
	this->exit = false;

	map<char, string> availableOptions = View::getViewsOptions().find(Console::initialView)->second;
	this->previousViews = {};

	this->currentView = View(Console::initialView, availableOptions);
	this->delay = 2000;
	this->loadActions();
	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView.getViewName()) != this->loadedViews.end())
	{
		this->handleView();
	}
	else
	{
		string exceptionIntro = "Please specify an existing view (";
		throw invalid_argument(exceptionIntro + this->currentView.getViewName() + ")");
	}
}

Console::Console(char *mode)
{
	this->mode = new char[strlen("debug") + 1];
	strcpy(this->mode, "debug");
	this->lastInput = '\0';
	this->exit = false;

	string viewName = "debug.view";
	map<char, string> availableOptions = View::getViewsOptions().find(Console::initialView)->second;
	this->previousViews = {};

	this->currentView = View(viewName, availableOptions);
	this->delay = 2000;
	this->loadActions();
	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView.getViewName()) != this->loadedViews.end())
	{
		this->handleView();
	}
	else
	{
		string exceptionIntro = "No debug view found: ";
		throw invalid_argument(exceptionIntro + this->currentView.getViewName());
	}
}

void Console::setLastInput(char input)
{
	if (isInCharStringMap(this->currentView.getAvailableOptions(), input))
	{
		this->lastInput = input;
	}
	else
	{
		throw invalid_argument("Please provide a valid selection.");
	}
}

vector<char> &Console::getActions()
{
	return this->actions;
}

void Console::showPrompt()
{
	cout << endl
		<< ">> ";
}

char Console::getLastInput()
{
	return this->lastInput;
}

void Console::loadViews(const fs::path &viewsFolder)
{
	if (!fs::exists(viewsFolder)
		|| !fs::is_directory(viewsFolder))
	{
		throw invalid_argument("Received an invalid directory: \"" + viewsFolder.string() + "\"");
	}

	fs::recursive_directory_iterator it(viewsFolder);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (fs::is_regular_file(*it)
			&& it->path().extension().string() == View::getViewExtension())
		{
			this->loadedViews.push_back(it->path().filename());
		}
		++it;
	}
}

void Console::loadActions()
{
	// TODO: load actions via config file
	vector<char> actions = { 'q', 'b', 'n', 'c' };

	this->actions = actions;
}

void Console::handleView()
{
	string content,
		path = Console::viewsFolder;
	path.append("\\").append(this->currentView.getViewName());

	stringstream buffer;
	ifstream viewFile(path, ios::out);

	if (viewFile.is_open())
	{
		buffer << viewFile.rdbuf();
		this->currentView.setRawFormat(buffer.str());
		this->theController = Controller(this->currentView.getViewName(), buffer.str(), View::getViewExtension());
	}
	else
	{
		cout << buffer.str()
			<< endl;
	}
	buffer.clear();
	viewFile.close();
}

void Console::renderNextView()
{
	string nextView = this->currentView.getAvailableOptions().find(this->getLastInput())->second;
	map<char, string> nextOptions = View::getViewsOptions().find(nextView)->second;

	// Cache the current view
	this->previousViews.push_back(this->currentView);
	this->currentView = View(nextView, nextOptions);

	clearScreen();
	this->handleView();
}

void Console::renderPreviousView()
{
	if (!this->previousViews.empty())
	{
		clearScreen();
		this->currentView = this->previousViews.back();
		this->handleView();
		this->previousViews.pop_back();
	}
}

void Console::reloadView()
{
	clearScreen();
	this->handleView();
}

bool Console::takeActionIfAny()
{
	if (isInCharVector(this->getActions(), this->lastInput))
	{
		switch (this->lastInput)
		{
			case 'q':
				this->breakTheLoop();
				break;
			case 'b':
				this->renderPreviousView();
				break;
			case 'n':
				// TODO: implement pagination for the questions index view
				break;
			default:
				break;
		}
		return true;
	}
	return false;
}

bool Console::shouldExit()
{
	return this->exit;
}

void Console::breakTheLoop()
{
	this->exit = true;
}

unsigned Console::getDelay()
{
	return this->delay;
}

Console::~Console()
{
	delete[] this->mode;

	clearScreen();
	cout << "Program exited the main console."
		<< endl;
}
