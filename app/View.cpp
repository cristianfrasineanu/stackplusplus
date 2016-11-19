#include "View.h"

//---View---
//----------
// A view has attached to it a range of available actions or certain verbs that are used by the console to do some action.
// It's basically a dictionary holding the options mapping.
map<string, map<char, string>> View::ViewsOptions = { { "",{ { '\0', "" } } } };

View::View()
{
	this->viewName = new char[strlen("NO_VIEW") + 1];
	strcpy(this->viewName, "NO_VIEW");
	this->hasInterpolation = false;
}

View::View(string &viewName, map<char, string> &availableOptions, bool hasInterpolation)
{
	this->viewName = new char[strlen(viewName.c_str()) + 1];
	strcpy(this->viewName, viewName.c_str());
	this->availableOptions = availableOptions;
	this->hasInterpolation = hasInterpolation;
}

View::View(const View &view)
{
	this->viewName = new char[strlen(view.viewName) + 1];
	strcpy(this->viewName, view.viewName);
	this->hasInterpolation = view.hasInterpolation;
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

		{ loginView, { { '1', "browse-index.view" }, { 'q', "quit" }, { 'b', "back" } } },

		{ signupView, { { 'q', "quit" }, { 'b', "back" } } },

		{ browseIndexView, { { 'q', "quit" }, { 'b', "back" } } },

		{ faqView, { { 'q', "quit" }, { 'b', "back" } } },

		{ helpView, { { 'q', "quit" }, { 'b', "back" } } }
	};
}

map<string, map<char, string>> &View::getViewsOptions()
{
	return View::ViewsOptions;
}

// Prevent multiple assignments of views, i.e. a view can transition only once and cannot split into multiple views.
void View::operator=(const View &view)
{
	delete[] this->viewName;

	this->viewName = new char[strlen(view.viewName) + 1];
	strcpy(this->viewName, view.viewName);
	this->hasInterpolation = view.hasInterpolation;
	this->availableOptions = view.availableOptions;
}

View::~View()
{
	delete[] this->viewName;
}
