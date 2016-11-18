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

//--- User --- 
//------------
unsigned User::count = 0;

void User::setFromLastUuid()
{
	// Get the last uuid from the db file

	User::count = 30;
}

User::User() : uuid(User::count++)
{
	this->nick = new char[4];
}

User::~User()
{
	delete[] this->nick;
}

unsigned User::getUuid()
{
	return this->uuid;
}

//---View---
//----------
map<string, map<char, string>> View::ViewsOptions = { { "", {{'\0', ""}} } };

View::View(string viewName, map<char, string> availableOptions, bool hasInterpolation)
{
	this->viewName = new char[strlen(viewName.c_str()) + 1];
	strcpy(this->viewName, viewName.c_str());
	this->availableOptions = availableOptions;
	this->hasInterpolation = hasInterpolation;
}

map<char, string> View::getAvailableOptions()
{
	return this->availableOptions;
}

char *View::getViewName()
{
	return this->viewName;
}

void View::loadViewsOptions()
{
	string someView = "aView",
		anotherView = "aaaView";

	View::ViewsOptions = { { someView, {{'1', "theview.view"}}},
					   {anotherView, {{'2', "someview.view"}}} };
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
	map<char, string> availableOptions = { {'1', "login.view"}, {'2', "signup.view"}, {'3', "browse-index.view"}, {'4', "faq.view"}, {'q', "quit"} };

	this->currentView = new View(Console::initialView, availableOptions, false);
	this->delay = 2000;

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
	string viewName = "debug.view";
	this->currentView = new View(viewName, { {'q', "quit"} }, true);

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
		throw system_error(error_code(500, system_category()), "The view stream couldn't be opened.");
	}

	viewFile.close();
}

void Console::renderNextView()
{
	this->currentView = new View(this->currentView->getAvailableOptions().find(this->getLastInput())->second, { {'5', "lala"} }, false);

	//TODO: finish the renderer
}

void Console::reloadView()
{
	system("cls");
	this->renderView(*this->currentView);
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
	cout << "Program exited successfully..."
		<< endl;
}
