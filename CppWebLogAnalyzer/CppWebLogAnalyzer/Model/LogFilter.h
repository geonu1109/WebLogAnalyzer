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
	void sortDynamicApi(const int &iProc, const DataInput &dataInput);
	void countHttpStatusCode(const DataInput &dataInput);
	void classifyClientAgent(const DataInput &dataInput);

private:
	const string getInFilePath(const tm &tmDate, const int &iFile);
	const string getOutFilePath(const tm &tmDate, const int &iProc, const int &iFile);
};

#endif