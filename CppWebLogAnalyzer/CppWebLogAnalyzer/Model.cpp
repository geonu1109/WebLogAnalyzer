#include "Model.h"
#include "FileProc.h"
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>

Model::Model(const DataConfig &config) : pConfig(&config) {
	field = (char **)malloc(sizeof(char *) * pConfig->FIELD_COUNT); // 필드 개수만큼 필드 포인터 할당
}

Model::~Model() {
	free(field); // 필드 포인터 해제
}

void Model::function1(const DataInput *pData) {
	char path[256];
	FILE *ifp = NULL, *ofp = NULL;
	char buffer[2048];
	clock_t st, et;

	for (int i = 0; i < pConfig->LOG_FILE_COUNT; i++) {
		sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, i + 1, "daouoffice.com_access", pData->year, pData->month, pData->day); // 입력파일 이름 지정
		ifp = FileProc::open(path, "r"); // 입력파일 열기
		sprintf(path, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc1.txt", pConfig->LOG_FILE_DIR, pData->year, pData->month, pData->day, i + 1, "daouoffice.com_access", pData->year, pData->month, pData->day); // 출력파일 이름 지정
		ofp = FileProc::open(path, "w"); // 출력파일 열기

		st = clock();
		while (fgets(buffer, 2048, ifp)) // 입력파일이 끝날 때까지 로그를 한 줄씩 읽어오기
		{
			splitBuffer(buffer); // 읽어온 로그를 필드 단위로 분리
			if (isValidTime(pData) && atof(field[pConfig->INDEX_RESPONSE_TIME-1]) >= pData->delay) // 해당 로그가 유효시간의 로그이고 지연 시간이 기준 시간을 넘은 경우
			{
				fprintf(ofp, "%s", record); // 출력파일에 쓰기
			}
		}
		et = clock();
		printf("%s %f seconds\n", path, (float)(et - st) / 1000);

		FileProc::close(ifp); // 입력파일 닫기
		FileProc::close(ofp); // 출력파일 닫기
	}
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