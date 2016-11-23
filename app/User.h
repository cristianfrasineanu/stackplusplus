#include <iostream>
#include <string>
#include <map>

#include "Entity.h"

class User : public EntityInterface {
private:
	static string modelPath;
	static string modelAlias;

	void defineValidationRules();
public:
	User();

	void receiveCleanInput(map<string, string> &);
	void writeNewRecord();
	void validateItem();

	void retrieveItemForActive();
	void retrieveAll();

	void logPayload();
	// Set the active to false when destroying the object.
};