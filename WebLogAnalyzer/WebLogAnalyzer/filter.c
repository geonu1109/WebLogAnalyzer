#include <stdio.h>
#include "utility.h"
#define BUF_SIZE 2048

extern int g_nFilePerDay;
extern char *g_strLogDir;
extern char *g_strLogFileName;

void filterDelayedAPI(void) {
	FILE *fpLog;
	char strDate[9];
	char strTimeStart[7];
	char strTimeEnd[7];
	int i;
	char strLogFile[BUF_SIZE];

	printf("date(YYYYMMDD): ");
	scanf("%s", strDate);
	printf("start time(HHMMSS): ");
	scanf("%s", strTimeStart);
	printf("end time(HHMMSS): ");
	scanf("%s", strTimeEnd);

	for (i = 0; i < g_nFilePerDay; i++) {
		sprintf(strLogFile, "%s\\%s\\ap%d.%s_%s-%s-%s", g_strLogDir, strDate, i+1, g_strLogFileName);
		fpLog = openFile()
	}
}

int main(int argc, const char * argv[]) {
	FILE *fpLog = NULL;
	char strBuf[BUF_SIZE], strLine[BUF_SIZE];
	char *pToken = NULL, *pPrevToken = NULL;
	fpLog = fopen(FILE_PATH, "r");
	while (fgets(strBuf, BUF_SIZE, fpLog)) {
		strncpy(strLine, strBuf, strlen(strBuf) + 1);
		pToken = strtok(strBuf, " ");
		while (pToken) {
			pPrevToken = pToken;
			pToken = strtok(NULL, " ");
		}
		if (atof(pPrevToken) >= RES_TIME_LIMIT) {
			printf("%s\n", strLine);
		}
	}
	printf("%d\n", cnt);

	return 0;
}