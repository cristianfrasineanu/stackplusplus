#include "UserRepository.h"
#include "Controller.h"

string UserRepository::alias = "user";

void UserRepository::defineValidation()
{
	// Stand back, I am going to try Regex!
	this->ValidationRules = {
		{ "fullname", "^(?=.*(?:[\\s\\-])([a-zA-Z]+\\s?)+)([a-zA-Z]+)(?:[\\s\\-]).*$" },
		{ "email", "^(?!.*[._]{2})[a-z0-9._]+@[a-z0-9]+(\\.[a-z]{1,3}){1,2}$" },
		{ "username", "^(?=.{7,19}$)(?![^a-zA-Z0-9])(?!.*[!_\\-\\.]{2})[a-zA-Z0-9\\.\\-_]+$" },
		{ "password", "^(?=.{5,16}$)(?=.*[A-Z])(?=.*[0-9])(?=.*[!\\-_@.$#])[a-zA-Z0-9!\\-_@.$#]+$" }
	};

	this->ValidationErrors = {
		{ "fullname", "Invalid full name." },
		{ "email", "Invalid email address." },
		{ "username", "Username should be 8-20 characters long, should start only with a letter and should not repeat special characters." },
		{ "password", "Password should be 5-16 characters long, and contain at least an uppercase letter, a number and a special character." },
	};

	this->errorsBag = {};
}

UserRepository::UserRepository()
{
	this->defineValidation();
	this->model = new UserModel();
}

void UserRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	this->model->setAttributes(cleanInput);
	this->model->save();
}

string &UserRepository::getAlias()
{
	return UserRepository::alias;
}

void UserRepository::validateItems(map<string, string> &truncatedInput)
{
	for (map<string, string>::iterator it = truncatedInput.begin(); it != truncatedInput.end(); it++)
	{
		try
		{
			if (!regex_match(it->second.c_str(), regex(this->ValidationRules[it->first.c_str()])))
			{
				this->errorsBag.push_back(this->ValidationErrors[it->first.c_str()]);
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

	// If there are no errors, send it along.
	if (this->errorsBag.empty())
	{
		this->receiveCleanInput(truncatedInput);
	}

	// Let the console know about the errors.
	Controller::setErrorsBag(this->errorsBag);
}

void UserRepository::retrieveItemForActive()
{
	// Search for the record having active set to true.
}

void UserRepository::retrieveAll()
{
	// Print everything.
}

UserRepository::~UserRepository()
{
	delete this->model;
}