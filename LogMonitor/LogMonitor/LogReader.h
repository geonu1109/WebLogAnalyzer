#ifndef __LOGREADER_H__
#define __LOGREADER_H__

#include "LogData.h"
#include <fstream>
#include <string>
using namespace std;

class LogReader
{
private:
	ifstream m_ifLogFile;
	LogData m_dataLog;

public:
	LogReader(void);
	~LogReader(void);
	void read(const string &strLogFilePath);
	const bool next();
	const string &getLogRecord(void) const;
	const string &getLogField(int iLogField) const;
};

#endif