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
		{ "action", "^(?!.*\\W+)(?!.*[A-Z]+)[a-z]+$" }
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

// If the user tries to login, compare the password with the one from the db and mark it as active.
// Determine which action it's taken based on the payload contents.
void UserRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	this->model.setAttributes(cleanInput);

	string action = cleanInput.find("action")->second;

	if (action == "login")
	{
		try
		{
			User user = this->model.getAfterUser(cleanInput.find("username")->second);
			if (!strcmp(user.password, cleanInput.find("password")->second.c_str()) 
				&& !strcmp(user.deleted_at, "")
				&& user.banned != true)
			{
				this->model.markAs(string("active"), user.id);
				toast(string("Login successful! Please press -c- confirm your access to the dashboard."), string("success"));
				printString("\n");
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
	else if (action == "signup")
	{
		// Try finding the user and validate the request.
		if (this->model.userExists(cleanInput.find("username")->second)) {
			Controller::pushError(string("The username already exists!"));
		}
		else {
			toast(string("Account created successfully! Please press -c- confirm your access to the dashboard."), string("success"));
			printString("\n");

			this->model.save();
		}
	}
	else
	{
		Controller::pushError(string("Please provide a valid action!"));
	}
	// TODO: for a ban action, check if the current user has the according privilegies.
}

string &UserRepository::getAlias()
{
	return UserRepository::alias;
}

void UserRepository::logOutUser()
{
	UserRepository users;

	try
	{
		User activeUser = users.model.getActive();
		users.model.markAs(string("logged_out"), activeUser.id);
		users.model.save();
	}
	catch (const exception &e)
	{
		toast(string(e.what()), string("error"));
	}
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
			toast("\n\n" + string(e.what()) + "\n", string("error"));
		}
	}

	if (Controller::getErrorBag().empty())
	{
		this->receiveCleanInput(truncatedInput);
	}
}

UserRepository::~UserRepository()
{
}