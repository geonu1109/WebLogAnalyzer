#include "LogFilterThread.h"
#include "Data/DataConfig.h"
#include "Data/DataInput.h"
#include "Data/DataLog.h"
#include "FilePathGenerator.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <ctime>
#include <stack>
using namespace std;

LogFilterThread::LogFilterThread()
{
}

LogFilterThread::~LogFilterThread()
{
}

void LogFilterThread::process(void) {
	stack<thread> stkThread;
	clock_t st, et;
	int iFileLimit = DataConfig::getInstance().getNumberOfLogFile();

	st = clock();

	for (int iFile = 1; iFile < iFileLimit + 1; iFile++) {
		stkThread.push(thread(&subprocess, iFile)); // 파일 별로 스레드 할당
	}

	while (!stkThread.empty()) {
		stkThread.top().join(); // 스레드가 종료될 때 까지 대기
		stkThread.pop(); // 종료된 스레드 제거
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;
}

void LogFilterThread::subprocess(const int &iFile) {
	ofstream ofResult;
	clock_t st, et;

	st = clock();

	DataLog dataLog(FilePathGenerator::getInFilePath(iFile)); // 로그 파일을 읽고 관리하는 객체 생성
	ofResult.open(FilePathGenerator::getOutFilePath(iFile)); // 결과를 저장할 파일 열기

	while (!dataLog.nextRecord().empty()) // 로그 파일에 읽어올 레코드가 남아있는 동안 다음 레코드 불러오기
	{
		if (!dataLog.isValidTime(DataInput::getInstance().getTimeEnd())) break; // 읽어온 로그가 기록된 시간이 검색 기준 시간을 넘는 경우 해당 파일에서 레코드 불러오기 종료
		else if (dataLog.isValidTime(DataInput::getInstance().getTimeStart(), DataInput::getInstance().getTimeEnd())) // 읽어온 로그가 검색하고자 하는 시간에 속하는 경우
		{
			if (dataLog.getResponseTime() >= DataInput::getInstance().getDelayLimit()) // 해당 로그의 지연시간이 기준 지연시간 이상인 경우
			{
				ofResult << dataLog.getRecord() << endl; // 출력파일에 해당 로그 출력
			}
		}
	}
	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close(); // 결과 파일 닫기

}