#include "LogData.h"
#include <stack>
#include <ctime>
#include <iostream>

LogData::LogData(void) {
	m_vecLogField.reserve(ConfigData::getInstance().getNumberOfLogField());
}

LogData::~LogData() {
}

void LogData::update(const string &strLogRecord) {
	m_vecLogField.clear();
	splitLog(strLogRecord);
}

const string LogData::getLogRecord(void) const {
	if (!isValid()) return string();
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
	if (m_vecLogField.size() != ConfigData::getInstance().getNumberOfLogField()) return false;
	return true;
}

void LogData::setDateTime(void) {
	if (!isValid()) return;
	time_t secNow;
	tm tmNow;
	char strBuffer[128];
	string mon;

	secNow = time(nullptr);
	localtime_s(&tmNow, &secNow);

	switch (tmNow.tm_mon) {
	case 0:
		mon = "Jan";
		break;
	case 1:
		mon = "Feb";
		break;
	case 2:
		mon = "Mar";
		break;
	case 3:
		mon = "Apr";
		break;
	case 4:
		mon = "May";
		break;
	case 5:
		mon = "Jun";
		break;
	case 6:
		mon = "Jul";
		break;
	case 7:
		mon = "Aug";
		break;
	case 8:
		mon = "Sep";
		break;
	case 9:
		mon = "Oct";
		break;
	case 10:
		mon = "Nov";
		break;
	case 11:
		mon = "Dec";
		break;
	default:
		throw string("wrong month");
	}

	sprintf_s(strBuffer, 128, "[%02d/%s/%04d:%02d:%02d:%02d +09:00]", tmNow.tm_mday, mon.c_str(), tmNow.tm_year + 1900, tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
	m_vecLogField[ConfigData::getInstance().getIndexOfDateTimeField() - 1] = strBuffer;
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
				throw string("fail to split log");
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