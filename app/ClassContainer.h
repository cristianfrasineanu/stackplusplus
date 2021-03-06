#include <iostream>
#include <filesystem>
#include <map>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class View {
private:
	static map<string, map<char, string>> ViewsOptions;

	char *viewName;
	bool hasInterpolation;

	map<char, string> availableOptions;

	View();
public:
	View(string &, map<char, string> &, bool);

	map<char, string> &getAvailableOptions();
	char *getViewName();
	static void loadViewsOptions();
	static map<string, map<char, string>> &getViewsOptions();

	~View();
};

class Console {
private:
	static string initialView;
	static char *viewsFolder;

	char *mode;
	char lastInput;
	unsigned delay;
	bool exit;
	View *currentView;
	vector<View *> previousViews;

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
	void takeActionIfAny();
	bool shouldExit();
	void breakTheLoop();

	~Console();
};