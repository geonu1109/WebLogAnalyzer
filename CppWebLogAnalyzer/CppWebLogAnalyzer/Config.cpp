#include "Config.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#define BUFFER_SIZE 2048

Config::Config(void) {
	char path[] = "..\\CppWebLogAnalyzer\\wlacfg.txt";
	load(path);
}

Config::~Config() {
	if(LOG_FILE_DIR) free(LOG_FILE_DIR);
}

void Config::load(char *path) {
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
		 } // ����ð� ��ġ
	 }

	 FileProc::close(fp);
}