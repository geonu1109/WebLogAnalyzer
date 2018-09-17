// #define WINDOWS

#include "SimpleLogData.h"
#include "ConfigData.h"
#include <iostream>

SimpleLogData::SimpleLogData(void) : LogData() {
}

const string &SimpleLogData::getLogRecord(void) const {
	return m_strSimpleLogRecord;
}

void SimpleLogData::update(const string &strLogRecord) {
	LogData::update(strLogRecord);
	if (isValid()) {
		setSimpleLogRecord();
	}
}

void SimpleLogData::setSimpleLogRecord(void) {
	char szBuffer[256];

#ifdef WINDOWS
	sprintf_s(szBuffer, 256, "[%2s:%2s:%2s] %-32s %-6s %-3s %-19s %-7s %-5s", getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(13, 2).c_str(), getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(16, 2).c_str(), getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(19, 2).c_str(), getApi().c_str(), getLogField(ConfigData::getInstance().getIndexOfHttpRequestMethodField() - 1).c_str(), getLogField(ConfigData::getInstance().getIndexOfHttpStatusCodeField() - 1).c_str(), getBrowser().c_str(), getOS().c_str(), getLogField(ConfigData::getInstance().getIndexOfResponseTimeField() - 1).c_str());
#else
	sprintf(szBuffer, "[%2s:%2s:%2s] %-32s %-6s %-3s %-19s %-7s %-5s", getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(13, 2).c_str(), getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(16, 2).c_str(), getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(19, 2).c_str(), getApi().c_str(), getLogField(ConfigData::getInstance().getIndexOfHttpRequestMethodField() - 1).c_str(), getLogField(ConfigData::getInstance().getIndexOfHttpStatusCodeField() - 1).c_str(), getBrowser().c_str(), getOS().c_str(), getLogField(ConfigData::getInstance().getIndexOfResponseTimeField() - 1).c_str());
#endif

	m_strSimpleLogRecord = string(szBuffer);
}