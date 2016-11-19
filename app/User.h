class User {
private:
	static unsigned count;

	const unsigned uuid;
	char *nick;
public:
	static void setFromLastUuid();
	User();
	~User();
	unsigned getUuid();
};