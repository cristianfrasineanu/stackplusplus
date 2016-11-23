#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Helpers.h"
#include "Model.h"

using namespace std;

class Controller {
private:
	static string viewInputFormat;
	static string viewOutputFormat;

	char *controllerName;
	vector<string> controllerAttributions;
	string viewChunk;
	Model model;

	void justShow();
	void prepareView();
	void prepareViewInput(string &, string &);
	// TODO: take the chunk one by one for output and request output from model for each output variable
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