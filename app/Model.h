#include "Helpers.h"
#include "RepositoryInterface.h"
#include "UserRepository.h"

using namespace std;

class Model {
private:
	static string userModelAlias;
	static string questionModelAlias;

	map<string, string> rawInput;
	map<string, string> serializedInput;

	RepositoryInterface *repository;

	string parseEntityName(string);
	void attachEntity(string &);
	void sendSerializedInput();
public:
	Model();

	void confirmInput(const map<string, string> &);

	~Model();
};