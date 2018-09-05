#include "LogFilter.h"
#include <iostream>
#include <fstream>
#include <ctime>

LogFilter::LogFilter(const DataConfig &dataConfig) : m_dataConfig(dataConfig) {
}

LogFilter::~LogFilter()
{
}

void LogFilter::filterDelayedApi(const DataInput &dataInput) {
	ofstream ofResult;
	clock_t st, et;
	bool boolPrev = false, boolCur = false;

	for (int iFile = 0; iFile < m_dataConfig.getNumberOfLogFile(); iFile++) {
		st = clock();
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1));
		ofResult.open(getOutFilePath(dataInput.getDate(), 1, iFile + 1));
		if (!ofResult.is_open()) {
			cout << endl;
			cout << "[method] void LogFilter::filterDelayedApi(const DataInput &dataInput)" << endl;
			cout << "[fatal error] fail to open result file" << endl;
			cout << "[file path] " << getOutFilePath(dataInput.getDate(), 1, iFile + 1) << endl;
			cout << endl;
			system("pause");
			exit(0);
		}
		boolPrev = false;
		boolCur = false;
		while (!dataLog.nextRecord().empty()) {
			boolCur = dataLog.isValidTime(dataInput.getTimeStart(), dataInput.getTimeEnd());
			if (boolCur == false && boolPrev == true) break;
			if (boolCur) {
				if (dataLog.getResponseTime() >= dataInput.getDelayLimit()) {
					ofResult << dataLog.getRecord() << endl;
				}
			}
			boolPrev = boolCur;
		}
		ofResult.close();
		et = clock();
		cout << endl;
		cout << "[system] " << iFile + 1 << "번 째 파일 끝: " << (float)(et - st) / 1000 << "초" << endl;
		cout << endl;
	}
}

const string LogFilter::getInFilePath(const tm &tmDate, const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", m_dataConfig.getPathLogFileDir().c_str(), tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iFile, "daouoffice.com_access", tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday); // 입력파일 이름 지정
	return string(strFilePath);
}

const string LogFilter::getOutFilePath(const tm &tmDate, const int &iProc, const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc%d.txt", m_dataConfig.getPathLogFileDir().c_str(), tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iFile, "daouoffice.com_access", tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iProc);
	return string(strFilePath);
}