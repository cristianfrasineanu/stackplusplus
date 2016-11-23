#include "User.h"

string User::modelPath = "..\\db\\user.store";
string User::modelAlias = "user";

void User::defineValidationRules()
{
	this->ValidationRules = {};
}

User::User()
{
	this->defineValidationRules();
}

void User::receiveCleanInput(map<string, string>& cleanInput)
{
	cout << "Got the input, doing something with it..."
		<< endl;
}

void User::writeNewRecord()
{
	//
}

void User::validateItem()
{
	// Appli validation rules for the next item
}

void User::retrieveItemForActive()
{
	// Search for the record having active set to true
}

void User::retrieveAll()
{
	// Print everything
}

void User::logPayload()
{
	// 
}


