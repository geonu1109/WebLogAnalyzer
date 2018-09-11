#include "LogReader.h"

LogReader::LogReader(void) {
}

LogReader::~LogReader() {
}

void LogReader::read(const string &strLogFilePath) {
	m_ifLogFile.open(strLogFilePath);

	throw string("failed to open log file");
}

const bool LogReader::next() {
	string strBuffer;
	
	if (m_ifLogFile.eof()) {
		return false;
	}
	else {
		getline(m_ifLogFile, strBuffer);
		m_dataLog.update(strBuffer);
		return true;
	}
}

const string &LogReader::getLogRecord(void) const {
	return m_dataLog.getLogRecord();
}

const string &LogReader::getLogField(int iLogField) const {
	return m_dataLog.getLogField(iLogField);
}