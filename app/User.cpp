#include "User.h"

//--- User --- 
//------------
unsigned User::count = 0;

void User::setFromLastUuid()
{
	// Get the last uuid from the db file

	User::count = 30;
}

User::User() : uuid(User::count++)
{
	this->nick = new char[4];
}

User::~User()
{
	delete[] this->nick;
}

unsigned User::getUuid()
{
	return this->uuid;
}