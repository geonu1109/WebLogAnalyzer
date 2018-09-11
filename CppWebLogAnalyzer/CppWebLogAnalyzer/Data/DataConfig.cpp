#include "DataConfig.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define CLion
DataConfig DataConfig::instance;

DataConfig::DataConfig(void)
#ifdef CLion
	: ConfigFilePath("../CppWebLogAnalyzer/CppWebLogAnalyzer/wlacfg.txt") {
#else
	: ConfigFilePath("../CppWebLogAnalyzer/wlacfg.txt") {
#endif
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
		cout << "[error] fail to open config file" << endl;
	}
	while (getline(ifConfig, strBuffer)) {
		ssBuffer.clear();
		ssBuffer.str(strBuffer);
		ssBuffer >> strToken;
		if (strToken.at(0) == '#') { continue; } // #���� �����ϴ� ���� �ּ�ó��
		else if (strToken == "PathLogFileDir") {
			ssBuffer >> strToken;
			PathLogFileDir = strToken;
		} // �α������� ����ִ� ���͸��� ���
		else if (strToken == "NumberOfLogFile") {
			ssBuffer >> strToken;
			NumberOfLogFile = stoi(strToken);
		} // �α������� ����
		else if (strToken == "NumberOfField") {
			ssBuffer >> strToken;
			NumberOfField = stoi(strToken);
		} // ���ڵ� �� �ʵ��� ����
		else if (strToken == "IndexResponseTime") {
			ssBuffer >> strToken;
			IndexResponseTime = stoi(strToken);
		} // ����ð� �ʵ��� ��ġ
		else if (strToken == "IndexDateTime") {
			ssBuffer >> strToken;
			IndexDateTime = stoi(strToken);
		} // ��¥ �� �ð� �ʵ��� ��ġ
		else if (strToken == "IndexHttpStatusCode") {
			ssBuffer >> strToken;
			IndexHttpStatusCode = stoi(strToken);
		} // HTTP ���� �ڵ� �ʵ��� ��ġ
		else if (strToken == "IndexApi") {
			ssBuffer >> strToken;
			IndexApi = stoi(strToken);
		} // Api �ʵ��� ��ġ
		else if (strToken == "IndexHttpRequestMethod") {
			ssBuffer >> strToken;
			IndexHttpRequestMethod = stoi(strToken);
		} // HTTP ��û ��� �ʵ��� ��ġ
		else if (strToken == "IndexClientAgent") {
			ssBuffer >> strToken;
			IndexClientAgent = stoi(strToken);
		} // HTTP ��û ��� �ʵ��� ��ġ
	}
}

DataConfig &DataConfig::getInstance(void) {
	return instance;
}