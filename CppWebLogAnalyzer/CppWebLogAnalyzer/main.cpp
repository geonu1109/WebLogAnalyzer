#include "View.h"
#include "Config.h"
#include "FileProc.h"
#include "Model.h"

int main(void) {
	Config config; // �⺻����� ���������� ����� ��ü ����
	Model model(config); // ���������� ������ ����� �� ����

	/*
	FILE *fp = fopen("C:\\Users\\user\\Desktop\\logdata\\20180824\\ap1.daouoffice.com_access_2018-08-24.txt", "r");
	char tmp[2048];
	fgets(tmp, 2048, fp);
	model.splitRecord(tmp);
	for (int i = 0; i < config.FIELD_COUNT; i++) {
		printf("%s\n", model.field[i]);
	}
	scanf("%c", stdin);
	*/ // �Ľ� �׽�Ʈ �ڵ�
	
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