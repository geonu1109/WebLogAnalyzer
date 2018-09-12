#include "Controller.h"
#include "ConfigData.h"
#include "ParamData.h"
#include "ResultWriter.h"
#include "Console.h"
#include "LogMonitor.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
	const string ConfigFilePath("../LogMonitor/logmoncfg.txt");
	const string ResultFilePath("~/result.txt");
	LogMonitor logMonitor;

	try {
		ConfigData::load(ConfigFilePath);
		ParamData::init(argc, argv);

		logMonitor.run();
	}
	catch (string strErrMsg) {
		Console::getInstance().printErr(strErrMsg);
	}

	system("pause");
	return 0;
}