#include <iostream>
#include <vector>
#include <map>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool isInCharStringMap(const map<char, string> &, char);
bool isInCharVector(const vector<char> &, char);
bool isInIntVector(const vector<int> &, int);
bool isInStringVector(const vector<string> &, string);
void sleepAndClearBuffer(unsigned delay);
void clearScreen();
void log(char *, char *, char *);
void log(string &, char *, char *);
void log(vector<string> &, char *, char *);