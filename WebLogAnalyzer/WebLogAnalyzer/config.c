#include <stdio.h>
#define CONFIG_FILE_PATH "..\\WebLogAnalyzer\\wlacfg.txt"
#define BUF_SIZE 2048

char g_strLogDir[BUF_SIZE];
int g_iResTime;
int g_nFilePerDay;
char g_strLogFileName[BUF_SIZE];

void loadConfig(void) {
	FILE *fpConfig = NULL;
	char strLine[BUF_SIZE];
	char *pToken;
	fpConfig = openFile(CONFIG_FILE_PATH, "r");

	while (fgets(strLine, BUF_SIZE, fpConfig)) {
		pToken = strtok(strLine, " \n");
		if (pToken[0] == '#' || (pToken[0] == '/' && pToken[1] == '/')) continue; // #또는 //으로 시작하는 줄은 주석처리
		if (!strcmp(pToken, "LogDir")) {
			pToken = strtok(NULL, " \n");
			strncpy(g_strLogDir, pToken, strlen(pToken));
		}
		if (!strcmp(pToken, "ResTimeIndex")) {
			pToken = strtok(NULL, " \n");
			g_iResTime = atoi(pToken);
		}
		if (!strcmp(pToken, "FilePerDay")) {
			pToken = strtok(NULL, " \n");
			g_nFilePerDay = atoi(pToken);
		}
		if (!strcmp(pToken, "LogFileName")) {
			pToken = strtok(NULL, " \n");
			strncpy(g_strLogFileName, pToken, strlen(pToken));
		}
	}
}