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
	map<string, string> userInputs;
	string viewChunk;
	// Model model;

	void justShow();
	void prepareView();
	void prepareViewInput(string &, string &);
	// TODO: interpolate the view strings for output with the according variables received from the model.
public:
	Controller();
	Controller(char *, string &, string &);

	bool hasInput(string &);
	bool hasOutput(string &);

	vector<string> &getControllerAttributions();
	char *getControllerName();

	void chopChunkAndGetAlias(string &);

	void operator=(const Controller &);

	~Controller();
};