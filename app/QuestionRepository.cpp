#include "QuestionRepository.h"
#include "Controller.h"

string QuestionRepository::alias = "question";

string &QuestionRepository::getAlias()
{
	return QuestionRepository::alias;
}

QuestionRepository::QuestionRepository()
{
	this->defineValidation();
}

void QuestionRepository::defineValidation()
{
	// Stand back, I am going to try Regex!
	this->ValidationRules = {
		{ "title", "^.*$" },
		{ "body", "^.*$" },
		{ "keyword", "^.*$" }
	};

	this->ValidationErrors = {
		{ "title", "..." },
		{ "body", "..." },
		{ "keyword", "..." }
	};

	Controller::pushError(string(""));
}

void QuestionRepository::receiveCleanInput(map<string, string> &cleanInput)
{
	this->model.setAttributes(cleanInput);

	string action = cleanInput.find("action")->second;

	if (action == "search")
	{
		string keyword = cleanInput.find("keyword")->second;

		toast(string("Search!"), string("notice"));
	}
	else if (action == "create")
	{
		toast(string("Create!"), string("notice"));
	}
	else
	{
		Controller::pushError(string("Please provide a valid action!"));
	}
}

// Determine what to output via the model.
void QuestionRepository::echo(const string &alias)
{
	if (alias == "")
	{
	}
}

void QuestionRepository::validateItems(map<string, string> &truncatedInput)
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

QuestionRepository::~QuestionRepository()
{
}