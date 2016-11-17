class Console {
private:
	char *currentView;
	vector<fs::path> loadedViews;
	void loadViews(const fs::path &root, const string &ext);
public:
	static string initialView;
	Console();
	~Console();
};

class User {
private:
	const unsigned uuid;
	char *nick;
public:
	static unsigned count;
	static void setFromLastUuid();
	User();
	~User();
	unsigned getUuid();
};