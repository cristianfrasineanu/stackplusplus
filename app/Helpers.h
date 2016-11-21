#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <Windows.h>

// Define include guard as function templates will get a redefined error.
#pragma once

using namespace std;

template<typename T>
inline void log(T &data, char *identifiedBy, char *when)
{
	cout << endl << "---*****LOGGER*****---" << endl
		<< identifiedBy << " was " << data << " when " << when << endl
		<< "---*****LOGGER*****---" << endl << endl;
}

template<typename V>
inline void log(vector<V> &data, char *identifiedBy, char *when)
{
	cout << endl << "---*****LOGGER*****---" << endl
		<< identifiedBy << " was ";
	for (vector<V>::iterator it = data.begin(); it != data.end(); it++)
	{
		cout << (*it) << " ";
	}
	cout << "when " << when << endl
		<< "---*****LOGGER*****---" << endl << endl;
}

template<typename FirstT, typename SecondT>
inline void log(map<FirstT, SecondT> &data, char *identifiedBy, char *when)
{
	cout << endl << "---*****LOGGER*****---" << endl
		<< identifiedBy << " was ";
	for (map<FirstT, SecondT>::iterator it = data.begin(); it != data.end(); it++)
	{
		cout << it->first << " " << it->second << " ";
	}
	cout << "when " << when << endl
		<< "---*****LOGGER*****---" << endl << endl;
}

template<typename V>
inline bool isInVector(vector<V> &haystack, V needle)
{
	return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

template<typename FirstT, typename SecondT>
inline bool isInMap(map<FirstT, SecondT> &haystack, FirstT needle)
{
	return haystack.find(needle) != haystack.end();
}

void sleepAndClearBuffer(unsigned delay);
void clearScreen();