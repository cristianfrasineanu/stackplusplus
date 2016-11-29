#pragma once

#include <regex>
#include <iomanip>
#include <ctime>
#include <locale>

#include "ModelInterface.h"

using namespace std;

typedef struct {
	int id;

	char full_name[255] = "";
	char email[255] = "";
	char username[20] = "";
	char password[17] = "";
	char created_at[50] = "";

	// Soft deletes
	char deleted_at[50] = "";
	char role[10] = "user";
	bool active = 1;
	bool banned = 0;
} User;

class UserModel : public ModelInterface {
private:
	static string pathToFile;

	User user;

	void openIOStream();
	void setLastId();

	long long fileSize;
	int lastId;
public:
	static void dumpFile();
	UserModel();

	User setAfterUser(string &);
	User setAfterId(int);
	User setActive();

	char *getFullName();

	bool userExists(string &);
	void markAs(string &, int);
	void save();
	void setAttributes(map<string, string> &);

	// Set the active to false on logout
	~UserModel();
};