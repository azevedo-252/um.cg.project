/**
 * Config.cpp
 */

#include "Config.h"

Config::Config(const string &source) {
	ini = iniparser_load((char *)source.c_str());
}

int Config::rint(const string &key) {
	return iniparser_getint(ini, (char *)key.c_str(), -1);
}

string Config::rstring(const string &key) {
	return iniparser_getstring(ini, (char *)key.c_str(), NULL);
}

float Config::rfloat(const string &key) {
	return (float) iniparser_getdouble(ini, (char *)key.c_str(), -1);
}

void Config::dump() {
	iniparser_dump(ini, stdout);
}
