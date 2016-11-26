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
		{ "password", "^(?=.{5,16}$)(?=.*[A-Z])(?=.*[0-9])(?=.*[!\\-_@.$#])[a-zA-Z0-9!\\-_@.$#]+$" },
		{ "logout", "^y|Y|n|N$" }
	};

	this->ValidationErrors = {
		{ "fullname", "Invalid full name." },
		{ "email", "Invalid email address." },
		{ "username", "Username should be 8-20 characters long, should start only with a letter and should not repeat special characters." },
		{ "password", "Password should be 5-16 characters long, and contain at least an uppercase letter, a number and a special character." },
	};

	Controller::pushError(string(""));
}

UserRepository::UserRepository()
{
	this->defineValidation();
}

void UserRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	this->model.setAttributes(cleanInput);

	// TODO: find a way to log ou the user and change the views without providing further input after confirming.
	if (cleanInput.find("logout") != cleanInput.end())
	{
		char choice[2];
		strcpy(choice, cleanInput.find("logout")->second.c_str());
		if ((char)tolower(choice[0]) == 'y')
		{
			//this->model.getActive();
			//this->model.markAs(string("nonactive"))
		}
		else
		{
			// Go back
		}
	}
	// If the user tries to login, compare the password with the one from the db.
	else if (cleanInput.find("fullname") == cleanInput.end())
	{
		try
		{
			User user = this->model.getAfterUser(cleanInput.find("username")->second);
			if (user.password == cleanInput.find("password")->second && user.banned != true && user.deleted_at == "")
			{
				this->model.markAs(string("active"), user.id);
				toast("Login successful! Please press -c- confirm your access to the dashboard.", string("success"));
			}
			else
			{
				Controller::pushError(string("Incorrect password!"));
			}
		}
		catch (const invalid_argument &e)
		{
			Controller::pushError(string(e.what()));
		}
	}
	else
	{
		this->model.save();
		toast("Account created successfully! Please press -c- confirm your access to the dashboard.", string("success"));
	}
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
				Controller::pushError(this->ValidationErrors[it->first.c_str()]);
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
	if (Controller::getErrorBag().empty())
	{
		this->receiveCleanInput(truncatedInput);
	}
}

UserRepository::~UserRepository()
{
}