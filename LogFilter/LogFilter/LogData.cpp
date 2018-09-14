#include "LogData.h"
#include "ConfigData.h"
#include "ArgumentData.h"
#include <stack>

LogData::LogData(void) {
	m_vecLogField.reserve(ConfigData::getInstance().getNumberOfLogField());
}

LogData::~LogData() {
}

void LogData::update(const string &strLogRecord) {
	m_vecLogField.clear();
	splitLog(strLogRecord);
}

const string &LogData::getLogRecord(void) const {
	string strBuffer;

	for (auto i : m_vecLogField) {
		strBuffer += i + ' ';
	}

	return strBuffer.substr(0, strBuffer.length() - 1);
}

const string &LogData::getLogField(int &iField) const {
	return m_vecLogField[iField];
}

bool LogData::isValid(void) const {
	if (m_vecLogField.size() != ConfigData::getInstance().getNumberOfLogField()) {
		return false;
	}
	else if (stof(m_vecLogField[ConfigData::getInstance().getIndexOfResponseTimeField() - 1]) >= ArgumentData::getInstance().getDelayTimeLimit()) {
		if (ArgumentData::getInstance().getHttpStatusCode().empty()) {
			return true;
		}
		for (auto i : ArgumentData::getInstance().getHttpStatusCode()) {
			if (i == stoi(m_vecLogField[ConfigData::getInstance().getIndexOfHttpStatusCodeField() - 1])) {
				return true;
			}
		}
	}
	return false;
}

void LogData::splitLog(const string &strLogRecord) {
	const int nLogRecordLen = strLogRecord.length();
	int iLogFieldCharStart = 0;
	stack<char> stkBlacket;

	for (int iLogRecordChar = 0; iLogRecordChar < nLogRecordLen; iLogRecordChar++) {
		// handle exception
		if (m_vecLogField.size() > ConfigData::getInstance().getNumberOfLogField()) {
			throw string("indicated invalid log field");
		}
		if (iLogRecordChar == nLogRecordLen - 1) {
			if (m_vecLogField.size() != ConfigData::getInstance().getNumberOfLogField() - 1) {
				// throw string("fail to split log");
			}
			m_vecLogField.push_back(strLogRecord.substr(iLogFieldCharStart, iLogRecordChar - iLogFieldCharStart));
			break;
		}

		// parse
		switch (strLogRecord[iLogRecordChar]) {
		case ' ':
			if (stkBlacket.empty()) {
				m_vecLogField.push_back(strLogRecord.substr(iLogFieldCharStart, iLogRecordChar - iLogFieldCharStart));
				iLogFieldCharStart = iLogRecordChar + 1;
			}
			else {} // ignore whitespaces if the stack isn't empty
			break;
		case '\"':
			if (strLogRecord[iLogRecordChar - 1] == ' ') {
				stkBlacket.push('\"');
			}
			else if (iLogRecordChar == nLogRecordLen - 1 || strLogRecord[iLogRecordChar + 1] == ' ') {
				if (stkBlacket.empty()) {
					throw string("stack underflowed");
				}
				else if (stkBlacket.top() == '\"') {
					stkBlacket.pop();
				}
			}
			else {} // ignore double quotes, if not start or end
			break;
		case '[':
			stkBlacket.push('[');
			break;
		case ']':
			if (stkBlacket.empty()) {
				throw string("stack underflowed");
			}
			else if (stkBlacket.top() == '[') {
				stkBlacket.pop();
			}
			break;
		default:
			break;
		}
	}
}