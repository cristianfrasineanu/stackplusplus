#include <map>

#include "Helpers.h"

using namespace std;

class View {
private:
	static map<string, map<char, string>> ViewsOptions;
	static string ViewExtenstion;

	char *viewName;
	string rawFormat;

	map<char, string> availableOptions;

public:
	static void loadViewsOptions();
	static map<string, map<char, string>> &getViewsOptions();
	static string getViewExtension();

	View();
	View(string &, map<char, string> &);
	View(const View &);

	map<char, string> &getAvailableOptions();
	char *getViewName();

	void setRawFormat(string &);

	void operator=(const View &);

	~View();
};