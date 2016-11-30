#pragma once

#include <sstream>
#include <stdexcept>

#include "Helpers.h"
#include "View.h"
#include "Controller.h"

using namespace std;

class Console {
private:
	static string initialView;
	static string viewsFolder;
	
	char *mode;
	unsigned delay = 2000;
	char lastInput = '\0';
	bool exit = false;

	View currentView;
	Controller theController;
	vector<View> previousViews;

	vector<fs::path> loadedViews;
	vector<char> actions;

	void loadViews(const fs::path &);
	void loadActions();

	void renderNextView();
	void renderNextView(string &);

	void renderPreviousView();
	void handleView();

	void handleErrors();
	void handleRedirect();
public:
	static void initTerminal();

	Console();
	Console(char *);

	char getLastInput();
	void setLastInput(char);
	void takeActionOrNext();
	bool shouldExit();
	void breakTheLoop();

	void showPrompt();
	unsigned getDelay();

	void reloadView();
	void provideRetry();

	~Console();
};