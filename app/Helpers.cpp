#include <iostream>
#include <vector>
#include <map>

#include "Helpers.h"

bool isInCharStringMap(const map<char, string> &haystack, char needle)
{
	return haystack.find(needle) != haystack.end();
}

bool isInCharVector(vector<char> haystack, char needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

bool isInIntVector(vector<int> haystack, int needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

bool isInStringVector(vector<string> haystack, string needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}
