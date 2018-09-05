#include "DataLog.h"
#include <iostream>
#include <stack>

DataLog::DataLog(const DataConfig &dataConfig, const string &strFilePath) : m_dataConfig(dataConfig), m_ifLog(strFilePath) {
	if (m_ifLog.fail()) {
		cout << endl;
		cout << "[method] DataLog::DataLog(const DataConfig &dataConfig, const string &strFilePath)" << endl;
		cout << "[fatal error] fail to open log file" << endl;
		cout << "[file path] " << strFilePath << endl;
		cout << endl;
		system("pause");
		exit(0);
	}
	m_arrField = new string[m_dataConfig.getNumberOfField()];
}

DataLog::~DataLog(void) {
	delete[] m_arrField;
}

const string DataLog::nextRecord(void) {
	if (!m_ifLog.eof()) {
		getline(m_ifLog, m_strRecord);
		setField();

		return m_strRecord;
	}
	else {
		return string();
	}
}

const string DataLog::getRecord(void) const {
	return m_strRecord;
}

const float DataLog::getResponseTime(void) const {
	return stof(m_arrField[m_dataConfig.getIndexResponseTime() - 1]);
}

const bool DataLog::isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const {
	tm tmTimeCur;
	tmTimeCur.tm_hour = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(13, 2));
	tmTimeCur.tm_min = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(16, 2));
	tmTimeCur.tm_sec = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(19, 2));

	if (getSecond(tmTimeStart) > getSecond(tmTimeEnd)) {
		cout << endl;
		cout << "[method] const bool DataLog::isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const" << endl;
		cout << "[fatal error] invalid time" << endl;
		cout << endl;
		system("pause");
		exit(0);
	}

	if (getSecond(tmTimeStart) <= getSecond(tmTimeCur) && getSecond(tmTimeCur) <= getSecond(tmTimeEnd)) return true;
	else return false;
}

void DataLog::setField(void) {
	stack<char> stkBracket;
	int iField = 0, iFieldStart = 0;
	const int nRecordLength = m_strRecord.length();

	for (int iRecordChar = 0; iRecordChar < nRecordLength; iRecordChar++) {
		if (iField == m_dataConfig.getNumberOfField()) {
			cout << endl;
			cout << "[method] void DataLog::setField(void)" << endl;
			cout << "[fatal error] Field index is overflowed." << endl;
			cout << "[record] " << m_strRecord << endl;
			cout << endl;
			system("pause");
			exit(0);
		}

		if (iRecordChar == nRecordLength - 1) {
			if (!stkBracket.empty()) {
				cout << endl;
				cout << "[method] void DataLog::setField(void)" << endl;
				cout << "[fatal error] Stack is not empty." << endl;
				cout << "[record] " << m_strRecord << endl;
				cout << endl;
				system("pause");
				exit(0);
			}

			else if (iField == m_dataConfig.getNumberOfField() - 1) {
				m_arrField[iField] = m_strRecord.substr(iFieldStart, iRecordChar - iFieldStart + 1);
				break;
			}

			else {
				cout << endl;
				cout << "[method] void DataLog::setField(void)" << endl;
				cout << "[fatal error] Field index does not matched." << endl;
				cout << "[record] " << m_strRecord << endl;
				cout << endl;
				system("pause");
				exit(0);
			}

		}

		switch (m_strRecord.at(iRecordChar)) {
		case ' ':
			if (stkBracket.empty()) {
				m_arrField[iField++] = m_strRecord.substr(iFieldStart, iRecordChar - iFieldStart);
				iFieldStart = iRecordChar + 1;
			}
			break;
		case '[':
			stkBracket.push('[');
			break;
		case ']':
			if (!stkBracket.empty() && stkBracket.top() == '[') { stkBracket.pop(); }
			else {
				cout << endl;
				cout << "[method] void DataLog::setField(void)" << endl;
				cout << "[minor error] [ ] is not matched." << endl;
				cout << "[record] " << m_strRecord << endl;
				cout << endl;
			}
			break;
		case '\"':
			if (m_strRecord.at(iRecordChar - 1) == ' ') {
				stkBracket.push('\"');
			}
			else if (m_strRecord.at(iRecordChar + 1) == ' ') {
				if (!stkBracket.empty() && stkBracket.top() == '\"') { stkBracket.pop(); }
				else {
					cout << endl;
					cout << "[method] void DataLog::setField(void)" << endl;
					cout << "[minor error] \" \" is not matched." << endl;
					cout << "[record] " << m_strRecord << endl;
					cout << endl;
				}
			}
			break;
		default:
			;
		}
	}
}

int DataLog::getSecond(const tm &tmTime) const {
	return tmTime.tm_hour * 3600 + tmTime.tm_min * 60 + tmTime.tm_sec;
}
