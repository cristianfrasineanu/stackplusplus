#pragma once

#include <iomanip>
#include <ctime>
#include <locale>

#include "ModelInterface.h"

using namespace std;

typedef struct {
	int id;
	int user_id;
	int category_id = 1;

	unsigned votes = 0;

	char title[255] = "";
	char body[1023] = "";
	char created_at[50] = "";

	// Soft deletes
	char deleted_at[50] = "";
	bool hasAnswer = 0;
	bool active = 0;
} Question;

class QuestionModel : public ModelInterface {
private:
	static string pathToFile;

	Question question;

	void openIOStream();
	void setLastId();

	long long fileSize;
	int lastId;
public:
	static void dumpFile();
	QuestionModel();

	Question setAfterUserId(int);
	Question setAfterId(int);

	bool questionTitleExists(string &);
	void markAnswered(int);
	void markAs(const string &, int);
	void save();
	void setAttributes(map<string, string> &);

	// Set the active to false on logout
	~QuestionModel();
};