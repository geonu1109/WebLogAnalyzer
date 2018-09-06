#include "Controller.h"
#include "Data/DataConfig.h"
#include "Model/LogFilter.h"
#include "LogFilterThread.h"
#include "Model.h"
#include "View.h"
#include <iostream>
#include <ctime>
using namespace std;

Controller::Controller() {
	LogFilter logFilter;
	LogFilterThread logFilterThread;
	DataInput::getInstance().setSelect(View::getInstance().showMenu());

	switch (DataInput::getInstance().getSelect()) {
	case 1:
		View::getInstance().showMenu1();
		logFilterThread.process();
		break;
	case 2:
		View::getInstance().showMenu2();
		logFilter.sortDynamicApi();
		break;
	case 3:
		View::getInstance().showMenu3();
		logFilter.countHttpStatusCode();
		break;
	case 4:
		View::getInstance().showMenu4();
		logFilter.sortDynamicApi();
		break;
	case 5:
		View::getInstance().showMenu5();
		logFilter.classifyClientAgent();
		break;
	default:
		;
	}
}

Controller::~Controller() {
}
