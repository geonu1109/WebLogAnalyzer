#include "LogFilter.h"
#include "ConfigData.h"
#include "LogData.h"
#include "ArgumentData.h"
#include "Output.h"
#include "Console.h"
#include "LogFactory.h"
#include "PathGenerator.h"
#include <thread>
#include <stack>
#include <fstream>
#include <iostream>

int LogFilter::s_arrcTotalLog[24];
int LogFilter::s_arrcValidLog[24];
mutex LogFilter::s_mtxTotalLog;
mutex LogFilter::s_mtxValidLog;

void LogFilter::run(void) {
	stack<thread> stkThread;
	for (int i = 0; i < ConfigData::getInstance().getNumberOfFile(); i++) {
		stkThread.push(thread(&subprocess, i + 1)); // create threads; file indexes start at 1
	}
	for (int i = 0; i < ConfigData::getInstance().getNumberOfFile(); i++) {
		stkThread.top().join(); // join threads
		stkThread.pop(); // destroy threads
	}
	Console::getInstance()->printChart(s_arrcValidLog, s_arrcTotalLog); // print result
}

void LogFilter::subprocess(const int &iFile) {
	ifstream ifLog(PathGenerator::mkLogFilePath(iFile));
	string strBuffer;
	LogData *pDataLog = LogFactory::getInstance().create();
	//unsigned long int ulSize, ulPos;
	//unsigned short int ratio = 0;
	int arrcTotalLog[24] = { 0 }, arrcValidLog[24] = { 0 };

	try {
		if (ifLog.fail()) {
			Console::getInstance()->print(PathGenerator::mkLogFilePath(iFile));
			throw string("fail to open log file");
		}

		//ulSize = ifLog.seekg(0, ios::end).tellg();
		//ifLog.seekg(0, ios::beg);

		while (!ifLog.eof()) {
			getline(ifLog, strBuffer);
			pDataLog->update(strBuffer);

			if (!pDataLog->isValid()) {
				continue; // ignore error log
			}

			arrcTotalLog[pDataLog->getHour()]++; // count total log

			if (pDataLog->isConditional()) {
				arrcValidLog[pDataLog->getHour()]++; // count valid log
				Output::getInstance()->print(pDataLog->getLogRecord());
			}

			//ulPos = ifLog.tellg();
			//if (ratio != ulPos / (ulSize / 100)) {
			//	ratio = ulPos / (ulSize / 100);
			//	Console::getInstance().showProgress(ratio);
			//}
		}
		for (int i = 0; i < 24; i++) {
			s_mtxTotalLog.lock();
			s_arrcTotalLog[i] += arrcTotalLog[i];
			s_mtxTotalLog.unlock();

			s_mtxValidLog.lock();
			s_arrcValidLog[i] += arrcValidLog[i];
			s_mtxValidLog.unlock();
		}
	}
	catch (const string &strErrMsg) {
		Console::getInstance()->printErr(strErrMsg);
		system("pause");
		exit(1);
	}
}