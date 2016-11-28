#include "Model.h"

string Model::parseEntityName(string inputAlias)
{
	return inputAlias.erase(inputAlias.find("-"), string::npos);
}

void Model::attachEntity(string &model)
{
	toLowerCase(model);
	if (model == UserRepository::getAlias())
	{
		this->repository = new UserRepository();
	}
	/*else if (model == "question")
	{

	}
	else if (model == "category")
	{

	}*/
}

Model::Model()
{
	this->repository = NULL;
	this->rawInput = {};
	this->truncatedInput = {};
}

// Pass the payload along to the repository in order to be validated.
void Model::confirmInput(const map<string, string> &payLoad)
{
	this->rawInput = payLoad;

	string entityName = this->parseEntityName((++this->rawInput.begin())->first),
		inputAlias;

	if (this->repository == NULL)
	{
		this->attachEntity(entityName);
	}

	for (map<string, string>::iterator it = this->rawInput.begin(); it != this->rawInput.end(); it++)
	{
		// Skip truncation for action.
		if (it->first == "action")
		{
			this->truncatedInput["action"] = it->second;

			continue;
		}

		inputAlias = it->first;
		inputAlias.erase(0, entityName.size() + 1);

		this->truncatedInput[inputAlias] = it->second;
	}

	// Validate the input, if there are any errors, display them and reload the view.
	this->repository->validateItems(this->truncatedInput);
}

Model::~Model()
{
	delete this->repository;
}
