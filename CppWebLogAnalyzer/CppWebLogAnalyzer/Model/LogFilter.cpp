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

LogFilter::LogFilter(void) {
}

LogFilter::~LogFilter()
{
}

void LogFilter::filterDelayedApi(void) {
	ofstream ofResult;
	clock_t st, et;
	int iFileLimit = DataConfig::getInstance().getNumberOfLogFile();

	st = clock();

	for (int iFile = 1; iFile < iFileLimit + 1; iFile++) {
		clock_t st, et;

		st = clock();

		DataLog dataLog(FilePathGenerator::getInFilePath(iFile)); // 로그 파일 자료 관리 객체 생성
		ofResult.open(FilePathGenerator::getOutFilePath(iFile)); // 결과 파일 열기

		while (!dataLog.nextRecord().empty()) // 로그 파일에서 레코드 한줄 씩 가져오기
		{
			if (!dataLog.isValidTime(DataInput::getInstance().getTimeEnd())) break; // 읽어온 로그의 기록 시간이 끝 시간을 넘으면 해당 파일에서 레코드 읽어오기 종료
			else if (dataLog.isValidTime(DataInput::getInstance().getTimeStart(), DataInput::getInstance().getTimeEnd())) {
				if (dataLog.getResponseTime() >= DataInput::getInstance().getDelayLimit()) {
					ofResult << dataLog.getRecord() << endl;
				}
			}
		}
		et = clock();
		cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;

		ofResult.close(); // 결과 파일 닫기
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;
}

void LogFilter::sortDynamicApi(void) {
	ofstream ofResult(FilePathGenerator::getOutFilePath(0));
	list<pair<string, int>> listApiCounter;
	list<pair<string, int>>::iterator iterApiCounter;
	string strApi;
	bool isInserted = false;
	clock_t st, et;

	// 입력

	st = clock();

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) // 파일 조회
	{
		DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
		clock_t st, et;

		st = clock();

		while (!dataLog.nextRecord().empty()) // 파일 내 레코드 조회
		{
			if (!dataLog.isValidTime(DataInput::getInstance().getTimeEnd())) break; // 읽어온 로그의 기록 시간이 끝 시간을 넘으면 해당 파일에서 레코드 읽어오기 종료
			else if (!dataLog.isStaticResource() && dataLog.isValidTime(DataInput::getInstance().getTimeStart(), DataInput::getInstance().getTimeEnd())) {
				if (DataInput::getInstance().getSelect() == 4 || (dataLog.getHttpRequestMethod() == DataInput::getInstance().getHttpRequestMethod() && dataLog.getHttpStatusCode() == DataInput::getInstance().getHttpStatusCode())) {
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
		cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;

	// 출력

	st = clock();

	listApiCounter.sort(desc);

	ofResult << DataInput::getInstance().getTimeStart().tm_hour << ":" << DataInput::getInstance().getTimeStart().tm_min << ":" << DataInput::getInstance().getTimeStart().tm_sec << " - ";
	ofResult << DataInput::getInstance().getTimeEnd().tm_hour << ":" << DataInput::getInstance().getTimeEnd().tm_min << ":" << DataInput::getInstance().getTimeEnd().tm_sec << endl;
	if (DataInput::getInstance().getSelect() == 2) {
		ofResult << "HTTP Status Code: " << DataInput::getInstance().getHttpStatusCode() << endl;
		ofResult << "HTTP Request Method: " << DataInput::getInstance().getHttpRequestMethod() << endl;
	}
	ofResult << endl;

	for (iterApiCounter = listApiCounter.begin(); iterApiCounter != listApiCounter.end(); iterApiCounter++) {
		ofResult << "[" << iterApiCounter->first << "] " << iterApiCounter->second << " times" << endl;
	}

	et = clock();
	cout << "[system] File output completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
}

void LogFilter::countHttpStatusCode(void) {
	ofstream ofResult(FilePathGenerator::getOutFilePath(0));
	clock_t st, et;
	list<pair<int, int>> arrlistHourlyStatus[24]; // 횟수, 코드
	list<pair<int, int>>::iterator iterHourlyStatus;

	int nHour, nHttpStatusCode;
	bool isInserted = false;

	st = clock();

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) {
		clock_t st, et;

		st = clock();

		DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
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
		cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
	}

	et = clock();
	cout << "[system] Total processing time: " << (float)(et - st) / 1000 << " seconds" << endl;

	st = clock();

	for (int i = 0; i < 24; i++) {
		arrlistHourlyStatus[i].sort();
		ofResult << i << " o'clock" << endl;
		for (iterHourlyStatus = arrlistHourlyStatus[i].begin(); iterHourlyStatus != arrlistHourlyStatus[i].end(); iterHourlyStatus++) {
			ofResult << "  [" << iterHourlyStatus->first << "] " << iterHourlyStatus->second << " times" << endl;
		}
		ofResult << endl;
	}

	et = clock();
	cout << "[system] File output completed: " << (float)(et - st) / 1000 << " seconds" << endl;

	ofResult.close();
}

void LogFilter::classifyClientAgent(void) {
	list<pair<pair<string, string>, int>> arrlistClientAgent[24];
	list<pair<pair<string, string>, int>>::iterator iterClientAgent;
	bool isInserted = false;
	int nHour;
	ofstream ofResult;

	clock_t st, et;
	st = clock();

	// input

	for (int iFile = 1; iFile < DataConfig::getInstance().getNumberOfLogFile() + 1; iFile++) {
		DataLog dataLog(FilePathGenerator::getInFilePath(iFile));
		pair<string, string> strClientAgent;

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
					iterClientAgent->second++;
					isInserted = true;
				}
			}
			if (!isInserted) {
				arrlistClientAgent[nHour].push_back(pair<pair<string, string>, int>(strClientAgent, 1));
			}
		}

		et = clock();
		cout << "[system] File " << iFile << " process completed: " << (float)(et - st) / 1000 << " seconds" << endl;
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