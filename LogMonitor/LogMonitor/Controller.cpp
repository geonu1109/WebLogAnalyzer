#include "Controller.h"
#include "ConfigData.h"
#include "Console.h"
#include "LogMonitor.h"
#include <iostream>
#include <string>
using namespace std;

Controller::Controller() {
}

void Controller::run(void) const {
	
	
	try {
		
	}
	catch (string strErrMsg) {
		Console::getInstance().printErr(strErrMsg);
		system("pause");
		exit(1);
	}
}
