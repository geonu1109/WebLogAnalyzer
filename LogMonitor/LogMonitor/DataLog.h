#ifndef __LOGDATA_H__
#define __LOGDATA_H__

#include "DataConfig.h"
#include <string>
using namespace std;

class DataLog
{
private:
	string m_strLogRecord;
	string *m_arrstrLogField;

public:
	DataLog(void);
	~DataLog(void);
	void update(const string &strLogRecord);
	const string &getLogRecord(void) const;
	const string &getLogField(int &iField) const;

private:
	void splitLog(void) const;
};

#endif