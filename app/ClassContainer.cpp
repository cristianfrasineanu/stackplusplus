#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

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

//---Console---
//-------------
// We need an initial state, because we don't have any means like mapping views to HTTP routes
char *Console::initialView = "home.view";
char *Console::viewsFolder = "..\\views";

Console::Console()
{
	this->mode = new char[strlen("live") + 1];
	strcpy(this->mode, "live");
	this->currentView = new char[strlen(Console::initialView) + 1];
	strcpy(this->currentView, Console::initialView);
	this->availableOptions = { '1', '2', '3', '4', '5', 'q' };
	this->delay = 2000;

	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView) != this->loadedViews.end())
	{
		this->renderView(this->currentView);
	}
	else
	{
		string exceptionIntro = "Please specify an existing view (";
		throw invalid_argument(exceptionIntro + this->currentView + ")");
	}
}

Console::Console(char *mode)
{
	this->mode = new char[strlen("debug") + 1];
	strcpy(this->mode, "debug");
	this->currentView = new char[strlen("debug.view") + 1];
	strcpy(this->currentView, "debug.view");

	this->loadViews(Console::viewsFolder);

	if (find(this->loadedViews.begin(), this->loadedViews.end(), this->currentView) != this->loadedViews.end())
	{
		this->renderView(this->currentView);
	}
	else
	{
		string exceptionIntro = "No debug view found: ";
		throw invalid_argument(exceptionIntro + this->currentView);
	}
}

void Console::setLastInput(char input)
{
	if (isInCharVector(this->availableOptions, input))
	{
		this->lastInput = input;
	}
	else {
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
		throw invalid_argument("Received an invalid directory: \"" + viewsFolder.string()+ "\"");
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

void Console::renderView(char *view)
{
	string content;
	string path = Console::viewsFolder;
	path.append("\\").append(view);
	stringstream buffer;
	ifstream viewFile(path, ios::out);

	if (viewFile.is_open())
	{
		buffer << viewFile.rdbuf();
		cout << buffer.str()
			<< endl;
		buffer.clear();
	}

	viewFile.close();
}

void Console::reloadView()
{
	system("cls");
	this->renderView(this->currentView);
}

unsigned Console::getDelay()
{
	return this->delay;
}

Console::~Console()
{
	delete[] this->currentView;
	delete[] this->mode;

	system("cls");
	cout << "Program exited successfully..."
		<< endl;
}

