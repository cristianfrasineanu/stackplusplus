#include "Console.h"

//---Console---
//-------------
// An initial state and a synchronous processing of the views is necessary due to the lack of console.
// It acts like a glue between all other components of the framework.
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

	this->delay = 2000;
	this->loadActions();
	this->loadViews(Console::viewsFolder);

	this->currentView = View(Console::initialView, availableOptions);

	if (isInVector(this->loadedViews, Console::initialView))
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

	this->delay = 2000;
	this->loadActions();
	this->loadViews(Console::viewsFolder);

	this->currentView = View(viewName, availableOptions);

	if (isInVector(this->loadedViews, viewName))
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
	if (isInMap(this->currentView.getAvailableOptions(), input))
	{
		this->lastInput = input;
	}
	else
	{
		throw invalid_argument("Please provide a valid selection.");
	}
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
	vector<char> actions = { 'q', 'b', 'n', 'y' };

	this->actions = actions;
}

void Console::handleView()
{
	string content,
		path = Console::viewsFolder;
	path.append("\\").append(this->currentView.getViewName());

	stringstream buffer;
	ifstream viewFile(path, ios::in);

	if (viewFile.is_open())
	{
		buffer << viewFile.rdbuf();
		this->currentView.setRawFormat(buffer.str());

		this->theController = Controller(this->currentView.getViewName(), buffer.str(), View::getViewExtension());
		if (!Controller::getErrorBag().empty())
		{
			toast(string("There were some issues:"), string("error"));
			printVector(Controller::getErrorBag());

			sleepAndClearBuffer(3 * this->delay);
			this->reloadView();
		}
		// TODO: provide an option to the users to cancel what they want to do.
		// i.e. show the errors and ask if they want to try again or go back.

		buffer.clear();
		viewFile.close();
	}
	else
	{
		throw system_error(error_code(3, system_category()), string("The input stream from the view couldn't be opened."));
	}
}

// Prepare the next view and also cache the current one.
void Console::renderNextView()
{
	string nextView = this->currentView.getAvailableOptions().find(this->getLastInput())->second;
	map<char, string> nextOptions = View::getViewsOptions().find(nextView)->second;

	this->previousViews.push_back(this->currentView);
	this->currentView = View(nextView, nextOptions);

	clearScreen();
	this->handleView();
}

// Render a custom view without caching the previous one as it breaks the normal flow.
void Console::renderNextView(string &viewName)
{
	map<char, string> nextOptions = View::getViewsOptions().find(viewName)->second;

	this->previousViews.erase(this->previousViews.begin(), this->previousViews.end());
	this->currentView = View(viewName, nextOptions);

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

void Console::takeActionOrNext()
{
	if (isInVector(this->actions, this->lastInput))
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
				// TODO: implement pagination
				break;
			case 'y':
				UserRepository::logOutUser();
				// TODO: Decouple this somehow
				this->renderNextView(string(Console::initialView));
			default:
				break;
		}
	}
	else
	{
		this->renderNextView();
	}
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

	// Dump all the records...
	UserModel::dumpFile();

	clearScreen();
	cout << "Program exited the main console."
		<< endl;
}
