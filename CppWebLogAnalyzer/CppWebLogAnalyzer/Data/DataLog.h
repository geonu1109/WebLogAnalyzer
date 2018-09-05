#ifndef __DATALOG_H__
#define __DATALOG_H__

#include <string>
#include <fstream>
#include "DataConfig.h"
#include "DataInput.h"
using namespace std;

class DataLog {
private:
	ifstream m_ifLog; // 입력받을 로그파일
	string m_strRecord; // 현재 로그의 레코드
	string *m_arrField; // 현재 로그의 필드목록
	const DataConfig &m_dataConfig; // 설정파일에서 읽어온 설정
	const DataInput &m_dataInput;

public:
	DataLog(const DataConfig &dataConfig, const DataInput &dataInput, const int &iFile);
	~DataLog(void);
	const string nextRecord(void);
	const string getRecord(void) const;
	const float getResponseTime(void) const;

private:
	void setField(void);
	const string getInFilePath(const int &iFile);
};

#endif