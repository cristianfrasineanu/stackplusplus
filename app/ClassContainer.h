#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class View {
private:
	char *viewName;
	bool hasInterpolation;
	vector<char> availableOptions;
	View();
public:
	View(char *, vector<char>, bool);
	vector<char> getAvailableOptions();
	char *getViewName();
	~View();
};

class Console {
private:
	static char *initialView;
	static char *viewsFolder;
	View *currentView;
	char *mode;
	char lastInput;
	unsigned delay;

	vector<fs::path> loadedViews;

	void loadViews(const fs::path &);
public:
	Console();
	Console(char *);

	char getLastInput();
	void setLastInput(char);
	void renderView(View &);
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