#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <map>

#include "View.h"
#include "Helpers.h"
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
public:
	Console();
	Console(char *);

	vector<char> &getActions();
	char getLastInput();

	void setLastInput(char);
	bool takeActionIfAny();
	bool shouldExit();
	void breakTheLoop();

	void showPrompt();
	unsigned getDelay();

	void handleView();
	void renderNextView();
	void renderPreviousView();
	void reloadView();

	~Console();
};