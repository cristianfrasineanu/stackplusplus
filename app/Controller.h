#pragma once

#include <fstream>

#include "Helpers.h"
#include "Model.h"

using namespace std;

class Controller {
private:
	static string userInputString;
	static string userOutputString;
	static string actionString;

	static vector<string> errorBag;

	char *controllerName;
	vector<string> controllerAttributions;
	map<string, string> userInputs;
	string viewChunk;
	Model model;

	void justShow();
	void prepareView();
	void prepareViewInput(const string &, const string &);
	void prepareViewOutput(const string &, const string &);
	void prepareAction(string &);
	void chopChunkAndGetAlias(string &, const string &);
public:
	static void pushError(string &);
	static vector<string> getErrorBag();
	static string hasRedirectTo;

	Controller();
	Controller(char *, string &, string &);

	bool hasInput(const string &);
	bool hasOutput(const string &);

	vector<string> &getControllerAttributions();
	char *getControllerName();

	void operator=(const Controller &);

	~Controller();
};