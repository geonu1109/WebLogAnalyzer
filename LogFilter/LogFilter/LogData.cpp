#include "LogData.h"
#include "ArgumentData.h"
#include "ConfigData.h"
#include <stack>

LogData::LogData(void) {
	m_vecLogField.reserve(ConfigData::getInstance().getNumberOfLogField());
}

LogData::~LogData() {
}

void LogData::update(const string &strLogRecord) {
	m_strLogRecord = strLogRecord;
	m_vecLogField.clear();
	splitLog(strLogRecord);
}

const string &LogData::getLogRecord(void) const {
	return m_strLogRecord;
}

const string &LogData::getLogField(const int &iField) const {
	return m_vecLogField[iField];
}

const bool LogData::isValid(void) const {
	if (m_vecLogField.size() != ConfigData::getInstance().getNumberOfLogField()) {
		return false;
	}
	return true;
}

const bool LogData::isConditional(void) const {
	if (stof(m_vecLogField[ConfigData::getInstance().getIndexOfResponseTimeField() - 1]) >= ArgumentData::getInstance().getDelayTimeLimit()) {
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

const bool LogData::isStaticResource(void) const {
	if (m_vecLogField[ConfigData::getInstance().getIndexOfApiField() - 1].find("/resource") != string::npos || m_vecLogField[ConfigData::getInstance().getIndexOfApiField() - 1].find("/favicon") != string::npos) {
		return true;
	}
	return false;
}

const string LogData::getApi(void) const {
	const string &strApiField = m_vecLogField[ConfigData::getInstance().getIndexOfApiField() - 1];
	int iApiChar = strApiField.find('?');
	string strApi;

	if (iApiChar != string::npos) {
		strApi = strApiField.substr(0, iApiChar);
	}
	else {
		strApi = strApiField;
	}

	iApiChar = strApi.find('/', 1);
	iApiChar = strApi.find('/', iApiChar + 1);
	iApiChar = strApi.find('/', iApiChar + 1);

	if (iApiChar != string::npos) {
		return strApi.substr(0, iApiChar);
	}
	else {
		return strApi;
	}
}

const string LogData::getBrowser(void) const {
	const string &strAgent = m_vecLogField[ConfigData::getInstance().getIndexOfClientAgentField() - 1];

	if (strAgent.find("compatible") != string::npos || strAgent.find("Windows") != string::npos) {
		return string("\"Internet Explorer\"");
	}
	else if (strAgent.find("Safari") != string::npos) {
		if (strAgent.find("Chrome") != string::npos) {
			if (strAgent.find("Edge") != string::npos) {
				return string("Edge");
			}
			else if (strAgent.find("OPR") != string::npos) {
				return string("Opera");
			}
			else if (strAgent.find("Whale") != string::npos) {
				return string("Whale");
			}
			else return string("Chrome");
		}
		else if (strAgent.find("Android") != string::npos) {
			return string("Android Browser");
		}
		else if (strAgent.find("Version") != string::npos) {
			return string("Safari");
		}
		else {
			return string("?");
		}
	}
	else if (strAgent.find("Firefox")) return string("Firefox");
	else return string("?");
}

const string LogData::getOS(void) const {
	const string &strAgent = m_vecLogField[ConfigData::getInstance().getIndexOfClientAgentField() - 1];

	if (strAgent.find("Windows") != string::npos) return string("Windows");
	else if (strAgent.find("Linux") != string::npos) {
		if (strAgent.find("Android") != string::npos) return string("Android");
		else return string("Linux");
	}
	else if (strAgent.find("iPhone") != string::npos || strAgent.find("iPad") != string::npos) return string("iOS");
	else if (strAgent.find("Macintosh") != string::npos) return string("macOS");
	else return string("?");
}

const int LogData::getHour(void) const {
	return stoi(m_vecLogField[ConfigData::getInstance().getIndexOfDateTimeField() - 1].substr(13, 2));
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
			m_vecLogField.push_back(strLogRecord.substr(iLogFieldCharStart, nLogRecordLen - iLogFieldCharStart));
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