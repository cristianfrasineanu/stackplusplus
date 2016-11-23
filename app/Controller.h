#include <fstream>

#include "Helpers.h"
#include "Model.h"

using namespace std;

class Controller {
private:
	static string viewInputFormat;
	static string viewOutputFormat;

	char *controllerName;
	vector<string> controllerAttributions;
	map<string, string> userInputs;
	string viewChunk;
	Model model;

	void justShow();
	void prepareView();
	void prepareViewInput(const string &, const string &);
	// TODO: take the chunk one by one for output and request output from model for each output variable
public:
	Controller();
	Controller(char *, string &, string &);

	bool hasInput(const string &);
	bool hasOutput(const string &);

	vector<string> &getControllerAttributions();
	char *getControllerName();

	void chopChunkAndGetAlias(string &);

	void operator=(const Controller &);

	~Controller();
};