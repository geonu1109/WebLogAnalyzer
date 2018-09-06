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
	ifstream m_ifLog; // 입력받을 로그파일
	string m_strRecord; // 현재 로그의 레코드
	string *m_arrField; // 현재 로그의 필드목록

public:
	DataLog(const string &strFilePath);
	~DataLog(void);
	const string nextRecord(void);
	const int getLine(void) const;
	const string getRecord(void) const;
	const float getResponseTime(void) const;
	const bool isValidTime(const tm &tmTimeEnd) const;
	const bool isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const;
	const bool isApi(void) const;
	const bool isStaticResource(void) const;
	const int getHour(void) const;
	const int getHttpStatusCode(void) const;
	const string getHttpRequestMethod(void) const;
	const string getApiField(void) const;
	const string getApiGroup(void) const;
	const string getClientAgentField(void) const;
	const string getBrowser(void) const;
	const string getOS(void) const;

private:
	void setField(void);
	int calTotalTime(const tm &tmTime) const;
};

#endif