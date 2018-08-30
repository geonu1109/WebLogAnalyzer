#include <stdio.h>
#include <stdlib.h>

FILE *openFile(const char * strFilePath, const char * strFileMode) {
	FILE *fp = fopen(strFilePath, strFileMode);
	if (fp == NULL) {
		printf("Fail to open file. FILENAME: \"%s\"\n", strFilePath);
		system("pause");
		exit(0);
	}
	return fp;
}