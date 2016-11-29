#include "View.h"

//---View---
//----------
// A view has attached to it a range of available actions 
// that determine the flow of the app.
map<string, map<char, string>> View::ViewsOptions = { { "",{ { '\0', "" } } } };
string View::ViewExtenstion = ".view";

View::View()
{
	this->viewName = new char[strlen("NO_VIEW") + 1];
	strcpy(this->viewName, "NO_VIEW");
	this->availableOptions = {};
}

View::View(string &viewName, map<char, string> &availableOptions)
{
	this->viewName = new char[viewName.size() + 1];
	strcpy(this->viewName, viewName.c_str());
	this->availableOptions = availableOptions;
}

View::View(const View &view)
{
	this->viewName = new char[strlen(view.viewName) + 1];
	strcpy(this->viewName, view.viewName);
	this->availableOptions = view.availableOptions;
}

map<char, string> &View::getAvailableOptions()
{
	return this->availableOptions;
}

char *View::getViewName()
{
	return this->viewName;
}

void View::setRawFormat(string &rawFormat)
{
	this->rawFormat = rawFormat;
}

void View::loadViewsOptions()
{
	// TODO: load ViewsOptions via config file
	string homeView = "home.view",
		loginView = "login.view",
		signupView = "signup.view",
		browseIndexView = "browse-index.view",
		faqView = "faq.view",
		helpView = "help.view",
		dashboardView = "dashboard.view",
		logoutView = "logout.view",
		findOrAsk = "search-or-ask.view";

	View::ViewsOptions = {
		{ homeView, { { '1', "login.view" }, { '2', "signup.view" }, { '3', "browse-index.view" },
		{ '4', "faq.view" }, { '5', "help.view" }, { 'q', "quit" } } },

		{ browseIndexView, { { 'q', "quit" }, { 'b', "back" } } },

		{ loginView, { { 'c', "dashboard.view" } } },

		{ signupView, { { 'c', "dashboard.view" } } },

		{ dashboardView, { { '1', "find-or-ask.view" }, { '4', "logout.view" } } },

		{ logoutView, { { 'y', "confirm" }, { 'b', "back" } } },
		 
		{ faqView, { { 'q', "quit" }, { 'b', "back" } } },

		{ helpView, { { 'q', "quit" }, { 'b', "back" } } },
		
		{ findOrAsk, { { 'c', "search-results.view" } } }
	};
}

map<string, map<char, string>> &View::getViewsOptions()
{
	return View::ViewsOptions;
}

string View::getViewExtension()
{
	return View::ViewExtenstion;
}

// The transition can be made only between two views, synchronously.
void View::operator=(const View &view)
{
	delete[] this->viewName;

	this->viewName = new char[strlen(view.viewName) + 1];
	strcpy(this->viewName, view.viewName);
	this->availableOptions = view.availableOptions;
}

View::~View()
{
	delete[] this->viewName;
}
