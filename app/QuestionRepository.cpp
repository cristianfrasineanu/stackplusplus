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
		{ "category", "^.*$" },
		{ "keyword", "^.*$" },
		{ "action", "(?!.*\\W+)(?!.*[A-Z]+)[a-z]+$" }
	};

	this->ValidationErrors = {
		{ "title", "..." },
		{ "body", "..." },
		{ "category", "..." },
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
		bool foundAnyRelated = false;

		vector<Question> results = this->model.retrieveAll();
		vector<Question>::iterator it = results.begin();

		while (it != results.end())
		{
			if (string((*it).title).find(keyword) != string::npos || string((*it).body).find(keyword) != string::npos)
			{
				foundAnyRelated = true;
				++it;
			}
			else
			{
				it = results.erase(it);
			}
		}

		if (!foundAnyRelated)
		{
			Controller::hasRedirectTo = "create.view";

			toast(string("No related questions found!"), string("notification"));
			printString("\n");
		}
		else
		{
			Controller::hasRedirectTo = "search-results.view";

			toast(string("Found ") + to_string(results.size()) + string(" similar questions."), string("notification"));
			printString("\n");
		}
	}
	else if (action == "create")
	{
		this->model.save();

		toast(string("Your question was created!"), string("notification"));
		printString("\n");
	}
	else
	{
		Controller::pushError(string("Please provide a valid action in your view!"));
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

		if (it->first == "category" && !isInVector(vector<string>({ "something", "tada", "c++" }), it->second))
		{
			Controller::pushError(string("Please provide a valid category."));
		}
	}

	if (Controller::getErrorBag().empty())
	{
		if (truncatedInput.find("action")->second == "create")
		{
			truncatedInput["userId"] = to_string(this->users.setActive().id);
		}
		this->receiveCleanInput(truncatedInput);
	}
}

QuestionRepository::~QuestionRepository()
{
}