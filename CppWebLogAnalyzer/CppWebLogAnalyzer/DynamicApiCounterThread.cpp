#include "DynamicApiCounterThread.h"
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

mutex DynamicApiCounterThread::m_mtxList;

DynamicApiCounterThread::DynamicApiCounterThread()
{
}

DynamicApiCounterThread::~DynamicApiCounterThread()
{
}

void DynamicApiCounterThread::process(void) {
	ofstream ofResult(FilePathGenerator::getOutFilePath(0));
	list<pair<string, int>> listApiCounter;
	list<pair<string, int>>::iterator iterApiCounter;
	clock_t st, et;
	stack<thread> stkThread;

	// input

	st = clock();

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) {
		stkThread.push(thread(&subprocess, iFile, &listApiCounter)); // 파일 별로 스레드 할당
	}

	while (!stkThread.empty()) {
		stkThread.top().join(); // 스레드가 종료될 때 까지 대기
		stkThread.pop(); // 종료된 스레드 제거
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;

	// output

	st = clock();

	listApiCounter.sort(&desc);

	ofResult << DataInput::getInstance().getTimeStart().tm_hour << ":" << DataInput::getInstance().getTimeStart().tm_min << ":" << DataInput::getInstance().getTimeStart().tm_sec << " - ";
	ofResult << DataInput::getInstance().getTimeEnd().tm_hour << ":" << DataInput::getInstance().getTimeEnd().tm_min << ":" << DataInput::getInstance().getTimeEnd().tm_sec << endl;
	if (DataInput::getInstance().getSelect() == 2) {
		ofResult << "HTTP Status Code: " << DataInput::getInstance().getHttpStatusCode() << endl;
		ofResult << "HTTP Request Method: " << DataInput::getInstance().getHttpRequestMethod() << endl;
	}
	ofResult << endl;

	for (iterApiCounter = listApiCounter.begin(); iterApiCounter != listApiCounter.end(); iterApiCounter++) {
		ofResult << "[" << iterApiCounter->first << "] " << iterApiCounter->second << " times" << endl;
	}

	et = clock();
	cout << "[system] File output completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
}

void DynamicApiCounterThread::subprocess(const int &iFile, list<pair<string, int>> *listApiCounter) {
	list<pair<string, int>>::iterator iterApiCounter;
	DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
	string strApi;
	bool isInserted = false;
	clock_t st, et;

	st = clock();

	while (!dataLog.nextRecord().empty()) // 파일 내 레코드 조회
	{
		if (!dataLog.isValidTime(DataInput::getInstance().getTimeEnd())) break; // 읽어온 로그의 기록 시간이 끝 시간을 넘으면 해당 파일에서 레코드 읽어오기 종료
		else if (!dataLog.isStaticResource() && dataLog.isValidTime(DataInput::getInstance().getTimeStart(), DataInput::getInstance().getTimeEnd())) {
			if (DataInput::getInstance().getSelect() == 4 || (dataLog.getHttpRequestMethod() == DataInput::getInstance().getHttpRequestMethod() && dataLog.getHttpStatusCode() == DataInput::getInstance().getHttpStatusCode())) {
				isInserted = false;
				strApi = dataLog.getApiGroup();
				for (iterApiCounter = listApiCounter->begin(); iterApiCounter != listApiCounter->end(); iterApiCounter++) // 리스트 조회
				{
					if (iterApiCounter->first == strApi) {
						m_mtxList.lock();
						iterApiCounter->second++;
						m_mtxList.unlock();
						isInserted = true;
						break;
					}
				}
				if (!isInserted) {
					m_mtxList.lock();
					listApiCounter->push_back(pair<string, int>(strApi, 1));
					m_mtxList.unlock();
				}
			}
		}
	}

	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
}

const bool DynamicApiCounterThread::desc(pair<string, int> &first, pair<string, int> &second) {
	if (first.second > second.second) return true;
	else return false;
}