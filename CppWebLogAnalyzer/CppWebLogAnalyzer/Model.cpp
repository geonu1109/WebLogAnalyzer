//#include "Model.h"
//#include "FileProc.h"
//#include "CounterHTTPStatus.h"
//#include <cstdlib>
//#include <cstring>
//#include <stack>
//#include <ctime>
//#include <list>
//using namespace std;
//
//Model::Model(const DataConfig &config) : pConfig(&config) {
//	field = (char **)malloc(sizeof(char *) * pConfig->FIELD_COUNT); // �ʵ� ������ŭ �ʵ� ������ �Ҵ�
//}
//
//Model::~Model() {
//	free(field); // �ʵ� ������ ����
//}
//
//void Model::function1(const DataInput *pData) {
//	FILE *ifp = NULL, *ofp = NULL;
//	char buffer[2048];
//	clock_t st, et;
//
//	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) // ���� ��¥�� �α����� ������� ��ȸ
//	{
//
//		ifp = getIFP(pData, i + 1); // �Է����� ����
//		ofp = getOFP(pData, i + 1, 1); // ������� ����
//
//		st = clock();
//		while (fgets(buffer, 2048, ifp)) // �Է����Ͽ��� �α� �� �� �� ����
//		{
//			splitBuffer(buffer); // �о�� �α׸� �ʵ� ������ �и�
//			if (isValidTime(pData) && atof(field[pConfig->INDEX_RESPONSE_TIME - 1]) >= pData->delay) // �ش� �αװ� ��ȿ�ð��� �α��̰� ���� �ð��� ���� �ð��� ���� ���
//			{
//				fprintf(ofp, "%s", record); // ������Ͽ� ����
//			}
//
//			FileProc::close(ifp); // �Է����� �ݱ�
//			FileProc::close(ofp); // ������� �ݱ�
//		}
//		et = clock();
//		printf("%d��° ���� ó�� �ð�: %f ��\n", i + 1, (float)(et - st) / 1000);
//	}
//}
//
//void Model::function3(const DataInput *pData) {
//	FILE *ifp = NULL, *ofp = NULL;
//	list<CounterHTTPStatus *> listCounterStatus;
//	list<CounterHTTPStatus *>::iterator iterList;
//	char buffer[2048];
//	int isCounted = 0;
//	int curHour;
//	clock_t st, et;
//
//	ofp = getOFP(pData, 0, 3);
//	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) // ���� ��¥�� �α����� ������� ��ȸ
//	{
//		st = clock();
//		ifp = getIFP(pData, i + 1);
//		while (fgets(buffer, 2048, ifp)) // �Է����Ͽ��� �α� �� �� �� ����
//		{
//			splitBuffer(buffer);
//			curHour = getHour();
//			for (iterList = listCounterStatus.begin(); iterList != listCounterStatus.end(); iterList++) // ����Ʈ ��ȸ
//			{
//				if ((*iterList)->getHour() == curHour && (*iterList)->getCode() == atoi(field[pConfig->INDEX_HTTP_STATUS - 1])) // ����Ʈ�� ��ϵ� ���°� �ִ� ���
//				{
//					(*iterList)->incrCounter();
//					isCounted = 1;
//					break;
//				}
//			}
//			if (!isCounted) // ����Ʈ�� ����� ���� �� �� ���
//			{
//				listCounterStatus.push_back(new CounterHTTPStatus(curHour, atoi(field[pConfig->INDEX_HTTP_STATUS - 1])));
//				isCounted = 1;
//			}
//			isCounted = 0;
//		}
//		et = clock();
//		FileProc::close(ifp);
//		printf("%d�� ° ���� �Է� �ð�: %f ��\n", i + 1, (float)(et - st) / 1000);
//	}
//	///////////////////////////// �� �ؿ� ���ľ� ��
//	listCounterStatus.sort(greater<pair<int, int>>());
//	fprintf(ofp, "%02d o'clock:\n");
//	for (iterList = listCounterStatus.begin(); iterList != listCounterStatus.end(); iterList++) {
//		fprintf(ofp, "%02d o'clock, %03d code: %+8d times\n", (*iterList)->getHour(), (*iterList)->getCode(), (*iterList)->getCounter());
//	}
//	fprintf(ofp, "\n");
//
//	FileProc::close(ofp);
//
//}
//
//void Model::splitBuffer(char *buffer) // �Ű������� �Է¹��� ���ڵ��� �ʵ带 ������ �������� �ʵ�� ������ ��������� �����ϴ� �޼ҵ�
//{
//	std::stack<char> stk;
//	int iField = 0;
//	int len = strlen(buffer);
//
//	strcpy_s(record, 2048, buffer); // ���ڵ� ����
//	field[iField++] = &buffer[0]; // ù��° �ʵ� ��ġ ����
//
//	for (int i = 0; i < len && iField < pConfig->FIELD_COUNT; i++) // �Է¹��� ���ڵ带 �� ���ھ� ��ȸ
//	{
//		if (stk.empty() && buffer[i] == ' ') { // ������ ����� �� ������ ���� ���
//			buffer[i] = '\0'; // ������ �� ���ڷ� ����
//			field[iField++] = &buffer[i + 1]; // ���� ���� ���ں��� �� �ʵ� ����
//		}
//		else if (buffer[i] == '[') // �ʵ� ���� ���ȣ�� �����ϴ� ���
//		{
//			stk.push(buffer[i]); // ���ÿ� ���ȣ ����
//		}
//		else if (buffer[i] == ']' && !stk.empty() && stk.top() == '[') // ���ȣ�� ���� �� ������ ����Ⱑ ���ȣ�� �����̾��� ���
//		{
//			stk.pop(); // ���ÿ��� ���ȣ ����
//		}
//		else if (buffer[i] == '\"') // ������ i��° ���� ū����ǥ�� ���
//		{
//			if (!stk.empty() && stk.top() == '\"') { // ������ ����Ⱑ ū����ǥ�� ���
//				stk.pop(); // ���ÿ��� ū����ǥ ����
//			}
//			else { // ������ ��ų� ������ �� ���� ū ����ǥ�� �ƴ� ���
//				stk.push(buffer[i]); // ū����ǥ ����
//			}
//		}
//	}
//	buffer[len - 1] = '\0'; // ���� ������ ���๮�ڸ� �ι��ڷ� ����
//}
//
//int Model::isValidTime(const DataInput *pData) // ���� ��ü�� ���� �α��� �ð��� ��ȿ�� �ð��� �α��̸� �� �ƴϸ� ������ ��ȯ�ϴ� �޼ҵ�
//{
//	int hour, minute, second;
//	char tmp[3];
//
//	hour = getHour(); // �� ���� �޾ƿ���
//	if (hour > pData->hour_start && hour < pData->hour_end) // �ð� ��ȿ �� ������ ���
//	{
//		return 1; // 1�� ��ȯ
//	}
//	else if (hour == pData->hour_start || hour == pData->hour_end) // �ð� ��� ���� ���
//	{
//		minute = getMinute(); // �� ���� �޾ƿ���
//		if (minute > pData->minute_start && minute < pData->minute_end) // ���� ��ȿ �� ������ ���
//		{
//			return 1; // 1�� ��ȯ
//		}
//		else if (minute == pData->minute_start || minute == pData->minute_end) // ���� ��� ���� ���
//		{
//			second = getSecond(); // �� ���� �޾ƿ���
//			if (second >= pData->second_start && second <= pData->second_end) // �ʰ� ��ȿ �� ������ ���
//			{
//				return 1; // 1�� ��ȯ
//			}
//		}
//	}
//	return 0; // �� �ܿ��� 0�� ��ȯ
//}
//
//FILE *Model::getIFP(const DataInput *pData, int iAP) {
//	FILE *ifp = NULL;
//	char path[512];
//
//	sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, iAP, "daouoffice.com_access", pData->year, pData->month, pData->day); // �Է����� �̸� ����
//	ifp = FileProc::open(path, "r"); // �Է����� ����
//
//	return ifp; // �Է����������� ��ȯ
//}
//
//FILE *Model::getOFP(const DataInput *pData, int iAP, int iProc) {
//	FILE *ofp = NULL;
//	char path[512];
//
//	sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc%1d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, iAP, "daouoffice.com_access", pData->year, pData->month, pData->day, iProc); // ������� �̸� ����
//	ofp = FileProc::open(path, "w"); // ������� ����
//
//	return ofp; // ������������� ��ȯ
//}
//
//int Model::getHour(void) {
//	char strHour[3];
//
//	strncpy_s(strHour, 3, &field[pConfig->INDEX_DATETIME - 1][13], 2);
//	return atoi(strHour);
//}
//
//int Model::getMinute(void) {
//	char strMinute[3];
//
//	strncpy_s(strMinute, 3, &field[pConfig->INDEX_DATETIME - 1][16], 2);
//	return atoi(strMinute);
//}
//
//int Model::getSecond(void) {
//	char strSecond[3];
//
//	strncpy_s(strSecond, 3, &field[pConfig->INDEX_DATETIME - 1][19], 2);
//	return atoi(strSecond);
//}