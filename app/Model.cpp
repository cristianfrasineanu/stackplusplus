#include "Model.h"

string Model::parseModelName(string inputAlias)
{
	return inputAlias.erase(inputAlias.find("-"), string::npos);
}

void Model::attachModel(string &model)
{
	toLowerCase(model);
	if (model == "user")
	{
		this->currentModel = new User();
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
	this->accessHistory = {};
	this->currentModel = NULL;
}

void Model::sendSerializedInput(map<string, string> &input)
{
	string modelName = this->parseModelName(input.begin()->first);

	if (this->currentModel == NULL)
	{
		this->attachModel(modelName);
	}

	string inputAlias = input.begin()->first;
	inputAlias.erase(0, modelName.size() + 1);

	// if (this->currentModel->validateItem(inputAlias, input.begin()->second)) {

	// If the validation was successful push back into the ready map
	this->ready[inputAlias] = input.begin()->second;

	// }
}

void Model::confirmInput()
{
	// Send the input to the attached model and determine if there are any errors and if the payload is complete
	this->currentModel->receiveCleanInput(this->ready);
}

Model::~Model()
{
	delete this->currentModel;
}
