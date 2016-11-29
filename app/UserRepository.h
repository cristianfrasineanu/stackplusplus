#pragma once

#include <regex>

#include "RepositoryInterface.h"
#include "UserModel.h"

using namespace std;

class UserRepository : public RepositoryInterface {
private:
	static string alias;

	UserModel model;

	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	static string &getAlias();
	static void logOutUser();

	UserRepository();

	void validateItems(map<string, string> &);
	void echo(const string &);

	~UserRepository();
};