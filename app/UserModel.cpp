#include "UserModel.h"

void UserModel::save()
{
	//this->io.write(reinterpret_cast<char *>(&this->User), sizeof(this->User));

	cout << "Theoretically wrote the data into the file"
		<< endl;
}

void UserModel::setAttributes(map<string, string> &cleanInputs)
{
	for (map<string, string>::iterator it = cleanInputs.begin(); it != cleanInputs.end(); it++)
	{
		if (isInVector(this->protectedAttributes, it->first))
		{
			continue;
		}
		else if (it->first == "fullname")
		{
			strcpy(this->User.full_name, it->second.c_str());
		}
		else if (it->first == "email")
		{
			strcpy(this->User.email, it->second.c_str());
		}
		else if (it->first == "username")
		{
			strcpy(this->User.username, it->second.c_str());
		}
		else if (it->first == "password")
		{
			strcpy(this->User.password, it->second.c_str());
		}
	}

	// If there's a new user, assign created_at with the current date.
	if (strlen(this->User.full_name) != 0)
	{
		time_t t = time(nullptr);
		strftime(this->User.created_at, sizeof(this->User.created_at), "%c", localtime(&t));
	}
}

UserModel::~UserModel()
{
	this->io.close();
}

string UserModel::pathToFile = "..\\database\\users.store";
void UserModel::openIOStream()
{
	this->io.open(UserModel::pathToFile, ios::in | ios::out | ios::app | ios::binary);

	if (!this->io.is_open())
	{
		cout << "Couldn't open " + UserModel::pathToFile;
	}
}

UserModel::UserModel()
{
	this->openIOStream();
	this->protectedAttributes = { "created_at", "deleted_at", "role", "active" };
}
