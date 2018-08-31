#include "View.h"
#include "Config.h"
#include "FileProc.h"
#include "Model.h"

int main(void) {
	Config config; // 기본경로의 설정파일을 사용해 객체 생성
	Model model(config); // 설정파일의 내용이 적용된 모델 생성

	/*
	FILE *fp = fopen("C:\\Users\\user\\Desktop\\logdata\\20180824\\ap1.daouoffice.com_access_2018-08-24.txt", "r");
	char tmp[2048];
	fgets(tmp, 2048, fp);
	model.splitRecord(tmp);
	for (int i = 0; i < config.FIELD_COUNT; i++) {
		printf("%s\n", model.field[i]);
	}
	scanf("%c", stdin);
	*/ // 파싱 테스트 코드
	
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

	return 0;
}