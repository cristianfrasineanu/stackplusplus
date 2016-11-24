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

void Model::confirmInput(const map<string, string> &payLoad)
{
	this->rawInput = payLoad;

	// There's interaction with only one model on the view.
	string entityName = this->parseEntityName(this->rawInput.begin()->first),
		inputAlias;

	if (this->repository == NULL)
	{
		this->attachEntity(entityName);
	}

	for (map<string, string>::iterator it = this->rawInput.begin(); it != this->rawInput.end(); it++)
	{
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
