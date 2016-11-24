#pragma once

#include <sstream>
#include <stdexcept>
#include <filesystem>

#include "Helpers.h"
#include "View.h"
#include "Controller.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class Console {
private:
	static string initialView;
	static string viewsFolder;
	
	char *mode;
	char lastInput;
	unsigned delay;
	bool exit;
	View currentView;
	Controller theController;
	vector<View> previousViews;

	vector<fs::path> loadedViews;
	vector<char> actions;

	void loadViews(const fs::path &);
	void loadActions();
	void renderNextView();
	void handleView();
	void renderPreviousView();
public:
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

	~Console();
};