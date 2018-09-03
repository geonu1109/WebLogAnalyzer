#include "Model.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>

Model::Model(const DataConfig &config) : pConfig(&config) {
	field = (char **)malloc(sizeof(char *) * pConfig->FIELD_COUNT); // �ʵ� ������ŭ �ʵ� ������ �Ҵ�
}

Model::~Model() {
	free(field); // �ʵ� ������ ����
}

void Model::function1(const DataInput *pData) {
	char path[256];
	FILE *ifp = NULL, *ofp = NULL;
	char buffer[2048];
	clock_t st, et;

	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) {
		sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, i + 1, "daouoffice.com_access", pData->year, pData->month, pData->day); // �Է����� �̸� ����
		ifp = FileProc::open(path, "r"); // �Է����� ����
		sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc1.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, i + 1, "daouoffice.com_access", pData->year, pData->month, pData->day); // ������� �̸� ����
		ofp = FileProc::open(path, "w"); // ������� ����

		st = clock();
		while (fgets(buffer, 2048, ifp)) // �Է������� ���� ������ �α׸� �� �پ� �о����
		{
			splitBuffer(buffer); // �о�� �α׸� �ʵ� ������ �и�
			if (isValidTime(pData) && atof(field[pConfig->INDEX_RESPONSE_TIME-1]) >= pData->delay) // �ش� �αװ� ��ȿ�ð��� �α��̰� ���� �ð��� ���� �ð��� ���� ���
			{
				fprintf(ofp, "%s", record); // ������Ͽ� ����
			}
		}
		et = clock();
		printf("%s %f seconds\n", path, (float)(et - st) / 1000);

		FileProc::close(ifp); // �Է����� �ݱ�
		FileProc::close(ofp); // ������� �ݱ�
	}
}

void Model::splitBuffer(char *buffer) // �Ű������� �Է¹��� ���ڵ��� �ʵ带 ������ �������� �ʵ�� ������ ��������� �����ϴ� �޼ҵ�
{
	std::stack<char> stk;
	int iField = 0;
	int len = strlen(buffer);

	strcpy_s(record, 2048, buffer); // ���ڵ� ����
	field[iField++] = &buffer[0]; // ù��° �ʵ� ��ġ ����

	for (int i = 0; i < len && iField < pConfig->FIELD_COUNT; i++) // �Է¹��� ���ڵ带 �� ���ھ� ��ȸ
	{
		if (buffer[i] == ' ' && stk.empty()) { // ������ ����� �� ������ ���� ���
			buffer[i] = '\0'; // ������ �� ���ڷ� ����
			field[iField++] = &buffer[i + 1]; // ���� ���� ���ں��� �� �ʵ� ����
		}
		else if (buffer[i] == '[') // �ʵ� ���� ���ȣ�� �����ϴ� ���
		{
			stk.push(buffer[i]); // ���ÿ� ���ȣ ����
		} 
		else if (buffer[i] == ']' && !stk.empty() && stk.top() == '[') // ���ȣ�� ������ ��� ���ÿ� ���ȣ�� ������
		{
			stk.pop(); // ���ÿ��� ���ȣ ����
		}
		else if (buffer[i] == '\"') // �ʵ� ���� ū����ǥ�� ���
		{
			if (!stk.empty() && stk.top() == '\"') { // ���ÿ� ū����ǥ�� ������
				stk.pop(); // ���ÿ��� ū����ǥ ����
			}
			else { // ������ ��ų� ������ �� ���� ū ����ǥ�� �ƴ� ���
				stk.push(buffer[i]); // ū����ǥ ����
			}
		}
	}
	buffer[len - 1] = '\0'; // ���� ������ ���๮�ڸ� �ι��ڷ� ����
}

int Model::isValidTime(const DataInput *pData) {
	int hour, minute, second;
	char tmp[3];

	strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][13], 2);
	hour = atoi(tmp);
	if (hour > pData->hour_start && hour < pData->hour_end) {
		return 1;
	}
	else if (hour == pData->hour_start || hour == pData->hour_end) {
		strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][16], 2);
		minute = atoi(tmp);
		if (minute > pData->minute_start && minute < pData->minute_end) {
			return 1;
		}
		else if (minute == pData->minute_start || minute == pData->minute_end) {
			strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][19], 2);
			second = atoi(tmp);
			if (second >= pData->second_start && second <= pData->second_end) {
				return 1;
			}
		}
	}
	return 0;
}