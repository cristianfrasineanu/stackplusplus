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

	bool setActiveIfAny();
	Question setAfterUserId(int);
	Question setAfterId(int);
	vector<Question> retrieveAll();

	int getId();
	char *getTitle();
	char *getBody();
	char *getCategory();

	bool questionTitleExists(string &);
	void markAnswered(int);
	void markAs(const string &, int = NULL);
	void save();
	void setAttributes(map<string, string> &);

	// Set the active to false on logout
	~QuestionModel();
};