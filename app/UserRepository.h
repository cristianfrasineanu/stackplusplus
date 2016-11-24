#pragma once

#include <regex>

#include "RepositoryInterface.h"
#include "UserModel.h"


class UserRepository : public RepositoryInterface {
private:
	static string alias;

	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	static string &getAlias();

	UserRepository();

	void validateItems(map<string, string> &);
	void retrieveItemForActive();
	void retrieveAll();

	~UserRepository();
};