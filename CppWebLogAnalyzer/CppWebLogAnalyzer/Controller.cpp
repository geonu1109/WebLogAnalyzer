#include "Controller.h"
#include "DataConfig.h"
#include "Model.h"
#include "View.h"

Controller::Controller() {
	DataConfig config; // �⺻����� ���������� ����� ��ü ����
	Model model(config); // ���������� ������ ����� �� ����

	switch (View::showMenu()) {
	case 1:
		model.function1(View::function1());
		break;
	case 2:
		break;
	case 3:
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
