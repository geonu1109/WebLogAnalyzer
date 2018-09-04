#ifndef __LOGFILTER_H__
#define __LOGFILTER_H__

#include "../Data/DataConfig.h"
#include "../Data/DataInput.h"
#include "../Data/DataLog.h"

class LogFilter
{
private:
	const DataConfig &m_dataConfig;

public:
	LogFilter(const DataConfig &dataConfig);
	~LogFilter();
	void filterDelayedApi(const DataInput &dataInput);
	
private:
	string getOutFilePath(const DataInput &dataInput, const int &iProc, const int &iFile);
};

#endif