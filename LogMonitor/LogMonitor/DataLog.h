#ifndef __LOGDATA_H__
#define __LOGDATA_H__
#include <string>
using namespace std;

class DataLog
{
public:
	DataLog();
	~DataLog();
	virtual void update(const string &strLogRecord) = 0;
};

#endif