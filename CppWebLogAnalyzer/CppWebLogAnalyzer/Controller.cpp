#include "Controller.h"
#include "Data/DataConfig.h"
#include "Model/LogFilter.h"
#include "LogFilterThread.h"
#include "HttpStatusCounterThread.h"
#include "Model.h"
#include "View.h"
#include <iostream>
#include <ctime>
using namespace std;

Controller::Controller() {
	LogFilter logFilter;
	DataInput::getInstance().setSelect(View::getInstance().showMenu());

	switch (DataInput::getInstance().getSelect()) {
	case 1:
		View::getInstance().showMenu1();
		LogFilterThread().process();
		break;
	case 2:
		View::getInstance().showMenu2();
		logFilter.sortDynamicApi();
		break;
	case 3:
		View::getInstance().showMenu3();
		// logFilter.countHttpStatusCode();
		HttpStatusCounterThread().process();
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
