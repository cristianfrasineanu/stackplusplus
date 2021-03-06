#include "UserModel.h"

char *UserModel::getFullName()
{
	return this->user.full_name;
}

int UserModel::getId()
{
	return this->user.id;
}

User UserModel::setAfterUser(string &username)
{
	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User)))
	{
		if (this->user.username == username)
		{
			return this->user;
		}
	}

	throw invalid_argument("Username not found!");
}

User UserModel::setAfterId(int id)
{
	this->io.seekg((id - 1) * sizeof(User), this->io.beg);
	this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

	return this->user;
}

bool UserModel::setActiveIfAny()
{
	if (this->user.active == true)
	{
		return true;
	}

	this->io.seekg(0, this->io.beg);
	while (this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User)))
	{
		if (this->user.active == true)
		{
			return true;
		}
	}

	return false;
}

bool UserModel::userExists(string &username)
{
	User user;

	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&user), sizeof(User)))
	{
		if (user.username == username)
		{
			return true;
		}
	}

	return false;
}

void UserModel::markAs(const string &status, int id)
{
	if (id != NULL)
	{
		this->setAfterId(id);
	}

	this->user.active = (status == "active") ? true : false;

	this->save();
}

// Serialize the user.
void UserModel::save()
{
	this->io.seekp((this->user.id - 1) * sizeof(User), this->io.beg);
	this->io.clear();
	if (!this->io.write(reinterpret_cast<char *>(&this->user), sizeof(User)))
	{
		throw system_error(error_code(3, generic_category()), "Failed persisting data to file!");
	}

	// Flush the intermediate buffer and update the destination.
	this->io.flush();
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
	if (cleanInputs.find("action")->second == "signup")
	{
		time_t t = time(nullptr);
		strftime(this->user.created_at, sizeof(this->user.created_at), "%c", localtime(&t));
		this->user.active = true;
	}

	this->user.id = ++this->lastId;
}

void UserModel::dumpFile()
{
	User user;

	ifstream db(UserModel::pathToFile, ios::in | ios::binary);
	ofstream dump((UserModel::pathToFile.substr(0, UserModel::pathToFile.find(".store")).append(".txt")), ios::out | ios::trunc);

	if (db.is_open() && dump.is_open())
	{
		db.seekg(0, db.beg);

		while (db.read(reinterpret_cast<char *>(&user), sizeof(User)))
		{
			dump << "Id: " << user.id << endl
				<< "Full name: " << user.full_name << endl
				<< "Email: " << user.email << endl
				<< "Username: " << user.username << endl
				<< "Password: " << user.password << endl
				<< "Created at: " << user.created_at << endl
				<< "Delete at: " << user.deleted_at << endl
				<< "Role: " << user.role << endl
				<< "Active: " << user.active << endl
				<< "Banned: " << user.banned << endl << endl;
		}

		db.close();
		dump.close();
	}
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
		toast(string("Couldn't open the file stream!"), string("error"));
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
		this->io.seekg((this->fileSize / sizeof(User) - 1) * sizeof(User), this->io.beg);
		this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

		this->lastId = this->user.id;
	}
}

UserModel::UserModel()
{
	this->openIOStream();

	// Non mass-assignable fields.
	this->protectedAttributes = { "id", "created_at", "deleted_at", "role", "active", "banned" };
	this->setLastId();
}
