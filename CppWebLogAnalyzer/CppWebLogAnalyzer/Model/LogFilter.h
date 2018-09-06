#ifndef __LOGFILTER_H__
#define __LOGFILTER_H__

#include "../Data/DataConfig.h"
#include "../Data/DataInput.h"
#include "../Data/DataLog.h"
#include "../FilePathGenerator.h"

class LogFilter
{
public:
	LogFilter(void);
	~LogFilter(void);
	void filterDelayedApi(void);
	void sortDynamicApi(void);
	void countHttpStatusCode(void);
	void classifyClientAgent(void);
};

#endif