#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class Console {
private:
	static char *initialView;
	static char *viewsFolder;
	char *currentView;
	char *mode;
	char lastInput;
	unsigned delay;

	vector<fs::path> loadedViews;
	vector<char> availableOptions;

	void loadViews(const fs::path &);
public:
	Console();
	Console(char *);

	char getLastInput();
	void setLastInput(char);
	void renderView(char *);
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