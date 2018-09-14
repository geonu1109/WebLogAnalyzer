#include "LogFilter.h"
#include "ConfigData.h"
#include "LogData.h"
#include "ArgumentData.h"
#include "Console.h"
#include <thread>
#include <stack>
#include <fstream>

int LogFilter::arrcTotalLog[24];
int LogFilter::arrcValidLog[24];
 mutex LogFilter::mtxTotalLog;
 mutex LogFilter::mtxValidLog;

void LogFilter::run(void) {
	stack<thread> stkThread;
	for (int i = 0; i < ConfigData::getInstance().getNumberOfFile(); i++)
	{
		stkThread.push(thread(&subprocess, i + 1)); // file indexes start at 1
	}
	for (int i = 0; i < ConfigData::getInstance().getNumberOfFile(); i++) {
		stkThread.top().join();
		stkThread.pop();
	}
	// 전체 통계 출력
}

void LogFilter::subprocess(const int &iFile) {
	ifstream ifLog(getLogFilePath(iFile));
	string strBuffer;
	LogData dataLog;

	if (ifLog.fail()) {
		throw string("fail to open log file");
	}

	while (ifLog.eof()) {
		getline(ifLog, strBuffer);
		dataLog.update(strBuffer);

		mtxTotalLog.lock();
		arrcTotalLog[dataLog.getHour()]++; // count total log
		mtxTotalLog.unlock();

		if (dataLog.isValid()) // 유효값 검사 확인해볼 것
		{
			mtxValidLog.lock();
			arrcValidLog[dataLog.getHour()]++; // count valid log
			mtxValidLog.unlock();
			Console::getInstance().print(strBuffer);
		}
	}
}

const string LogFilter::getLogFilePath(const int &iLogFile) {
	char strBuffer[128];
	time_t secNow;
	tm tmNow;

	secNow = time(nullptr);
	localtime_s(&tmNow, &secNow);

	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);

	return strBuffer;
}