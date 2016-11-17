#include <iostream>
#include <fstream>
#include <windows.h>
#include <filesystem>

#include "Helpers.h"
#include "ClassContainer.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

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

string Console::initialView = "home";
Console::Console()
{
	this->currentView = new char[Console::initialView.length + 1];
	strcpy(this->currentView, Console::initialView.c_str);
	this->loadViews("\\views", "views");
}
void Console::loadViews(const fs::path &root, const string &ext)
{
	if (fs::exists(root) || !fs::is_directory(root)) return;

	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;

	while (it != endit)
	{
		if (fs::is_regular_file(*it)
			&& it->path().extension() == ext)
		{
			this->loadedViews.push_back(it->path().filename());
		}
		++it;

	}
}
Console::~Console()
{
	system("cls");
	cout << "Program exited successfully..."
		<< endl;
	cin.get();
}
