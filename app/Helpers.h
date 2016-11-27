#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

// Please forgive me. 
#include <curses.h>

using namespace std;

template<typename V, typename N>
inline bool isInVector(vector<V> &haystack, N needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

template<typename FirstT, typename SecondT>
inline bool isInMap(map<FirstT, SecondT> &haystack, FirstT needle)
{
	return haystack.find(needle) != haystack.end();
}


void printVector(vector<string> &);
void toast(string &, string &);
void toLowerCase(string &);
void sleepAndClearBuffer(unsigned);
void clearScreen();
void getString(string &);
void printString(const char *);
void clearPreviousLines(unsigned);