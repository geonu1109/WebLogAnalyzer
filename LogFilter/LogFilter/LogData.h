#ifndef __LogData_h__
#define __LogData_h__

#include "ConfigData.h"
#include <string>
#include <vector>
using namespace std;

class LogData {
private:
	vector<string> m_vecLogField;

public:
	LogData(void);
	~LogData(void);
	void update(const string &strLogRecord);
	const string &getLogRecord(void) const;
	const string &getLogField(int &iField) const;
	bool isValid(void) const;

private:
	void splitLog(const string &strLogRecord);
};

#endif