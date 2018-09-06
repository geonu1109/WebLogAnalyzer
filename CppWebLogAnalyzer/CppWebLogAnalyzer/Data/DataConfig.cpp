#include "DataConfig.h"
#include <iostream>
#include <fstream>
#include <sstream>

DataConfig::DataConfig(void) {
	string strFilePath = "..\\CppWebLogAnalyzer\\wlacfg.txt";
	load(strFilePath);
}

DataConfig::~DataConfig() {
}

const string DataConfig::getPathLogFileDir(void) const {
	return PathLogFileDir;
}

const int DataConfig::getNumberOfLogFile(void) const {
	return NumberOfLogFile;
}

const int DataConfig::getNumberOfField(void) const {
	return NumberOfField;
}

const int DataConfig::getIndexResponseTime(void) const {
	return IndexResponseTime;
}

const int DataConfig::getIndexDateTime(void) const {
	return IndexDateTime;
}

const int DataConfig::getIndexHttpStatusCode(void) const {
	return IndexHttpStatusCode;
}

const int DataConfig::getIndexApi(void) const {
	return IndexApi;
}

const int DataConfig::getIndexHttpRequestMethod(void) const {
	return IndexHttpRequestMethod;
}

const int DataConfig::getIndexClientAgent(void) const {
	return IndexClientAgent;
}

void DataConfig::load(const string &strFilePath) {
	ifstream ifConfig(strFilePath);
	string strBuffer, strToken;
	stringstream ssBuffer;
	
	if (!ifConfig.is_open()) {
		cout << "config���� ���� ����" << endl;
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