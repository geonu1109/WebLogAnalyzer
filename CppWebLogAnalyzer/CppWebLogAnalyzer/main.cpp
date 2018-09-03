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
	*/ // 파싱 테스트 코드

	/*
	FILE *fp = fopen("C:\\Users\\user\\Desktop\\logdata\\20180824\\ap1.daouoffice.com_access_2018-08-24.txt", "r");
	char str[2048];
	clock_t st, et;

	st = clock();
	while (fgets(str, 2048, fp)) {
		// printf("%s", str);
	}
	et = clock();

	printf("걸린 시간: %f초\n", (float)(et - st) / 1000);
	*/ // 파일 입출력 시간 측정
	system("pause");
	return 0;
}