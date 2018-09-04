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

const string &DataConfig::getPathLogFileDir(void) const {
	return PathLogFileDir;
}

const int &DataConfig::getNumberOfLogFile(void) const {
	return NumberOfLogFile;
}

const int &DataConfig::getNumberOfField(void) const {
	return NumberOfField;
}

const int &DataConfig::getIndexResponseTime(void) const {
	return IndexResponseTime;
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
		else if (strToken == "IndexHttpStatus") {
			ssBuffer >> strToken;
			IndexHttpStatus = stoi(strToken);
		} // HTTP ���� �ڵ� �ʵ��� ��ġ
	}
}