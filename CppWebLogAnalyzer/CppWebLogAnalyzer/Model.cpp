#include "Model.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>
#include <list>
#include <utility>
using namespace std;

Model::Model(const DataConfig &config) : pConfig(&config) {
	field = (char **)malloc(sizeof(char *) * pConfig->FIELD_COUNT); // 필드 개수만큼 필드 포인터 할당
}

Model::~Model() {
	free(field); // 필드 포인터 해제
}

void Model::function1(const DataInput *pData) {
	FILE *ifp = NULL, *ofp = NULL;
	char buffer[2048];
	clock_t st, et;

	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) // 동일 날짜의 로그 파일 한 개씩 수행
	{
		
		ifp = getIFP(pData, i + 1); // 입력파일 열기
		ofp = getOFP(pData, i + 1, 1); // 출력파일 열기

		st = clock();
		while (fgets(buffer, 2048, ifp)) // 입력파일이 끝날 때까지 로그를 한 줄씩 읽어오기
		{
			splitBuffer(buffer); // 읽어온 로그를 필드 단위로 분리
			if (isValidTime(pData) && atof(field[pConfig->INDEX_RESPONSE_TIME-1]) >= pData->delay) // 해당 로그가 유효시간의 로그이고 지연 시간이 기준 시간을 넘은 경우
			{
				fprintf(ofp, "%s", record); // 출력파일에 쓰기
			}

			FileProc::close(ifp); // 입력파일 닫기
			FileProc::close(ofp); // 출력파일 닫기
		}
		et = clock();
		printf("%d번째 파일 처리 시간: %f 초\n", i + 1, (float)(et - st) / 1000);
	}
}

void Model ::function3(const DataInput *pData) {
	FILE *ifp = NULL, *ofp = NULL;
	list<pair<int, int>> listCounterStatus; // first: 횟수, second: 상태
	list<pair<int, int>>::iterator iterList;
	char buffer[2048];
	int isCounted = 0;
	clock_t st, et;

	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) {
		st = clock();
		ifp = getIFP(pData, i + 1);
		while (fgets(buffer, 2048, ifp)) {
			splitBuffer(buffer);
			for (iterList = listCounterStatus.begin(); iterList != listCounterStatus.end(); iterList++) {
				if (iterList->second == atoi(field[pConfig->INDEX_HTTP_STATUS - 1])) {
					iterList->first++;
					isCounted = 1;
					break;
				}
			}
			if (!isCounted) {
				listCounterStatus.push_back(pair<int, int>(1, atoi(field[pConfig->INDEX_HTTP_STATUS - 1])));
				isCounted = 1;
			}
			isCounted = 0;
		}
		et = clock();
		FileProc::close(ifp);
		printf("%d번 째 파일 입력 시간: %f 초\n", i + 1, (float)(et - st) / 1000);
	}

	st = clock();
	ofp = getOFP(pData, 0, 3);
	listCounterStatus.sort(greater<pair<int, int>>());
	for (iterList = listCounterStatus.begin(); iterList != listCounterStatus.end(); iterList++) {
		fprintf(ofp, "%03d: %+8d times\n", iterList->second, iterList->first);
	}
	et = clock();
	FileProc::close(ofp);
	printf("파일 출력 시간: %f 초\n", (float)(et - st) / 1000);

}

void Model::splitBuffer(char *buffer) // 매개변수로 입력받은 레코드의 필드를 나누고 나누어진 필드와 원본을 멤버변수에 저장하는 메소드
{
	std::stack<char> stk;
	int iField = 0;
	int len = strlen(buffer);

	strcpy_s(record, 2048, buffer); // 레코드 복사
	field[iField++] = &buffer[0]; // 첫번째 필드 위치 지정

	for (int i = 0; i < len && iField < pConfig->FIELD_COUNT; i++) // 입력받은 레코드를 한 글자씩 조회
	{
		if (buffer[i] == ' ' && stk.empty()) { // 스택이 비었을 때 공백이 나온 경우
			buffer[i] = '\0'; // 공백을 널 문자로 변경
			field[iField++] = &buffer[i + 1]; // 공백 뒤의 문자부터 새 필드 시작
		}
		else if (buffer[i] == '[') // 필드 값이 대괄호로 시작하는 경우
		{
			stk.push(buffer[i]); // 스택에 대괄호 삽입
		} 
		else if (buffer[i] == ']' && !stk.empty() && stk.top() == '[') // 대괄호가 끝나는 경우 스택에 대괄호가 있으면
		{
			stk.pop(); // 스택에서 대괄호 삭제
		}
		else if (buffer[i] == '\"') // 필드 값이 큰따옴표인 경우
		{
			if (!stk.empty() && stk.top() == '\"') { // 스택에 큰따옴표가 있으면
				stk.pop(); // 스택에서 큰따옴표 제거
			}
			else { // 스택이 비거나 스택의 맨 위가 큰 따옴표가 아닌 경우
				stk.push(buffer[i]); // 큰따옴표 삽입
			}
		}
	}
	buffer[len - 1] = '\0'; // 버퍼 마지막 개행문자를 널문자로 변경
}

int Model::isValidTime(const DataInput *pData) // 현재 객체가 가진 로그의 시간이 유효한 시간의 로그이면 참 아니면 거짓을 반환하는 메소드
{
	int hour, minute, second;
	char tmp[3];

	strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][13], 2); // 필드에서 시 가져오기
	hour = atoi(tmp); // 시를 정수로 변환
	if (hour > pData->hour_start && hour < pData->hour_end) // 시가 유효 시 사이인 경우
	{
		return 1; // 1을 반환
	}
	else if (hour == pData->hour_start || hour == pData->hour_end) // 시가 경계 값인 경우
	{
		strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][16], 2); // 필드에서 분 가져오기
		minute = atoi(tmp); // 분을 정수로 변환
		if (minute > pData->minute_start && minute < pData->minute_end) // 분이 유효 분 사이인 경우
		{
			return 1; // 1을 반환
		}
		else if (minute == pData->minute_start || minute == pData->minute_end) // 분이 경계 값인 경우
		{
			strncpy_s(tmp, 3, &field[pConfig->INDEX_DATETIME - 1][19], 2); // 필드에서 초 가져오기
			second = atoi(tmp); // 초를 정수로 변환
			if (second >= pData->second_start && second <= pData->second_end) // 초가 유효 초 사이인 경우
			{
				return 1; // 1을 반환
			}
		}
	}
	return 0; // 그 외에는 0을 반환
}

FILE *Model::getIFP(const DataInput *pData, int iAP) {
	FILE *ifp = NULL;
	char path[512];

	sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, iAP, "daouoffice.com_access", pData->year, pData->month, pData->day); // 입력파일 이름 지정
	ifp = FileProc::open(path, "r"); // 입력파일 열기

	return ifp; // 입력파일포인터 반환
}

FILE *Model::getOFP(const DataInput *pData, int iAP, int iProc) {
	FILE *ofp = NULL;
	char path[512];

	sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc%1d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, iAP, "daouoffice.com_access", pData->year, pData->month, pData->day, iProc); // 출력파일 이름 지정
	ofp = FileProc::open(path, "w"); // 출력파일 열기

	return ofp; // 출력파일포인터 반환
}