#include "Controller.h"
#include "Data/DataConfig.h"
#include "Model/LogFilter.h"
#include "Model.h"
#include "View.h"
#include <iostream>
#include <ctime>
using namespace std;

Controller::Controller() {
	DataConfig::getInstance().load(); // 설정파일 불러오기
	LogFilter logFilter;

	DataInput::getInstance().setSelect(View::showMenu());

	switch (DataInput::getInstance().getSelect()) {
	case 1:
		View::showMenu1();
		logFilter.filterDelayedApi();
		break;
	case 2:
		View::showMenu2();
		logFilter.sortDynamicApi();
		break;
	case 3:
		View::showMenu3();
		logFilter.countHttpStatusCode();
		break;
	case 4:
		View::showMenu4();
		logFilter.sortDynamicApi();
		break;
	case 5:
		View::showMenu5();
		logFilter.classifyClientAgent();
		break;
	default:
		;
	}
}

Controller::~Controller() {
}
