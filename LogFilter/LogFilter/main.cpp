#include "ConfigData.h"
#include "ArgumentData.h"
#include "LogData.h"

int main(int argc, char *argv[]) {
	const string ConfigFilePath("../LogFilter/logfiltercfg.txt");

	ConfigData::getInstance().load(ConfigFilePath);
	ArgumentData::getInstance().init(argc, argv);



	system("pause");
	return 0;
}