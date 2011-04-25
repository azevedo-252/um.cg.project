/**
 * Config.h
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include <iostream>

using namespace std;

#include "iniparser/iniparser.h"

class Config {
private:
	dictionary *ini;

public:
	Config(const string &source);

	int rint(const string &key);
	string rstring(const string &key);
	float rfloat(const string &key);

	void dump();
};

#endif
