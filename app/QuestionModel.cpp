#include "QuestionModel.h"

Question QuestionModel::setAfterUserId(int userId)
{
	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&this->question), sizeof(question)))
	{
		if (this->question.user_id == userId)
		{
			return this->question;
		}
	}

	throw invalid_argument("Question not found!");
}

Question QuestionModel::setAfterId(int id)
{
	this->io.seekg((id - 1) * sizeof(Question), this->io.beg);
	this->io.read(reinterpret_cast<char *>(&this->question), sizeof(Question));

	return this->question;
}

bool QuestionModel::questionTitleExists(string &title)
{
	Question question;

	this->io.seekg(0, this->io.beg);

	while (this->io.read(reinterpret_cast<char *>(&question), sizeof(Question)))
	{
		if (question.title == title)
		{
			return true;
		}
	}

	return false;
}

void QuestionModel::markAnswered(int id)
{
	this->setAfterId(id);

	this->question.hasAnswer = true;

	this->save();
}

void QuestionModel::markAs(const string &status, int id)
{
	this->setAfterId(id);

	this->question.active = (status == "active") ? true : false;

	this->save();
}

// Serialize the object.
void QuestionModel::save()
{
	this->io.seekp((this->question.id - 1) * sizeof(Question), this->io.beg);

	this->io.clear();

	if (!this->io.write(reinterpret_cast<char *>(&this->question), sizeof(Question)))
	{
		throw system_error(error_code(3, generic_category()), "Failed persisting data to file!");
	}
}

void QuestionModel::setAttributes(map<string, string> &cleanInputs)
{
	for (map<string, string>::iterator it = cleanInputs.begin(); it != cleanInputs.end(); it++)
	{
		if (isInVector(this->protectedAttributes, it->first))
		{
			continue;
		}
		else if (it->first == "title")
		{
			strcpy(this->question.title, it->second.c_str());
		}
		else if (it->first == "body")
		{
			strcpy(this->question.body, it->second.c_str());
		}
	}

	// If there's a new user, assign created_at with the current date.
	if (cleanInputs.find("action")->second == "create")
	{
		time_t t = time(nullptr);
		strftime(this->question.created_at, sizeof(this->question.created_at), "%c", localtime(&t));
	}

	this->question.id = ++this->lastId;
}

void QuestionModel::dumpFile()
{
	Question question;

	ifstream db(QuestionModel::pathToFile, ios::in | ios::binary);
	ofstream dump((QuestionModel::pathToFile.substr(0, QuestionModel::pathToFile.find(".store")).append(".txt")), ios::out | ios::trunc);

	if (db.is_open() && dump.is_open())
	{
		db.seekg(0, db.beg);

		while (db.read(reinterpret_cast<char *>(&question), sizeof(Question)))
		{
			dump << question.id << endl
				<< question.user_id << endl
				<< question.category_id << endl
				<< question.title << endl
				<< question.body << endl
				<< question.created_at << endl
				<< question.deleted_at << endl
				<< question.hasAnswer << endl;
		}

		db.close();
		dump.close();
	}
}

QuestionModel::~QuestionModel()
{
	this->io.close();
}

string QuestionModel::pathToFile = "..\\database\\questions.store";
void QuestionModel::openIOStream()
{
	this->io.open(QuestionModel::pathToFile, ios::in | ios::out | ios::binary);
	this->io.seekp(0, this->io.end);
	this->fileSize = this->io.tellp();

	if (!this->io.is_open())
	{
		toast(string("Couldn't open the file stream!"), string("error"));
	}
}

void QuestionModel::setLastId()
{
	if (this->fileSize == 0)
	{
		this->lastId = 0;
	}
	else
	{
		this->io.seekg((this->fileSize / sizeof(Question) - 1) * sizeof(Question), this->io.beg);
		this->io.read(reinterpret_cast<char *>(&this->question), sizeof(Question));

		this->lastId = this->question.id;
	}
}

QuestionModel::QuestionModel()
{
	this->openIOStream();
	this->protectedAttributes = { "id", "user_id", "category_id", "created_at", "deleted_at", "votes", "hasAnswer" };
	this->setLastId();
}
