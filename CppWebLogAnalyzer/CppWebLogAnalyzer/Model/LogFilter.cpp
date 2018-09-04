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

	for (int iFile = 0; iFile < m_dataConfig.getNumberOfLogFile(); iFile++) {
		st = clock();
		DataLog log(m_dataConfig, dataInput, iFile + 1);
		ofResult.open(getOutFilePath(dataInput, 1, iFile + 1));
		if (!ofResult.is_open()) {
			cout << "result파일 열기 실패" << endl;
		}

		while (!log.nextRecord().empty()) {
			if (log.getResponseTime() >= dataInput.getDelayLimit()) {
				ofResult << log.getRecord() << endl;
			}
		}
		ofResult.close();
		et = clock();
		cout << iFile + 1 << "번 째 파일 끝: " << (float)(et - st) / 1000 << "초" << endl;
	}
}

string LogFilter::getOutFilePath(const DataInput &dataInput, const int &iProc, const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc%d.txt", m_dataConfig.getPathLogFileDir().c_str(), dataInput.getYear(), dataInput.getMonth(), dataInput.getDay(), iFile, "daouoffice.com_access", dataInput.getYear(), dataInput.getMonth(), dataInput.getDay(), iProc);
	return string(strFilePath);
}