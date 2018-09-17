// #define WINDOWS

#include "Controller.h"
#include "ConfigData.h"
#include "ArgumentData.h"
#include "Console.h"
#include "LogMonitor.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
#ifdef WINDOWS
	const string ConfigFilePath("../LogMonitor/logmoncfg.txt");
#else
	const string ConfigFilePath("/etc/logmoncfg.txt");
#endif
	LogMonitor logMonitor;

	try {
		ConfigData::load(ConfigFilePath);
		ArgumentData::init(argc, argv);

		logMonitor.run();
	}
	catch (string strErrMsg) {
		Console::getInstance().printErr(strErrMsg);
	}

	system("pause");
	return 0;
}