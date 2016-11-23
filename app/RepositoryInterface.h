#pragma once

#include <string>
#include <map>

#include "Helpers.h"

using namespace std;

//---Entity---
//------------
// This entity acts like a repository interface between the accessor model and the actual model.
// An example would be if we want to get all the records for a certain model.
// The controller sends the request, the accessor model determines which model is needed and through
// the repostory calls the methods responsible for retrieveing the data.
class RepositoryInterface {
private:
	virtual void defineValidation() = 0;
protected:
	map<string, string> ValidationRules;
	map<string, string> ValidationErrors;
	virtual void receiveCleanInput(map<string, string> &) = 0;
public:
	virtual void writeNewRecord() = 0;
	virtual void validateItems(map<string, string> &) = 0;

	virtual void retrieveItemForActive() = 0;
	virtual void retrieveAll() = 0;
};