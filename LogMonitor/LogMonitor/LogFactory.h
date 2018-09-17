#ifndef __LogFactory_h__
#define __LogFactory_h__

#include "LogData.h"

class LogFactory {
private:
	static LogFactory *pInstance;

public:
	static const LogFactory &getInstance(void);
	LogData *create(void) const;

private:
	LogFactory();
};

#endif