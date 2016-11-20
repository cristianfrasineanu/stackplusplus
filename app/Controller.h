#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Helpers.h"

using namespace std;

class Controller {
private:
	static string viewInputFormat;
	static string viewOutputFormat;

	char *controllerName;
	vector<string> controllerAttributions;
	string viewChunk;

	void prepareView();
	void prepareViewInput();
	// TODO: interpolate the view strings for output with the according variables received from the model.
public:
	static string &getViewInputFormat();
	static string &getViewOutputFormat();
	static bool hasInput(string &);

	Controller();
	Controller(char *, string &, string &);

	vector<string> &getControllerAttributions();
	char *getControllerName();

	void operator=(const Controller &);

	~Controller();
};