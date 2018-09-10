#ifndef __DATALOGFIELD_H__
#define __DATALOGFIELD_H__

#include "DataLog.h"

class DataLogField : DataLog
{
private:
	string *m_arrLogField;

public:
	DataLogField();
	~DataLogField();
	virtual void update(const string &strLogRecord) override;
};

#endif