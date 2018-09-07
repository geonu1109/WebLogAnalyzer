#include "HttpStatusCounterThread.h"
#include "FilePathGenerator.h"
#include "Data/DataConfig.h"
#include "Data/DataInput.h"
#include "Data/DataLog.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <stack>
#include <vector>
#include <thread>

mutex HttpStatusCounterThread::m_mtxList;

HttpStatusCounterThread::HttpStatusCounterThread()
{
}


HttpStatusCounterThread::~HttpStatusCounterThread()
{
}


void HttpStatusCounterThread::process(void) {
	ofstream ofResult(FilePathGenerator::getOutFilePath(0));
	clock_t st, et;
	list<pair<int, int>> arrlistHourlyStatus[24]; // HTTP Status Code, Count
	list<pair<int, int>>::iterator iterHourlyStatus;
	stack<thread> stkThread;

	// input

	st = clock();

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) {
		stkThread.push(thread(&subprocess, iFile, arrlistHourlyStatus)); // 파일 별로 스레드 할당
	}

	while (!stkThread.empty()) {
		stkThread.top().join(); // 스레드가 종료될 때 까지 대기
		stkThread.pop(); // 종료된 스레드 제거
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;

	// output

	st = clock();

	for (int i = 0; i < 24; i++) {
		arrlistHourlyStatus[i].sort();
		ofResult << i << " o'clock" << endl;
		for (iterHourlyStatus = arrlistHourlyStatus[i].begin(); iterHourlyStatus != arrlistHourlyStatus[i].end(); iterHourlyStatus++) {
			ofResult << "  [" << iterHourlyStatus->first << "] " << iterHourlyStatus->second << " times" << endl;
		}
		ofResult << endl;
	}

	et = clock();
	cout << "[system] File output completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
}

void HttpStatusCounterThread::subprocess(const int &iFile, list<pair<int, int>> *arrlistHourlyStatus) {
	list<pair<int, int>>::iterator iterHourlyStatus;
	int nHour, nHttpStatusCode;
	bool isInserted = false;
	clock_t st, et;

	st = clock();

	DataLog dataLog(FilePathGenerator::getInFilePath(iFile)); // 로그 파일 객체 생성
	while (!dataLog.nextRecord().empty()) // 로그 한 줄씩 불러오기
	{
		nHour = dataLog.getHour();
		isInserted = false;
		nHttpStatusCode = dataLog.getHttpStatusCode();
 
		for (iterHourlyStatus = arrlistHourlyStatus[nHour].begin(); iterHourlyStatus != arrlistHourlyStatus[nHour].end(); iterHourlyStatus++) // HTTP Status Code 가 저장된 리스트 조회
		{
			if (iterHourlyStatus->first == nHttpStatusCode) // 이미 리스트에 등록된 게 있으면
			{
				m_mtxList.lock();
				iterHourlyStatus->second++; // 카운터 1 증가(임계영역)
				m_mtxList.unlock();

				isInserted = true;
				break;
			}
		}
		if (!isInserted) // 리스트에 아직 등록되지 않은 Code이면
		{
			m_mtxList.lock();
			arrlistHourlyStatus[nHour].push_back(pair<int, int>(nHttpStatusCode, 1)); // 리스트에 등록(임계영역)
			m_mtxList.unlock();
		}
	}

	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
}