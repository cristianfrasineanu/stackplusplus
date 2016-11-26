#pragma once

#include "Helpers.h"

using namespace std;

//---Repository---
//----------------
// This entity acts like a glue between the accessor model and the actual model.
// An example would be if we want to get all the records for a certain model.
// The controller sends the request, the accessor model determines which model is needed and through
// the repository it calls the methods responsible for retrieving your data.
class RepositoryInterface {
private:
	virtual void defineValidation() = 0;
	virtual void receiveCleanInput(map<string, string> &) = 0;
protected:
	map<string, string> ValidationRules;
	map<string, string> ValidationErrors;
public:
	virtual void validateItems(map<string, string> &) = 0;

	virtual ~RepositoryInterface();
};