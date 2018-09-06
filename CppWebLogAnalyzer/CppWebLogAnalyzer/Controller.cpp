#include "Controller.h"
#include "Data/DataConfig.h"
#include "Model/LogFilter.h"
#include "Model.h"
#include "View.h"
#include <iostream>
#include <ctime>
using namespace std;

Controller::Controller() {
	DataConfig config; // �⺻����� ���������� ����� ��ü ����
	LogFilter logFilter(config);
	View view;
	clock_t st, et;

	switch (view.showMenu()) {
	case 1:
		logFilter.filterDelayedApi(view.showMenu1());
		break;
	case 2:
		logFilter.sortDynamicApi(2, view.showMenu2());
		break;
	case 3:
		logFilter.countHttpStatusCode(view.showMenu3());
		break;
	case 4:
		logFilter.sortDynamicApi(4, view.showMenu4());
		break;
	case 5:
		logFilter.classifyClientAgent(view.showMenu5());
		break;
	default:
		;
	}
}

Controller::~Controller() {
}
