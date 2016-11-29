#pragma once

#include <regex>

#include "RepositoryInterface.h"
#include "QuestionModel.h"

using namespace std;

class QuestionRepository : public RepositoryInterface {
private:
	static string alias;

	QuestionModel model;

	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	static string &getAlias();

	QuestionRepository();

	void validateItems(map<string, string> &);
	void echo(const string &);

	~QuestionRepository();
};