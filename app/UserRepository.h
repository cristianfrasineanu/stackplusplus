#pragma once

#include <regex>

#include "RepositoryInterface.h"
#include "UserModel.h"
#include "QuestionModel.h"

using namespace std;

class UserRepository : public RepositoryInterface {
private:
	static string alias;

	UserModel model;
	QuestionModel questions;

	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	static string &getAlias();

	UserRepository();

	void validateItems(map<string, string> &);
	void echo(const string &);
	void apply(const string &);

	~UserRepository();
};