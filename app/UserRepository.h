#include <iostream>
#include <string>
#include <map>
#include <regex>

#include "RepositoryInterface.h"

class UserRepository : public RepositoryInterface {
private:
	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	UserRepository();

	void writeNewRecord();
	void validateItems(map<string, string> &);

	void retrieveItemForActive();
	void retrieveAll();

	// Set the active to false when destroying the object.
};