#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Helpers.h"
#include "Entity.h"
#include "User.h"

using namespace std;

class Model {
private:
	static string userModelAlias;
	static string questionModelAlias;

	vector<string> accessHistory;
	map<string, string> ready;

	EntityInterface *currentModel;

	string parseModelName(string);
	void attachModel(string &);
public:
	Model();

	void sendSerializedInput(map<string, string> &);
	void confirmInput();

	~Model();
};