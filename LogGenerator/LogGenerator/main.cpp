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

const string strLogDirPath("C:/Users/user/Desktop/logdata");

string getLogFilePath(const int &iLogFile) {
	char strBuffer[128];
	time_t secNow;
	tm tmNow;

	secNow = time(nullptr);
	localtime_s(&tmNow, &secNow);

	sprintf_s(strBuffer, 128, "%s/%04d%02d%02d/ap%d.%s_%04d-%02d-%02d.txt", strLogDirPath.c_str(), tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday, iLogFile, "daouoffice.com_access", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);

	return strBuffer;
}

int main(void) {
	try {
		ConfigData::load("../LogGenerator/loggencfg.txt");
		ifstream ifFile("C:/Users/user/Desktop/logdata/20180824/ap1.daouoffice.com_access_2018-08-24.txt");
		ofstream ofFile;
		string strBuffer;
		int count = 1;
		streampos pos;
		LogData dataLog;

		srand(time(nullptr));
		system("mkdir C:\\Users\\user\\Desktop\\logdata\\20180913");
		ofFile.open(getLogFilePath(1));
		ofFile.close();

		while (true) {
			this_thread::sleep_for(chrono::milliseconds(100));

			ofFile.open(getLogFilePath(1), ios::app);
			pos = (float)rand() / RAND_MAX * ifFile.seekg(0, ios::end).tellg() - 1000;
			cout << "pos: " << pos << endl;
			ifFile.seekg(pos);
			getline(ifFile, strBuffer); // 불완전한 로그 제거
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
