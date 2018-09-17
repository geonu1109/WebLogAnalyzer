#ifndef __LogData_h__
#define __LogData_h__

#include <string>
#include <vector>
#include <ctime>
using namespace std;

class LogData {
private:
	string m_strLogRecord;
	vector<string> m_vecLogField;

public:
	LogData(void);
	~LogData(void);
	virtual void update(const string &strLogRecord);
	virtual const string &getLogRecord(void) const;
	const string &getLogField(const int &iField) const;
	const bool isValid(void) const;
	const bool isConditional(void) const;
	const bool isStaticResource(void) const;
	const string getApi(void) const;
	const string getBrowser(void) const;
	const string getOS(void) const;
	const int getHour(void) const;

private:
	void splitLog(const string &strLogRecord);
};

#endif