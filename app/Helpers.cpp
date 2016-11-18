#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
#include <conio.h>

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
	// so as long as the keyboard is hit during that period, the input won't be taken into consideration.
	while (_kbhit())
	{
		_getch();
	}
}
