#include "Helpers.h"

bool isInCharStringMap(const map<char, string> &haystack, char needle)
{
	return haystack.find(needle) != haystack.end();
}

bool isInCharVector(const vector<char> &haystack, char needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

bool isInIntVector(const vector<int> &haystack, int needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

bool isInStringVector(const vector<string> &haystack, string needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

void sleepAndClearBuffer(unsigned delay)
{
	Sleep(delay);

	// Clear the keyboard buffer during the sleep cycle (if there are any keys pressed), 
	// so whatever keys are hit are discarded
	while (_kbhit())
	{
		_getch();
	}
}

void clearScreen()
{
	system("cls");
}

void log(char *data, char *identifier, char *situation)
{
	cout << "---///////////---" << endl;
	cout << identifier << " is currently " << data << " when " << situation << endl;
	cout << "---///////////---" << endl;
}

void log(string &data, char *identifier, char *situation)
{
	cout << "---///////////---" << endl;
	cout << identifier << " is currently " << data.c_str() << " when " << situation << endl;
	cout << "---///////////---" << endl;
}

void log(vector<string> &data, char *identifier, char *situation)
{
	cout << "---///////////---" << endl;
	cout << identifier << " is currently ";
	for (vector<string>::iterator it = data.begin(); it != data.end(); it++)
	{
		cout << (*it).c_str() << " ";
	}
	cout << " when " << situation << endl;
	cout << "---///////////---" << endl;
}