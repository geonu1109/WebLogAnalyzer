#ifndef __DATALOG_H__
#define __DATALOG_H__

#include <string>
#include <fstream>
#include <ctime>
#include "DataConfig.h"
#include "DataInput.h"
using namespace std;

class DataLog {
private:
	int m_nLine;
	ifstream m_ifLog; // �Է¹��� �α�����
	string m_strRecord; // ���� �α��� ���ڵ�
	string *m_arrField; // ���� �α��� �ʵ���
	const DataConfig &m_dataConfig; // �������Ͽ��� �޾ƿ� ����

public:
	DataLog(const DataConfig &dataConfig, const string &strFilePath);
	~DataLog(void);
	const string nextRecord(void);
	const int getLine(void) const;
	const string getRecord(void) const;
	const float getResponseTime(void) const;
	const bool isValidTime(const tm &tmTimeEnd) const;
	const bool isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const;
	const bool isApi(void) const;
	const int getHour(void) const;
	const int getHttpStatusCode(void) const;
	const string getHttpRequestMethod(void) const;
	const string getApi(void) const;
	const string getApiGroup(void) const;

private:
	void setField(void);
	int calTotalTime(const tm &tmTime) const;
};

#endif