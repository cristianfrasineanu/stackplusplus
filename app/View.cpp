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
		findOrAskView = "find-or-ask.view",
		createView = "create.view",
		searchResultsView = "search-results.view",
		showQuestionView = "show-question.view";

	// Create non-linkable views, e.g. search results

	View::ViewsOptions = {
		{ homeView, { { '1', loginView }, { '2', signupView }, { '3', browseIndexView },
		{ '4', faqView }, { '5', helpView }, { 'q', "" } } },

		{ browseIndexView, { { 'q', "" }, { 'b', "" } } },

		{ loginView, { { 'c', dashboardView } } },

		{ signupView, { { 'c', dashboardView } } },

		{ dashboardView, { { '1', findOrAskView }, { '4', logoutView } } },

		{ logoutView, { { 'y', "" }, { 'b', "" } } },

		{ faqView, { { 'q', "" }, { 'b', "" } } },

		{ helpView, { { 'q', "" }, { 'b', "" } } },

		{ findOrAskView, { { 'b', "" } } },

		{ searchResultsView, { { '1', createView }, { '3', dashboardView } } },

		{ createView, { } },

		{ showQuestionView, { { '1', dashboardView } } }
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
