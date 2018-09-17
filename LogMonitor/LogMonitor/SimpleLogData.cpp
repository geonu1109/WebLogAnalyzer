#include "SimpleLogData.h"
#include "ConfigData.h"

SimpleLogData::SimpleLogData() : LogData() {
}

SimpleLogData::~SimpleLogData() {
}

const string &SimpleLogData::getLogRecord(void) const {
	return m_strSimpleLogRecord;
}

void SimpleLogData::update(const string &strLogRecord) {
	LogData::update(strLogRecord);
}

void SimpleLogData::setSimpleLogRecord(void) {
	char szBuffer[256] = { '\0' };
	int len = 0;

	szBuffer[len++] = '[';
	strcpy_s(&szBuffer[len], 3, getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(13, 2).c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ':';
	strcpy_s(&szBuffer[len], 3, getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(16, 2).c_str());
	len = strlen(szBuffer);
	szBuffer[strlen(szBuffer)] = ':';
	strcpy_s(&szBuffer[len], 3, getLogField(ConfigData::getInstance().getIndexOfDateTimeField() - 1).substr(19, 2).c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ']';
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 128, getApi().c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 6, getLogField(ConfigData::getInstance().getIndexOfHttpRequestMethodField() - 1).c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 4, getLogField(ConfigData::getInstance().getIndexOfHttpStatusCodeField() - 1).c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 10, getBrowser().c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 10, getOS().c_str());
	len = strlen(szBuffer);
	szBuffer[len++] = ' ';

	strcpy_s(&szBuffer[len], 10, getLogField(ConfigData::getInstance().getIndexOfResponseTimeField - 1).c_str());
	szBuffer[strlen(szBuffer)] = '\0';

	m_strSimpleLogRecord = string(szBuffer);
}