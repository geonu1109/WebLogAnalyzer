#include "LogFilter.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <list>
#include <utility>

const bool desc(pair<string, int> &first, pair<string, int> &second) {
	if (first.second > second.second) return true;
	else return false;
}

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
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1)); // 로그 파일 자료 관리 객체 생성
		ofResult.open(getOutFilePath(dataInput.getDate(), 1, iFile + 1)); // 결과 파일 열기
		if (!ofResult.is_open()) // 파일이 제대로 열렸나 검사
		{
			cout << endl;
			cout << "[method] void LogFilter::filterDelayedApi(const DataInput &dataInput)" << endl;
			cout << "[fatal error] fail to open result file" << endl;
			cout << "[file path] " << getOutFilePath(dataInput.getDate(), 1, iFile + 1) << endl;
			cout << endl;
			system("pause");
			exit(0);
		}
		while (!dataLog.nextRecord().empty()) // 로그 파일에서 레코드 한줄 씩 가져오기
		{
			if (!dataLog.isValidTime(dataInput.getTimeEnd())) break; // 읽어온 로그의 기록 시간이 끝 시간을 넘으면 해당 파일에서 레코드 읽어오기 종료
			else if (dataLog.isValidTime(dataInput.getTimeStart(), dataInput.getTimeEnd())) {
				if (dataLog.getResponseTime() >= dataInput.getDelayLimit()) {
					ofResult << dataLog.getRecord() << endl;
				}
			}
		}
		ofResult.close(); // 결과 파일 닫기
		et = clock();
		cout << endl;
		cout << "[system] File " << iFile + 1 << " end: " << (float)(et - st) / 1000 << " seconds" << endl;
		cout << endl;
	}
}

void LogFilter::sortDynamicApi(const int &iProc, const DataInput &dataInput) {
	ofstream ofResult(getOutFilePath(dataInput.getDate(), iProc, 0));
	list<pair<string, int>> listApiCounter;
	list<pair<string, int>>::iterator iterApiCounter;
	string strApi;
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

	// 입력

	for (int iFile = 0; iFile < m_dataConfig.getNumberOfLogFile(); iFile++) // 파일 조회
	{
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile + 1));

		st = clock();

		while (!dataLog.nextRecord().empty()) // 파일 내 레코드 조회
		{
			if (!dataLog.isValidTime(dataInput.getTimeEnd())) break; // 읽어온 로그의 기록 시간이 끝 시간을 넘으면 해당 파일에서 레코드 읽어오기 종료
			else if (!dataLog.isStaticResource() && dataLog.isValidTime(dataInput.getTimeStart(), dataInput.getTimeEnd())) {
				if (iProc == 4 || (dataLog.getHttpRequestMethod() == dataInput.getHttpRequestMethod() && dataLog.getHttpStatusCode() == dataInput.getHttpStatusCode())) {
					isInserted = false;
					strApi = dataLog.getApiGroup();
					for (iterApiCounter = listApiCounter.begin(); iterApiCounter != listApiCounter.end(); iterApiCounter++) // 리스트 조회
					{
						if (iterApiCounter->first == strApi) {
							iterApiCounter->second++;
							isInserted = true;
							break;
						}
					}
					if (!isInserted) {
						listApiCounter.push_back(pair<string, int>(strApi, 1));
					}
				}
			}
		}

		et = clock();
		cout << endl;
		cout << "[system] File " << iFile + 1 << " complete: " << (float)(et - st) / 1000 << " seconds" << endl;
		cout << endl;
	}

	// 출력

	st = clock();

	listApiCounter.sort(desc);

	ofResult << dataInput.getTimeStart().tm_hour << ":" << dataInput.getTimeStart().tm_min << ":" << dataInput.getTimeStart().tm_sec << " - ";
	ofResult << dataInput.getTimeEnd().tm_hour << ":" << dataInput.getTimeEnd().tm_min << ":" << dataInput.getTimeEnd().tm_sec << endl;
	if (iProc == 2) {
		ofResult << "HTTP Status Code: " << dataInput.getHttpStatusCode() << endl;
		ofResult << "HTTP Request Method: " << dataInput.getHttpRequestMethod() << endl;
	}
	ofResult << endl;

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
	list<pair<int, int>> arrlistHourlyStatus[24]; // 횟수, 코드
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
			ofResult << "    " << iterHourlyStatus->first << ": " << iterHourlyStatus->second << " times" << endl;
		}
		ofResult << endl;
	}

	et = clock();
	cout << endl;
	cout << "[system] File output complete: " << (float)(et - st) / 1000 << " seconds" << endl;
	cout << endl;

	ofResult.close();
}

void LogFilter::classifyClientAgent(const DataInput &dataInput) {
	list<pair<pair<string, string>, int>> arrlistClientAgent[24];
	list<pair<pair<string, string>, int>>::iterator iterClientAgent;
	bool isInserted = false;
	int nHour;
	ofstream ofResult;

	clock_t st, et;

	// input

	for (int iFile = 1; iFile < m_dataConfig.getNumberOfLogFile() + 1; iFile++) {
		DataLog dataLog(m_dataConfig, getInFilePath(dataInput.getDate(), iFile));
		pair<string, string> strClientAgent;
		
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
					iterClientAgent->second++;
					isInserted = true;
				}
			}
			if (!isInserted) {
				arrlistClientAgent[nHour].push_back(pair<pair<string, string>, int>(strClientAgent, 1));
			}
		}

		et = clock();
		cout << "[system] File " << iFile << " process complete: " << (float)(et - st) / 1000 << " seconds" << endl;
	}

	// output

	ofResult.open(getOutFilePath(dataInput.getDate(), 5, 0));

	st = clock();

	for (int i = 0; i < 24; i++) {
		arrlistClientAgent[i].sort();
		ofResult << "[" << i << " o'clock]" << endl;
		for (iterClientAgent = arrlistClientAgent[i].begin(); iterClientAgent != arrlistClientAgent[i].end(); iterClientAgent++) {
			ofResult << "  (" << iterClientAgent->first.first << ", " << iterClientAgent->first.second << ") " << iterClientAgent->second << " times" << endl;
		}
		ofResult << endl;
	}

	et = clock();
	cout << "[system] File output complete: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
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