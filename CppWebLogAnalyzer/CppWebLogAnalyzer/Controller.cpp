#include "Controller.h"
#include "DataConfig.h"
#include "Model.h"
#include "View.h"

Controller::Controller() {
	DataConfig config; // 기본경로의 설정파일을 사용해 객체 생성
	Model model(config); // 설정파일의 내용이 적용된 모델 생성

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
