#include "DataLog.h"
#include <iostream>
#include <stack>

DataLog::DataLog(const DataConfig &dataConfig, const DataInput &dataInput, const int &iFile) : m_dataConfig(dataConfig), m_dataInput(dataInput) {
	m_ifLog.open(getInFilePath(iFile));
	if (m_ifLog.fail()) {
		cout << "log파일 열기 실패" << endl;
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

const string DataLog::getInFilePath(const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", m_dataConfig.getPathLogFileDir().c_str(), m_dataInput.getYear(), m_dataInput.getMonth(), m_dataInput.getDay(), iFile, "daouoffice.com_access", m_dataInput.getYear(), m_dataInput.getMonth(), m_dataInput.getDay()); // 입력파일 이름 지정
	return string(strFilePath);
}