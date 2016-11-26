#include "UserModel.h"

User UserModel::getAfterUser(string &username)
{
	this->io.seekg(0, this->io.beg);

	do
	{
		this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

		if (this->user.username == username)
		{
			return this->user;
		}
	} while (!this->io.eof());

	throw("Username not found!");
}

User UserModel::getAfterId(int id)
{
	this->io.seekg((id - 1) * sizeof(User), this->io.beg);
	this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

	return this->user;
}

void UserModel::markAs(string &status, int id)
{
	this->getAfterId(id);

	this->user.active = (status == "active") ? true : false;

	this->save();
}

// Serialize the object when saving a user.
void UserModel::save()
{
	this->io.seekp((this->user.id - 1) * sizeof(User), this->io.beg);
	this->io.write(reinterpret_cast<char *>(&this->user), sizeof(User));
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
			strcpy(this->user.full_name, it->second.c_str());
		}
		else if (it->first == "email")
		{
			strcpy(this->user.email, it->second.c_str());
		}
		else if (it->first == "username")
		{
			strcpy(this->user.username, it->second.c_str());
		}
		else if (it->first == "password")
		{
			strcpy(this->user.password, it->second.c_str());
		}
	}

	// If there's a new user, assign created_at with the current date.
	if (strlen(this->user.full_name) != 0)
	{
		time_t t = time(nullptr);
		strftime(this->user.created_at, sizeof(this->user.created_at), "%c", localtime(&t));
	}

	this->user.id = ++this->lastId;
}

UserModel::~UserModel()
{
	this->io.close();
}

string UserModel::pathToFile = "..\\database\\users.store";
void UserModel::openIOStream()
{
	this->io.open(UserModel::pathToFile, ios::in | ios::out | ios::binary);
	this->io.seekp(0, this->io.end);
	this->fileSize = this->io.tellp();

	if (!this->io.is_open())
	{
		cout << "Couldn't open the file stream path: " << UserModel::pathToFile;
	}
}

void UserModel::setLastId()
{
	if (this->fileSize == 0)
	{
		this->lastId = 0;
	}
	else
	{
		User lastUser;

		this->io.seekg((this->fileSize / sizeof(User) - 1) * sizeof(User), this->io.beg);
		this->io.read(reinterpret_cast<char *>(&lastUser), sizeof(lastUser));

		this->lastId = lastUser.id;
	}
}

UserModel::UserModel()
{
	this->openIOStream();
	this->protectedAttributes = { "created_at", "deleted_at", "role", "active", "banned" };
	this->setLastId();
}
