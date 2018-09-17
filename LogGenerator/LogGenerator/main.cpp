// #define WINDOWS

#include "ConfigData.h"
#include "LogData.h"
#include "Console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;

string mkInputFilePath(const int &iLogFile) {
	char strBuffer[128];
    time_t secNow;
    tm tmNow;

    secNow = time(nullptr);

#ifdef WINDOWS
    localtime_s(&tmNow, &secNow);
	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), 2018, 8, 24, iLogFile, "daouoffice.com_access", 2018, 8, 24);
#else
	tmNow = *localtime(&secNow);
    sprintf(strBuffer, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
#endif

	return strBuffer;
}

string mkResultDirPath(void) {
	char strBuffer[128];
	time_t secNow;
	tm tmNow;

	secNow = time(nullptr);

#ifdef WINDOWS
    localtime_s(&tmNow, &secNow);
	sprintf_s(strBuffer, 128, "mkdir %s\\%04d%02d%02d", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
#else
    tmNow = *localtime(&secNow);
	sprintf(strBuffer, "mkdir %s/%04d%02d%02d", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
#endif

	return strBuffer;
}

string mkResultFilePath(const int &iLogFile) {
	char strBuffer[128];
	time_t secNow;
	tm tmNow;

	secNow = time(nullptr);

#ifdef WINDOWS
	localtime_s(&tmNow, &secNow);
	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
#else
    tmNow = *localtime(&secNow);
    sprintf(strBuffer, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", ConfigData::getInstance().getLogDirPath().c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
#endif

	return strBuffer;
}

int main(void) {
	try {
#ifdef WINDOWS
		ConfigData::load("../LogGenerator/loggencfg.txt");
#else
		ConfigData::load("/etc/loggencfg.txt");
#endif
		ifstream ifFile(mkInputFilePath(1));
		ofstream ofFile;
		string strBuffer;
		int count = 1;
		streampos pos;
		LogData dataLog;

		srand(time(nullptr));
		cout << "mkResultDirPath(): " << mkResultDirPath() << endl;
		system(mkResultDirPath().c_str());
		ofFile.open(mkResultFilePath(1));
		ofFile.close();

		while (true) {
			this_thread::sleep_for(chrono::milliseconds(100));

			ofFile.open(mkResultFilePath(1), ios::app);
			pos = (float)rand() / RAND_MAX * ifFile.seekg(0, ios::end).tellg() - 1000;
			cout << "pos: " << pos << endl;
			ifFile.seekg(pos);
			getline(ifFile, strBuffer); // remove uncomplete log
			getline(ifFile, strBuffer);
			dataLog.update(strBuffer);
			dataLog.setDateTime();
			ofFile << dataLog.getLogRecord() << endl;

			ofFile.close();
		}
	}
	catch (const string &strErrMsg) {
		Console::getInstance().printErr(strErrMsg);
		system("pause");
		exit(1);
	}

	system("pause");
	return 0;
}
