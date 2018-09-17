#ifndef __SimpleLogData_h__
#define __SimpleLogData_h__

#include "LogData.h"
#include <string>
using namespace std;

class SimpleLogData : public LogData {
private:
	string m_strSimpleLogRecord;

public:
	SimpleLogData(void);
	virtual const string &getLogRecord(void) const;
	virtual void update(const string &strLogRecord);

private:
	void setSimpleLogRecord(void);
};

#endif