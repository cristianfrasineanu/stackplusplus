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
		{ "keyword", "..." },
		{ "action", "Please provide a valid action!" }
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

		Controller::hasRedirectTo = "show-question.view";
	}
	else
	{
		Controller::pushError(string("Please provide a valid action in your view!"));
	}
}

// Determine what to output via the model.
void QuestionRepository::echo(const string &alias)
{
	this->model.setActiveIfAny();

	if (alias == "id")
	{
		printString(to_string(this->model.getId()).c_str());
	}
	else if (alias == "title")
	{
		printString(this->model.getTitle());
	}
	else if (alias == "body")
	{
		printString(this->model.getBody());
	}
	else if (alias == "category")
	{
		printString(this->model.getCategory());
	}
}

void QuestionRepository::apply(const string &action)
{
	if (action == "reset")
	{
		if (this->model.setActiveIfAny())
		{
			this->model.markAs("non_active");
		}
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

		// TODO: implement a category model.
		if (it->first == "category" && !isInVector(vector<string>({ "something", "tada", "c++" }), it->second))
		{
			Controller::pushError(string("Please provide a valid category."));
		}
	}

	if (Controller::getErrorBag().empty())
	{
		if (truncatedInput.find("action")->second == "create")
		{
			this->users.setActiveIfAny();
			truncatedInput["userId"] = to_string(this->users.getId());
		}
		this->receiveCleanInput(truncatedInput);
	}
}

QuestionRepository::~QuestionRepository()
{
}