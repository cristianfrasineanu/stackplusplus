#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <map>

#include "Helpers.h"
#include "View.h"

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
	vector<View> previousViews;

	vector<fs::path> loadedViews;
	vector<char> actions;

	void loadViews(const fs::path &);
	void loadActions();
public:
	Console();
	Console(char *);

	vector<char> &getActions();

	void showPrompt();
	char getLastInput();
	void setLastInput(char);
	unsigned getDelay();

	void renderView(View &);
	void renderNextView();
	void renderPreviousView();
	void reloadView();

	bool takeActionIfAny();
	bool shouldExit();
	void breakTheLoop();

	~Console();
};