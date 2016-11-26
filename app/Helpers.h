#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <Windows.h>

using namespace std;

template<typename T>
inline void log(const T &data, char *identifiedBy, char *when)
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

template<typename V>
inline void printVector(vector<V> &v)
{
	for (vector<V>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it)
			<< endl;
	}
}

template<typename T>
inline void toast(T content, string &status)
{
	cout << endl << endl;

	if (status == "success")
	{
		cout << "++ " << content;
	}
	else if (status == "error")
	{
		cout << "!! " << content;
	}
	else
	{
		cout << "** " << content;
	}

	cout << endl;
}

void toLowerCase(string &);
void sleepAndClearBuffer(unsigned);
void clearScreen();