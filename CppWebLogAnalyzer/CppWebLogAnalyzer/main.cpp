#include "Controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>

int main(void) {
	Controller controller;

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

	/*
	FILE *fp = fopen("C:\\Users\\user\\Desktop\\logdata\\20180824\\ap1.daouoffice.com_access_2018-08-24.txt", "r");
	char str[2048];
	clock_t st, et;

	st = clock();
	while (fgets(str, 2048, fp)) {
		// printf("%s", str);
	}
	et = clock();

	printf("�ɸ� �ð�: %f��\n", (float)(et - st) / 1000);
	*/ // ���� ����� �ð� ����
	system("pause");
	return 0;
}