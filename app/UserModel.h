#pragma once

#include <regex>
#include <iomanip>
#include <ctime>
#include <locale>

#include "ModelInterface.h"

class UserModel : public ModelInterface {
private:
	static string pathToFile;
	
	struct {
		char full_name[255] = "";
		char email[255] = "";
		char username[20] = "";
		char password[17] = "";
		char created_at[50] = "";

		// Soft deletes
		char deleted_at[50] = "";
		char role[10] = "user";
		bool active = 1;
	} User;

	void openIOStream();
public:
	// Open the IOStream and assign the protected attributes that shouldn't be changed by the user
	UserModel();

	void save();
	void setAttributes(map<string, string> &);

	// Set the active to false on logout
	~UserModel();
};