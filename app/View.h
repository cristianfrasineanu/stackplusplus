#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <map>

#include "Helpers.h"

using namespace std;

class View {
private:
	static map<string, map<char, string>> ViewsOptions;

	char *viewName;
	bool hasInterpolation;

	map<char, string> availableOptions;

public:
	static void loadViewsOptions();
	static map<string, map<char, string>> &getViewsOptions();

	View();
	View(string &, map<char, string> &, bool);
	View(const View &);

	map<char, string> &getAvailableOptions();
	char *getViewName();

	void operator=(const View &);
	~View();
};