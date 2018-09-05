#ifndef __DATALOG_H__
#define __DATALOG_H__

#include <string>
#include <fstream>
#include "DataConfig.h"
#include "DataInput.h"
using namespace std;

class DataLog {
private:
	ifstream m_ifLog; // �Է¹��� �α�����
	string m_strRecord; // ���� �α��� ���ڵ�
	string *m_arrField; // ���� �α��� �ʵ���
	const DataConfig &m_dataConfig; // �������Ͽ��� �о�� ����
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