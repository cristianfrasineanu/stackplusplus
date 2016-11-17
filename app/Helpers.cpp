#include <iostream>
#include <vector>

#include "Helpers.h"


unsigned getLastUuid()
{
	return 40;
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
