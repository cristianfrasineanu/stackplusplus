#pragma once

#include <string>
#include <map>

#include "Helpers.h"

using namespace std;

class EntityInterface {
private:
	virtual void defineValidationRules() = 0;
protected:
	map<string, string> ValidationRules;

	// Might change, as we writing only string to the DB
	map<string, string> payLoad;
public:
	virtual void receiveCleanInput(map<string, string> &) = 0;
	virtual void writeNewRecord() = 0;
	virtual void validateItem() = 0;

	virtual void retrieveItemForActive() = 0;
	virtual void retrieveAll() = 0;

	virtual void logPayload() = 0;
};