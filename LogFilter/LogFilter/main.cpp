#include "ConfigData.h"
#include "ArgumentData.h"
#include "LogData.h"
#include "LogFilter.h"
#include "Console.h"

int main(int argc, char *argv[]) {
	const string ConfigFilePath("../LogFilter/logfiltercfg.txt");

	try {
		ConfigData::load(ConfigFilePath);
		ArgumentData::init(argc, argv);

		LogFilter::run();
	}
	catch (const string &strErrMsg) {
		Console::getInstance()->printErr(strErrMsg);
		system("pause");
		exit(1);
	}

	system("pause");
	return 0;
}