#include <regex>

#include "RepositoryInterface.h"
#include "UserModel.h"

class UserRepository : public RepositoryInterface {
private:
	void defineValidation();
	void receiveCleanInput(map<string, string> &);
public:
	UserRepository();

	void validateItems(map<string, string> &);
	void retrieveItemForActive();
	void retrieveAll();

	~UserRepository();
};