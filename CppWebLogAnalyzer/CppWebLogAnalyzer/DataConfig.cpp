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
		 if (pToken[0] == '#') continue; // #으로 시작하는 줄은 주석처리
		 if (!strcmp("LOG_FILE_DIR", pToken)) {
			 pToken = strtok(NULL, " \n");
			 LOG_FILE_DIR = (char *)malloc(strlen(pToken) + 1);
			 strcpy(LOG_FILE_DIR, pToken);
		 } // 로그파일 경로
		 if (!strcmp("LOG_FILE_COUNT", pToken)) {
			 pToken = strtok(NULL, " ");
			 LOG_FILE_COUNT = atoi(pToken);
		 } // 로그파일 개수
		 if (!strcmp("FIELD_COUNT", pToken)) {
			 pToken = strtok(NULL, " ");
			 FIELD_COUNT = atoi(pToken);
		 } // 필드 개수
		 if (!strcmp("INDEX_RESPONSE_TIME", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_RESPONSE_TIME = atoi(pToken);
		 } // 응답시간 필드 위치
		 if (!strcmp("INDEX_DATETIME", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_DATETIME = atoi(pToken);
		 } // 날짜 및 시간 필드 위치
		 if (!strcmp("INDEX_HTTP_STATUS", pToken)) {
			 pToken = strtok(NULL, " ");
			 INDEX_HTTP_STATUS = atoi(pToken);
		 } // HTTP 상태 필드 위치
	 }

	 FileProc::close(fp);
}