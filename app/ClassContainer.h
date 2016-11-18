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
	View(string, map<char, string>, bool);

	map<char, string> getAvailableOptions();
	char *getViewName();
	static void loadViewsOptions();

	~View();
};

class Console {
private:
	static string initialView;
	static char *viewsFolder;
	char *mode;
	char lastInput;
	unsigned delay;
	View *currentView;
	vector<fs::path> loadedViews;

	void loadViews(const fs::path &);
public:
	Console();
	Console(char *);

	char getLastInput();
	void setLastInput(char);
	void renderView(View &);
	void renderNextView();
	void reloadView();
	unsigned getDelay();

	~Console();
};

class User {
private:
	const unsigned uuid;
	char *nick;
public:
	static unsigned count;
	static void setFromLastUuid();
	User();
	~User();
	unsigned getUuid();
};