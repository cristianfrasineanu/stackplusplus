#pragma once

#include <fstream>

#include "Helpers.h"

//---Model---
//----------------
// The contents of an entity are serialized as a structure with static components.
// Writing directly objects to files can yield great havoc afterwards as we are possibly writing addresses, not values.
// The model detects what to do with data when writing to file from the state of the attributes.
class ModelInterface {
private:
	virtual void openIOStream() = 0;
protected:
	map<string, string> attributes;
	vector<string> protectedAttributes;

	fstream io;
public:
	virtual void save() = 0;
	virtual void setAttributes(map<string, string> &) = 0;
	virtual void markAs(const string &, int) = 0;
	
	virtual ~ModelInterface();
};