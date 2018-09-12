#ifndef __LogData_h__
#define __LogData_h__

#include "ConfigData.h"
#include <string>
using namespace std;

class LogData {
private:
	string m_strLogRecord;
	string *m_arrstrLogField;

public:
	LogData(void);
	~LogData(void);
	void update(const string &strLogRecord);
	const string &getLogRecord(void) const;
	const string &getLogField(int &iField) const;

private:
	void splitLog(void) const;
};

#endif