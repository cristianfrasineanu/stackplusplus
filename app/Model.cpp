#include "Model.h"

string Model::parseEntityName(string inputAlias)
{
	return inputAlias.erase(inputAlias.find("-"), string::npos);
}

void Model::attachEntity(string &model)
{
	toLowerCase(model);
	if (model == "user")
	{
		this->repository = new UserRepository();
	}
	else if (model == "question")
	{

	}
	else if (model == "category")
	{

	}
}

Model::Model()
{
	this->repository = NULL;
	this->rawInput = {};
	this->serializedInput = {};
}

void Model::sendSerializedInput()
{
	// There's interaction with only one model on the view.
	string modelName = this->parseEntityName(this->rawInput.begin()->first),
		inputAlias;

	if (this->repository == NULL)
	{
		this->attachEntity(modelName);
	}

	for (map<string, string>::iterator it = this->rawInput.begin(); it != this->rawInput.end(); it++)
	{
		inputAlias = it->first;
		inputAlias.erase(0, modelName.size() + 1);

		this->serializedInput[inputAlias] = it->second;
	}

	// Sanitize the input, if there are any errors, display them and reload the view.
	this->repository->validateItems(this->serializedInput);
}

void Model::confirmInput(const map<string, string> &payLoad)
{
	this->rawInput = payLoad;
	this->sendSerializedInput();
}

Model::~Model()
{
	delete this->repository;
}
