#include "LogMonitor.h"
#include "Console.h"
#include "LogData.h"
#include "LogFactory.h"
#include <stack>
#include <thread>
#include <ctime>

LogMonitor::LogMonitor(void) {
}

LogMonitor::~LogMonitor(void) {
}

void LogMonitor::run(void) {
	stack<thread> stkThread;

	for (int iLogFile = 1; iLogFile < ConfigData::getInstance().getNumberOfFile() + 1; iLogFile++) {
		stkThread.push(thread(&subprocess, getLogFilePath(iLogFile)));
	}
	
	while (!stkThread.empty()) {
		stkThread.top().join();
		stkThread.pop();
	}
}

void LogMonitor::subprocess(const string &strLogFilePath) {
	try {
		ifstream ifLog(strLogFilePath);
		LogData *pDataLog = LogFactory::getInstance().create();
		streampos posPrev(ifLog.seekg(0, ios::end).tellg()), posCur;
		string strBuffer;

		// error handling
		if (ifLog.fail()) {
			Console::getInstance().print(strLogFilePath);
			throw string("fail to open log file");
		}

		ifLog.close();

		while (true) {
			this_thread::sleep_for(chrono::seconds(1));

			ifLog.open(strLogFilePath);
			posCur = ifLog.seekg(0, ios::end).tellg();
			if (posCur > posPrev) {
				ifLog.seekg(posPrev);

				while (!ifLog.eof()) {
					getline(ifLog, strBuffer);
					pDataLog->update(strBuffer);
					if (pDataLog->isValid() && !pDataLog->isStaticResource()) {
						Console::getInstance().print(pDataLog->getLogRecord());
					}
				}
				posPrev = posCur;
			}

			ifLog.close();
		}
	}
	catch (const string &strErrMsg) {
		Console::getInstance().printErr(strErrMsg);
		system("pause");
		exit(1);
	}
}

const string LogMonitor::getLogFilePath(const int &iLogFile) {
	char strBuffer[128];
	time_t secNow;
	tm tmNow;

	secNow = time(nullptr);
	localtime_s(&tmNow, &secNow);

	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);

	return strBuffer;
}