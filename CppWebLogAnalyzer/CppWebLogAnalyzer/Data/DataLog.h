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
	const DataConfig &m_dataConfig; // 설정파일에서 받아온 정보

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