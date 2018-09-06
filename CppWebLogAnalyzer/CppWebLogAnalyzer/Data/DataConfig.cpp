#include "DataConfig.h"
#include <iostream>
#include <fstream>
#include <sstream>

DataConfig DataConfig::instance;

DataConfig::DataConfig(void) : ConfigFilePath("..\\CppWebLogAnalyzer\\wlacfg.txt") {
	load();
}

DataConfig::~DataConfig() {
}

const string DataConfig::getPathLogFileDir(void) {
	return PathLogFileDir;
}

const int DataConfig::getNumberOfLogFile(void) {
	return NumberOfLogFile;
}

const int DataConfig::getNumberOfField(void) {
	return NumberOfField;
}

const int DataConfig::getIndexResponseTime(void) {
	return IndexResponseTime;
}

const int DataConfig::getIndexDateTime(void) {
	return IndexDateTime;
}

const int DataConfig::getIndexHttpStatusCode(void) {
	return IndexHttpStatusCode;
}

const int DataConfig::getIndexApi(void) {
	return IndexApi;
}

const int DataConfig::getIndexHttpRequestMethod(void) {
	return IndexHttpRequestMethod;
}

const int DataConfig::getIndexClientAgent(void) {
	return IndexClientAgent;
}

void DataConfig::load(void) {
	ifstream ifConfig(ConfigFilePath);
	string strBuffer, strToken;
	stringstream ssBuffer;
	
	if (ifConfig.fail()) {
		cout << "config파일 열기 실패" << endl;
	}
	while (getline(ifConfig, strBuffer)) {
		ssBuffer.clear();
		ssBuffer.str(strBuffer);
		ssBuffer >> strToken;
		if (strToken.at(0) == '#') { continue; } // #으로 시작하는 줄은 주석처리
		else if (strToken == "PathLogFileDir") {
			ssBuffer >> strToken;
			PathLogFileDir = strToken;
		} // 로그파일이 들어있는 디렉터리의 경로
		else if (strToken == "NumberOfLogFile") {
			ssBuffer >> strToken;
			NumberOfLogFile = stoi(strToken);
		} // 로그파일의 개수
		else if (strToken == "NumberOfField") {
			ssBuffer >> strToken;
			NumberOfField = stoi(strToken);
		} // 레코드 당 필드의 개수
		else if (strToken == "IndexResponseTime") {
			ssBuffer >> strToken;
			IndexResponseTime = stoi(strToken);
		} // 응답시간 필드의 위치
		else if (strToken == "IndexDateTime") {
			ssBuffer >> strToken;
			IndexDateTime = stoi(strToken);
		} // 날짜 및 시간 필드의 위치
		else if (strToken == "IndexHttpStatusCode") {
			ssBuffer >> strToken;
			IndexHttpStatusCode = stoi(strToken);
		} // HTTP 상태 코드 필드의 위치
		else if (strToken == "IndexApi") {
			ssBuffer >> strToken;
			IndexApi = stoi(strToken);
		} // Api 필드의 위치
		else if (strToken == "IndexHttpRequestMethod") {
			ssBuffer >> strToken;
			IndexHttpRequestMethod = stoi(strToken);
		} // HTTP 요청 방식 필드의 위치
		else if (strToken == "IndexClientAgent") {
			ssBuffer >> strToken;
			IndexClientAgent = stoi(strToken);
		} // HTTP 요청 방식 필드의 위치
	}
}

DataConfig &DataConfig::getInstance(void) {
	return instance;
}