#include "Model.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>

Model::Model(const Config &config) : pConfig(&config) {
	field = (char **)malloc(sizeof(char *) * pConfig->FIELD_COUNT);
}

Model::~Model() {
	free(field);
}

void Model::function1(const InputData *data) {
	char path[256];
	FILE *ifp = NULL, *ofp = NULL;
	char buffer[2048];

	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) {
		sprintf(path, "%s\\%s\\ap%d.%s_%s-%s-%s.txt", pConfig->LOG_FILE_DIR, data->DATE, i + 1, "daouoffice.com_access", data->DATE, data->DATE, data->DATE);
		ifp = FileProc::open(path, "r");
		sprintf(path, "%s\\%s\\ap%d.%s_%s-%s-%s_proc1.txt", pConfig->LOG_FILE_DIR, data->DATE, i + 1, "daouoffice.com_access", data->DATE, data->DATE, data->DATE);
		ofp = FileProc::open(path, "w");

		clock_t st, et;
		st = clock();
		while (fgets(buffer, 2048, ifp)) {
			strcpy_s(record, 2048, buffer);
			splitRecord(buffer);
			if (atof(field[pConfig->INDEX_RESPONSE_TIME-1]) >= data->delay) {
				fprintf(ofp, "%s", record);
			}
		}
		et = clock();
		printf("%s %f seconds\n", path, (float)(et - st) / 1000);

		FileProc::close(ifp);
		FileProc::close(ofp);
	}
}

void Model::splitRecord(char *record) {
	std::stack<char> stk;
	int iField = 0;
	int len = strlen(record);
	field[iField++] = &record[0];

	for (int i = 0; i < len && iField < pConfig->FIELD_COUNT; i++) {
		if (record[i] == ' ') {
			if (stk.empty()) {
				record[i] = '\0';
				field[iField++] = &record[i + 1];
			}
		}
		else if (record[i] == '[') {
			stk.push(record[i]);
		}
		else if (record[i] == ']' && stk.top() == '[') {
			stk.pop();
		}
		else if (record[i] == '\"') {
			if (!stk.empty() && stk.top() == '\"') {
				stk.pop();
			}
			else {
				stk.push(record[i]);
			}
		}
	}
	record[len - 1] = '\0';
}