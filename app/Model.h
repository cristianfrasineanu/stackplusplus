#pragma once

#include "Helpers.h"
#include "RepositoryInterface.h"
#include "UserRepository.h"

using namespace std;

class Model {
private:
	map<string, string> rawInput;
	map<string, string> truncatedInput;

	RepositoryInterface *repository;

	string parseEntityName(string);
	void attachEntity(string &);
public:
	Model();

	void confirmInput(const map<string, string> &);
	void render(const string &);

	~Model();
};