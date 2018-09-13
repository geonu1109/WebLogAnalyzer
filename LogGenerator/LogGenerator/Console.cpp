#include "Console.h"
#include <iostream>

Console Console::instance;

Console &Console::getInstance(void) {
	return instance;
}

void Console::print(const string &strMsg) const {
	cout << strMsg << endl;
}

void Console::printErr(const string &strErrMsg) const {
	cout << "[error] " << strErrMsg << endl;
}

Console::Console() {

}