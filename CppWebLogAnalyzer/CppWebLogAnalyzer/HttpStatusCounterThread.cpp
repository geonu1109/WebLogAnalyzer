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

mutex HttpStatusCounterThread::mtx;

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
		stkThread.push(thread(&subprocess, iFile, arrlistHourlyStatus));
	}
	while (!stkThread.empty()) {
		stkThread.top().join();
		stkThread.pop();
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

	DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
	while (!dataLog.nextRecord().empty()) {
		nHour = dataLog.getHour();
		isInserted = false;
		nHttpStatusCode = dataLog.getHttpStatusCode();
 
		for (iterHourlyStatus = arrlistHourlyStatus[nHour].begin(); iterHourlyStatus != arrlistHourlyStatus[nHour].end(); iterHourlyStatus++) {
			if (iterHourlyStatus->first == nHttpStatusCode) {
				mtxList.lock();
				iterHourlyStatus->second++;
				mtxList.unlock();
				isInserted = true;
				break;
			}
		}
		if (!isInserted) {
			mtxList.lock();
			arrlistHourlyStatus[nHour].push_back(pair<int, int>(nHttpStatusCode, 1));
			mtxList.unlock();
		}
	}

	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
}