#include "Controller.h"
#include "DataConfig.h"
#include "DataParam.h"
#include "ResultWriter.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
	const string ConfigFilePath("../LogMonitor/logmoncfg.txt");
	const string ResultFilePath("~/result.txt");

	Controller controller;

	DataConfig::load(ConfigFilePath);
	DataParam::init(argc, argv);
	controller.process();

	system("pause");
	return 0;
}