#include "Console.h"

//---Console---
//-------------
// An initial state and a synchronous processing of the views is necessary due to the lack of console.
// It acts like a glue between all other components of the framework.
string Console::initialView = "home.view";
string Console::viewsFolder = "..\\views";

// Prepare a standard screen that buffers all keys, doesn't echo input,
// waits for the input and isn't affected by interrupt characters.
void Console::initTerminal()
{
	initscr();

	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, FALSE);
	resize_term(150, 150);

	// Scroll to the bottom if the content overflows.
	scrollok(stdscr, TRUE);

	start_color();
	use_default_colors();

	// Define color pairs to be assign to stdscr.
	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	wbkgd(stdscr, COLOR_PAIR(1) | A_BOLD);
	refresh();
}

void Console::showPrompt()
{
	printString(">> ");
}

void Console::loadActions()
{
	// TODO: load actions via config file
	vector<char> actions = { 'q', 'b', 'n', 'y' };

	this->actions = actions;
}

Console::Console()
{
	this->mode = new char[strlen("live") + 1];
	strcpy(this->mode, "live");

	View::loadViewsOptions();
	map<char, string> availableOptions = View::getViewsOptions().find(Console::initialView)->second;
	this->previousViews = {};

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
		throw invalid_argument(exceptionIntro + this->currentView.getViewName() + ")\n");
	}
}

Console::Console(char *mode)
{
	this->mode = new char[strlen("debug") + 1];
	strcpy(this->mode, "debug");

	string viewName = "debug.view";
	View::loadViewsOptions();
	map<char, string> availableOptions = View::getViewsOptions().find(viewName)->second;
	this->previousViews = {};

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
		throw invalid_argument(exceptionIntro + this->currentView.getViewName() + ")\n");
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
			printString("\n");
			printVector(Controller::getErrorBag());

			// Empty the bag and provide a retry step.
			Controller::pushError(string(""));
			this->provideRetry();
		}

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

void Console::provideRetry()
{
	printString("\n");
	toast(string("Would you like to retry or go back? (Y/b)\n"), string("notification"));
	this->showPrompt();
	do
	{
		this->lastInput = (char)tolower(getch());
		if (this->lastInput == 'y')
		{
			this->reloadView();
		}
		else if (this->lastInput == 'b')
		{
			this->renderPreviousView();
		}
	} while (this->lastInput != 'y' && this->lastInput != 'b');
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
				// TODO: Decouple this somehow
				UserRepository::logOutUser();
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

	// Revert to default terminal and display notice.
	clearScreen();
	wbkgd(stdscr, COLOR_PAIR(1));
	printString("Program exited the main console.\n");

	sleepAndFlushInput(this->delay);

	endwin();
	refresh();
}
