#include "DataLog.h"
#include <stack>

DataLog::DataLog(void) {
	m_arrstrLogField = new string[DataConfig::getInstance().getLogField()];
}

DataLog::~DataLog() {
	delete[] m_arrstrLogField;
}

void DataLog::update(const string &strLogRecord) {
	m_strLogRecord = strLogRecord;
	
	splitLog();
}

const string &DataLog::getLogRecord(void) const {
	return m_strLogRecord;
}

const string &DataLog::getLogField(int &iField) const {
	return m_arrstrLogField[iField];
}

void DataLog::splitLog(void) const {
	const int nLogRecordLen = m_strLogRecord.length();
	int iLogField = 0, iLogFieldCharStart = 0;
	stack<char> stkChar;

	for (int iLogRecordChar = 0; iLogRecordChar < nLogRecordLen; iLogRecordChar++) {
		// handle exception
		if (iLogField > DataConfig::getInstance().getLogField()) {
			throw string("indicated invalid log field");
		}
		if (iLogRecordChar == nLogRecordLen - 1) {
			if (iLogField != DataConfig::getInstance().getLogField() - 1) {
				throw string("fail to split log");
			}
			m_arrstrLogField[iLogField] = m_strLogRecord.substr(iLogFieldCharStart, iLogRecordChar - iLogFieldCharStart);
			break;
		}

		// parse
		switch (m_strLogRecord.at(iLogRecordChar)) {
		case ' ':
			if (stkChar.empty()) {
				m_arrstrLogField[iLogField++] = m_strLogRecord.substr(iLogFieldCharStart, iLogRecordChar - iLogFieldCharStart);
				iLogFieldCharStart = iLogRecordChar + 1;
			}
			else { } // ignore whitespaces if the stack isn't empty
			break;
		case '\"':
			if (m_strLogRecord.at(iLogRecordChar - 1) == ' ') {
				stkChar.push('\"');
			}
			else if (iLogRecordChar == nLogRecordLen - 1 || m_strLogRecord.at(iLogRecordChar + 1) == ' ') {
				if (stkChar.empty()) {
					throw string("stack underflowed");
				}
				else if (stkChar.top() == '\"') {
					stkChar.pop();
				}
			}
			else { } // ignore double quotes, if not start or end
			break;
		case '[':
			stkChar.push('[');
			break;
		case ']':
			if (stkChar.empty()) {
				throw string("stack underflowed");
			}
			else if (stkChar.top() == '[') {
				stkChar.pop();
			}
			break;
		default:
			break;
		}
	}
}