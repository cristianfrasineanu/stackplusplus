#include "UserModel.h"

User UserModel::getAfterUser(string &username)
{
	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User)))
	{
		if (this->user.username == username)
		{
			return this->user;
		}
	}

	// Otherwise if we reach the end of the file, the eof flag will be set and write will fail.
	this->io.clear();

	throw invalid_argument("Username not found!");
}

User UserModel::getAfterId(int id)
{
	this->io.seekg((id - 1) * sizeof(User), this->io.beg);
	this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

	this->io.clear();

	return this->user;
}

User UserModel::getActive()
{
	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User)))
	{
		if (this->user.active == true)
		{
			return this->user;
		}
	}

	this->io.clear();

	throw exception("No active user!");
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

	this->io.clear();

	return false;
}

void UserModel::markAs(string &status, int id)
{
	this->getAfterId(id);

	this->user.active = (status == "active") ? true : false;

	this->save();
}

// Serialize the object.
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
	if (cleanInputs.find("action")->second == "signup")
	{
		time_t t = time(nullptr);
		strftime(this->user.created_at, sizeof(this->user.created_at), "%c", localtime(&t));
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
			dump << user.id << endl
				<< user.full_name << endl
				<< user.email << endl
				<< user.username << endl
				<< user.password << endl
				<< user.created_at << endl
				<< user.deleted_at << endl
				<< user.role << endl
				<< user.active << endl
				<< user.banned << endl << endl;
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
		this->io.seekg((this->fileSize / sizeof(User) - 1) * sizeof(User), this->io.beg);
		this->io.read(reinterpret_cast<char *>(&this->user), sizeof(User));

		this->io.clear();

		this->lastId = this->user.id;
	}
}

UserModel::UserModel()
{
	this->openIOStream();
	this->protectedAttributes = { "created_at", "deleted_at", "role", "active", "banned" };
	this->setLastId();
}
