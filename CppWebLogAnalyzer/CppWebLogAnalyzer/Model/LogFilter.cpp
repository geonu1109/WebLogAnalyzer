#include "LogFilter.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include <utility>

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
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1)); // �α� ���� �ڷ� ���� ��ü ����
		ofResult.open(getOutFilePath(dataInput.getDate(), 1, iFile + 1)); // ��� ���� ����
		if (!ofResult.is_open()) // ������ ����� ���ȳ� �˻�
		{
			cout << endl;
			cout << "[method] void LogFilter::filterDelayedApi(const DataInput &dataInput)" << endl;
			cout << "[fatal error] fail to open result file" << endl;
			cout << "[file path] " << getOutFilePath(dataInput.getDate(), 1, iFile + 1) << endl;
			cout << endl;
			system("pause");
			exit(0);
		}
		while (!dataLog.nextRecord().empty()) // �α� ���Ͽ��� ���ڵ� ���� �� ��������
		{
			if (dataLog.isValidTime(dataInput.getTimeStart(), dataInput.getTimeEnd())) {
				if (dataLog.getResponseTime() >= dataInput.getDelayLimit()) {
					ofResult << dataLog.getRecord() << endl;
				}
			}
		}
		ofResult.close(); // ��� ���� �ݱ�
		et = clock();
		cout << endl;
		cout << "[system] File " << iFile + 1 << " end: " << (float)(et - st) / 1000 << " seconds" << endl;
		cout << endl;
	}
}

void LogFilter::sortDynamicApi(const DataInput &dataInput) {
	ofstream ofResult(getOutFilePath(dataInput.getDate(), 2, 0));
	list<pair<string, int>> listApiCounter;
	list<pair<string, int>>::iterator iterApiCounter;
	bool isInserted = false;
	clock_t st, et;

	if (ofResult.fail()) {
		cout << endl;
		cout << "[method] void LogFilter::sortDynamicApi(const DataInput &dataInput)" << endl;
		cout << "[fatal error] fail to open result file" << endl;
		cout << "[file path] " << getOutFilePath(dataInput.getDate(), 2, 0) << endl;
		cout << endl;
		system("pause");
		exit(0);
	}

	for (int iFile = 0; iFile < m_dataConfig.getNumberOfLogFile(); iFile++) // ���� ��ȸ
	{
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1));
		
		st = clock();

		while (!dataLog.nextRecord().empty()) // ���� �� ���ڵ� ��ȸ
		{
			if (dataLog.getHttpRequestMethod() == dataInput.getHttpRequestMethod() && dataLog.getHttpStatusCode() == dataInput.getHttpStatusCode()) {
				isInserted = false;
				for (iterApiCounter = listApiCounter.begin(); iterApiCounter != listApiCounter.end(); iterApiCounter++) // ����Ʈ ��ȸ
				{
					if (iterApiCounter->first == dataLog.getApi()) {
						iterApiCounter->second++;
						isInserted = true;
					}
				}
				if (!isInserted) {
					listApiCounter.push_back(pair<string, int>(dataLog.getApi(), 1));
				}
			}
		}

		et = clock();
		cout << endl;
		cout << "[system] File " << iFile + 1 << " complete: " << (float)(et - st) / 1000 << " seconds" << endl;
		cout << endl;
	}

	ofResult << dataInput.getTimeStart().tm_hour << dataInput.getTimeStart().tm_min << dataInput.getTimeStart().tm_mday << " - ";
	ofResult << dataInput.getTimeEnd().tm_hour << dataInput.getTimeEnd().tm_min << dataInput.getTimeEnd().tm_mday << endl;
	ofResult << "HTTP Status Code: " << dataInput.getHttpStatusCode() << endl;
	ofResult << "HTTP Request Method: " << dataInput.getHttpRequestMethod() << endl << endl;

	st = clock();

	for (iterApiCounter = listApiCounter.begin(); iterApiCounter != listApiCounter.end(); iterApiCounter++) {
		ofResult << iterApiCounter->first << ": " << iterApiCounter->second << endl;
	}
	
	et = clock();
	cout << endl;
	cout << "[system] File output complete: " << (float)(et - st) / 1000 << " seconds" << endl;
	cout << endl;

	ofResult.close();
}

void LogFilter::countHttpStatusCode(const DataInput &dataInput) {
	ofstream ofResult(getOutFilePath(dataInput.getDate(), 3, 0));
	clock_t st, et;
	list<pair<int, int>> arrlistHourlyStatus[24]; // Ƚ��, �ڵ�
	list<pair<int, int>>::iterator iterHourlyStatus;
	tm tmTime;
	int nHour, nHttpStatusCode;
	bool isInserted = false;

	for (int iFile = 0; iFile < m_dataConfig.getNumberOfLogFile(); iFile++) {
		st = clock();

		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1));
		while (!dataLog.nextRecord().empty()) {
			nHour = dataLog.getHour();
			isInserted = false;
			nHttpStatusCode = dataLog.getHttpStatusCode();
			for (iterHourlyStatus = arrlistHourlyStatus[nHour].begin(); iterHourlyStatus != arrlistHourlyStatus[nHour].end(); iterHourlyStatus++) {
				if (iterHourlyStatus->first == nHttpStatusCode) {
					iterHourlyStatus->second++;
					isInserted = true;
					break;
				}
			}
			if (!isInserted) {
				arrlistHourlyStatus[nHour].push_back(pair<int, int>(nHttpStatusCode, 1));
			}
		}

		et = clock();
		cout << endl;
		cout << "[system] File " << iFile + 1 << " complete: " << (float)(et - st) / 1000 << " seconds" << endl;
		cout << endl;
	}

	st = clock();
	
	for (int i = 0; i < 24; i++) {
		arrlistHourlyStatus[i].sort();
		ofResult << i << " o'clock" << endl;
		for (iterHourlyStatus = arrlistHourlyStatus[i].begin(); iterHourlyStatus != arrlistHourlyStatus[i].end(); iterHourlyStatus++) {
			ofResult << "    " << iterHourlyStatus->first << ": " << iterHourlyStatus->second << endl;
		}
		ofResult << endl;
	}
	
	et = clock();
	cout << endl;
	cout << "[system] File output complete: " << (float)(et - st) / 1000 << " seconds" << endl;
	cout << endl;

	ofResult.close();
}

const string LogFilter::getInFilePath(const tm &tmDate, const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", m_dataConfig.getPathLogFileDir().c_str(), tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iFile, "daouoffice.com_access", tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday); // �Է����� �̸� ����
	return string(strFilePath);
}

const string LogFilter::getOutFilePath(const tm &tmDate, const int &iProc, const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d_proc%d.txt", m_dataConfig.getPathLogFileDir().c_str(), tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iFile, "daouoffice.com_access", tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday, iProc);
	return string(strFilePath);
}