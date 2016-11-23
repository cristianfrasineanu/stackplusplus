#include "UserRepository.h"

void UserRepository::defineValidation()
{
	this->ValidationRules = {
		{ "username", "^(?=.{8,19}([a-zA-Z0-9]+)$)(?![^a-zA-Z])(?!.*[!_\45.]{2})[a-zA-Z0-9.\45_]+$" },
		{ "password", "^(?=.{5,16}$)(?=.*[A-Z])(?=.*[0-9])(?=.*[!\45_@.$#])[a-zA-Z0-9!\45_@.$#]+$" }
	};

	this->ValidationErrors = {
		{ "username", "Your username should have 8-20 characters, should start only with a letter, doesn't repeat special characters and finishes with a letter or a number." },
		{ "password", "Your password should habe 6-16 characters, and contain an uppercase letter, a number and a special character." }
	};
}

UserRepository::UserRepository()
{
	this->defineValidation();
}

void UserRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	log(cleanInput, "cleanInput", "after validation");
	// Load the record into the model
}

void UserRepository::writeNewRecord()
{
	//
}

void UserRepository::validateItems(map<string, string> &serializedInput)
{
	map<string, string> serializedCopy = serializedInput;

	for (map<string, string>::iterator it = serializedCopy.begin(); it != serializedCopy.end(); it++)
	{
		try
		{
			if (!regex_match(it->second.c_str(), regex(this->ValidationRules[it->first.c_str()])))
			{
				throw invalid_argument(this->ValidationErrors[it->first.c_str()]);
			}
		}
		catch (const regex_error &e)
		{
			cout << endl
				<< e.what()
				<< endl
				<< e.code()
				<< endl;
		}
	}

	this->receiveCleanInput(serializedInput);
}

void UserRepository::retrieveItemForActive()
{
	// Search for the record having active set to true
}

void UserRepository::retrieveAll()
{
	// Print everything
}


