#include "LogFactory.h"
#include "ArgumentData.h"
#include "SimpleLogData.h"

LogFactory *LogFactory::pInstance = nullptr;

const LogFactory &LogFactory::getInstance(void) {
	if (pInstance == nullptr) {
		pInstance = new LogFactory();
	}
	return *pInstance;
}

LogData *LogFactory::create(void) const {
	if (ArgumentData::getInstance().isEasyMode()) {
		return new SimpleLogData();
	}
	else {
		return new LogData();
	}
}

LogFactory::LogFactory() {
}