#include "ClientAgentClassifierThread.h"
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

mutex ClientAgentClassifierThread::mtxList;

ClientAgentClassifierThread::ClientAgentClassifierThread()
{
}

ClientAgentClassifierThread::~ClientAgentClassifierThread()
{
}

void ClientAgentClassifierThread::process(void) {
	list<pair<pair<string, string>, int>> arrlistClientAgent[24];
	list<pair<pair<string, string>, int>>::iterator iterClientAgent;
	ofstream ofResult;
	stack<thread> stkThread;

	clock_t st, et;
	st = clock();

	// input

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) {
		stkThread.push(thread(&subprocess, iFile, arrlistClientAgent)); // 파일 별로 스레드 할당
		
	}

	while (!stkThread.empty()) {
		stkThread.top().join(); // 스레드가 종료될 때 까지 대기
		stkThread.pop(); // 종료된 스레드 제거
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;

	// output

	ofResult.open(FilePathGenerator::getOutFilePath(0));

	st = clock();

	for (int i = 0; i < 24; i++) {
		arrlistClientAgent[i].sort();
		ofResult << i << " o'clock" << endl;
		for (iterClientAgent = arrlistClientAgent[i].begin(); iterClientAgent != arrlistClientAgent[i].end(); iterClientAgent++) {
			ofResult << "  [" << iterClientAgent->first.first << ", " << iterClientAgent->first.second << "] " << iterClientAgent->second << " times" << endl;
		}
		ofResult << endl;
	}

	et = clock();
	cout << "[system] File output completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
}

void ClientAgentClassifierThread::subprocess(const int &iFile, list<pair<pair<string, string>, int>> arrlistClientAgent[]) {
	list<pair<pair<string, string>, int>>::iterator iterClientAgent;
	DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
	pair<string, string> strClientAgent;
	int nHour;
	bool isInserted = false;

	clock_t st, et;
	st = clock();

	while (!dataLog.nextRecord().empty()) {
		strClientAgent.first = dataLog.getBrowser();
		strClientAgent.second = dataLog.getOS();
		isInserted = false;

		//if (dataLog.getBrowser() == "etc" || dataLog.getOS() == "etc") {
		//	cout << "[User-Agent] " << dataLog.getClientAgentField() << endl;
		//}

		nHour = dataLog.getHour();

		for (iterClientAgent = arrlistClientAgent[nHour].begin(); iterClientAgent != arrlistClientAgent[nHour].end(); iterClientAgent++) {
			if (iterClientAgent->first.first == strClientAgent.first && iterClientAgent->first.second == strClientAgent.second) {
				mtxList.lock();
				iterClientAgent->second++;
				mtxList.unlock();
				isInserted = true;
			}
		}
		if (!isInserted) {
			mtxList.lock();
			arrlistClientAgent[nHour].push_back(pair<pair<string, string>, int>(strClientAgent, 1));
			mtxList.unlock();
		}
	}

	et = clock();
	cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
}