#include "Helpers.h"

void toLowerCase(string &input)
{
	transform(input.begin(), input.end(), input.begin(),
			  [](unsigned char ch) { return tolower(ch); });
}

void sleepAndClearBuffer(unsigned delay)
{
	Sleep(delay);
	flushinp();
}

void clearScreen()
{
	clear();
	refresh();
}

void getString(string &input)
{
	char buffer[256];
	getstr(buffer);
	input = buffer;
}

void printString(const char *str)
{
	printw(str);
	refresh();
}

void clearPreviousLines(unsigned n)
{
	unsigned cn = n;
	int x, y;

	getyx(stdscr, y, x);

	move(y, 0);
	clrtoeol();

	while (n > 0)
	{
		move(y - n--, 0);
		clrtoeol();
	}

	// Move to the beginning of the first one.
	move(y - cn, 0);
}

void toast(string &content, string &status)
{
	if (status == "success")
	{
		//cout << "++ " << content;
		printw("++ %s", content.c_str());
	}
	else if (status == "error")
	{
		//cout << "!! " << content;
		printw("!! %s", content.c_str());
	}
	else
	{
		//cout << "** " << content;
		printw("** %s", content.c_str());
	}
	refresh();
}

void printVector(vector<string> &v)
{
	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		printw("%s\n", (*it).c_str());
		refresh();
	}
}