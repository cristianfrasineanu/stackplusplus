#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <map>

#include "Helpers.h"
#include "ClassContainer.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

//---View---
//----------
// A view has attached to it a range of available actions or certain verbs that are used by the console to do some action.
// It's basically a dictionary holding the options mapping
map<string, map<char, string>> View::ViewsOptions = { { "", {{'\0', ""}} } };

View::View(string &viewName, map<char, string> &availableOptions, bool hasInterpolation)
{
	this->viewName = new char[strlen(viewName.c_str()) + 1];
	strcpy(this->viewName, viewName.c_str());
	this->availableOptions = availableOptions;
	this->hasInterpolation = hasInterpolation;
}

map<char, string> &View::getAvailableOptions()
{
	return this->availableOptions;
}

char *View::getViewName()
{
	return this->viewName;
}

void View::loadViewsOptions()
{
	string homeView = "home.view",
		loginView = "login.view",
		signupView = "signup.view",
		browseIndexView = "browse-index.view",
		faqView = "faq.view",
		helpView = "help.view";

	View::ViewsOptions = {
							{ homeView, { { '1', "login.view" }, { '2', "signup.view" }, { '3', "browse-index.view" },
										  { '4', "faq.view" }, { '5', "help.view" }, { 'q', "quit" } } },
							{ loginView, { { '1', "browse-index.view" }, { 'q', "quit" } } },
							{ signupView, { { 'q', "quit" } } },
							{ browseIndexView, { {'q', "quit"} } },
							{ faqView, { {'q', "quit"} } },
							{ helpView, { { 'q', "quit" } } }
	};
}

map<string, map<char, string>> &View::getViewsOptions()
{
	return View::ViewsOptions;
}

View::~View()
{
	delete[] this->viewName;
}

//---Console---
//-------------
// We need an initial state, because we don't have any means like mapping views to HTTP routes
string Console::initialView = "home.view";
char *Console::viewsFolder = "..\\views";

Console::Console()
{
	this->mode = new char[strlen("live") + 1];
	strcpy(this->mode, "live");
	this->exit = false;

	map<char, string> availableOptions = View::getViewsOptions().find(Console::initialView)->second;

	this->currentView = new View(Console::initialView, availableOptions, false);
	this->delay = 2000;

	this->loadActions();
	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView->getViewName()) != this->loadedViews.end())
	{
		this->renderView(*this->currentView);
	}
	else
	{
		string exceptionIntro = "Please specify an existing view (";
		throw invalid_argument(exceptionIntro + this->currentView->getViewName() + ")");
	}
}

Console::Console(char *mode)
{
	this->mode = new char[strlen("debug") + 1];
	strcpy(this->mode, "debug");
	this->exit = false;

	string viewName = "debug.view";
	map<char, string> availableOptions = View::getViewsOptions().find(Console::initialView)->second;

	this->currentView = new View(viewName, availableOptions, true);
	this->delay = 2000;

	this->loadActions();
	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView->getViewName()) != this->loadedViews.end())
	{
		this->renderView(*this->currentView);
	}
	else
	{
		string exceptionIntro = "No debug view found: ";
		throw invalid_argument(exceptionIntro + *this->currentView->getViewName());
	}
}

void Console::setLastInput(char input)
{
	if (isInCharStringMap(this->currentView->getAvailableOptions(), input))
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
			&& it->path().extension() == ".view")
		{
			this->loadedViews.push_back(it->path().filename());
		}
		++it;
	}
}

void Console::loadActions()
{
	vector<char> actions = { 'q', 'b', 'n' };

	this->actions = actions;
}

void Console::renderView(View &view)
{
	string content;
	string path = Console::viewsFolder;
	path.append("\\").append(view.getViewName());
	stringstream buffer;
	ifstream viewFile(path, ios::out);

	if (viewFile.is_open())
	{
		buffer << viewFile.rdbuf();
		cout << buffer.str()
			<< endl;
		buffer.clear();
	}
	else
	{
		throw system_error(error_code(3, system_category()), "The view stream couldn't be opened");
	}

	viewFile.close();
}

void Console::renderNextView()
{
	string nextView = this->currentView->getAvailableOptions().find(this->getLastInput())->second;
	map<char, string> nextOptions = View::getViewsOptions().find(nextView)->second;

	// Cache the current view
	this->previousViews.push_back(this->currentView);
	// The name and then the corresponding options map to the view from ViewsOptions and the hasInterpolation boolean
	this->currentView = new View(nextView,
								 nextOptions,
								 false);

	//TODO: detemine if the view has interpolation enabled in order to replace the template strings or to splice the view in certain places
	system("cls");
	this->renderView(*this->currentView);
}

void Console::renderPreviousView()
{
	if (!this->previousViews.empty())
	{
		this->renderView(*this->previousViews.back());
		this->previousViews.pop_back();
	}
}

void Console::reloadView()
{
	system("cls");
	this->renderView(*this->currentView);
}

void Console::takeActionIfAny()
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
		}
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
	delete this->currentView;
	delete[] this->mode;

	system("cls");
	cout << "Program exited the main console."
		<< endl;
}
