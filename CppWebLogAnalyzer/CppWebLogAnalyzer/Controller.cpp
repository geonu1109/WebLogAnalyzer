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
		st = clock();
		logFilter.filterDelayedApi(view.showMenu1());
		et = clock();
		cout << "�ɸ� �ð�: " << (float)(et - st) / 1000 << endl;
		break;
	case 2:
		break;
	case 3:
		// model.function3(View::function3());
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		;
	}
}

Controller::~Controller() {
}
