#include "iniparser/src/iniparser.h"

int main() {
	dictionary *ini = iniparser_load("config.ini");

	iniparser_dump(ini, stdout);
	
	return 0;
}
