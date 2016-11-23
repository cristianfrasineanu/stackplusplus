#include "UserRepository.h"

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
		{ "fullname", "Please enter a valid firstname and lastname." },
		{ "email", "Please enter a valid email address." },
		{ "username", "Your username should have 8-20 characters, should start only with a letter, doesn't repeat special characters and finishes with a letter or a number." },
		{ "password", "Your password should habe 5-16 characters, and contain an uppercase letter, a number and a special character." },
	};
}

UserRepository::UserRepository()
{
	this->defineValidation();
	this->model = new UserModel();
}

void UserRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	log(cleanInput, "cleanInput", "after validation");

	this->model->setAttributes(cleanInput);
	this->model->save();
}

void UserRepository::validateItems(map<string, string> &serializedInput)
{
	for (map<string, string>::iterator it = serializedInput.begin(); it != serializedInput.end(); it++)
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

UserRepository::~UserRepository()
{
	delete this->model;
}


