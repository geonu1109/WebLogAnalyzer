#include "DataConfig.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#define BUFFER_SIZE 2048

DataConfig::DataConfig(void) {
	char path[] = "..\\CppWebLogAnalyzer\\wlacfg.txt";
	load(path);
}

DataConfig::~DataConfig() {
	if(LOG_FILE_DIR) free(LOG_FILE_DIR);
}

void DataConfig::load(char *path) {
	 FILE *fp = FileProc::open(path, "r");
	 char buffer[BUFFER_SIZE];
	 char *pToken;

	 while (fgets(buffer, BUFFER_SIZE, fp)) {
		 pToken = strtok(buffer, " ");
		 if (pToken[0] == '#') continue; // #���� �����ϴ� ���� �ּ�ó��
		 if (!strcmp("LOG_FILE_DIR", pToken)) {
			 pToken = strtok(NULL, " \n");
			 LOG_FILE_DIR = (char *)malloc(strlen(pToken) + 1);
			 strcpy(LOG_FILE_DIR, pToken);
		 } // �α����� ���
		 if (!strcmp("LOG_FILE_COUNT", pToken)) {
			 pToken = strtok(NULL, " ");
			 LOG_FILE_COUNT = atoi(pToken);
		 } // �α����� ����
		 if (!strcmp("FIELD_COUNT", pToken)) {
			 pToken = strtok(NULL, " ");
			 FIELD_COUNT = atoi(pToken);
		 } // �ʵ� ����
		 if (!strcmp("INDEX_RESPONSE_TIME", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_RESPONSE_TIME = atoi(pToken);
		 } // ����ð� �ʵ� ��ġ
		 if (!strcmp("INDEX_DATETIME", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_DATETIME = atoi(pToken);
		 } // ��¥ �� �ð� �ʵ� ��ġ
		 if (!strcmp("INDEX_HTTP_STATUS", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_HTTP_STATUS = atoi(pToken);
		 } // HTTP ���� �ʵ� ��ġ
	 }

	 FileProc::close(fp);
}