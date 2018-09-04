#include "DataLog.h"
#include <iostream>
#include <stack>

DataLog::DataLog(const DataConfig &dataConfig, const DataInput &dataInput, const int &iFile) : m_dataConfig(dataConfig), m_dataInput(dataInput) {
	m_ifLog.open(getInFilePath(iFile));
	if (!m_ifLog.is_open()) {
		cout << "log파일 열기 실패" << endl;
	}
	m_arrField = new string[m_dataConfig.getNumberOfField()];
}

DataLog::~DataLog(void) {
	delete[] m_arrField;
}

const string &DataLog::nextRecord(void) {
	if (!m_ifLog.eof()) {
		getline(m_ifLog, m_strRecord);
		setField();

		return m_strRecord;
	}
	else {
		return string();
	}
}

const string &DataLog::getRecord(void) const {
	return m_strRecord;
}

const float &DataLog::getResponseTime(void) const {
	return stof(m_arrField[m_dataConfig.getIndexResponseTime() - 1]);
}

void DataLog::setField(void) {
	stack<char> stkBracket;
	int iField = 0, iFieldStart = 0;
	const int nRecordLength = m_strRecord.length();

	for (int iRecordChar = 0; iRecordChar < nRecordLength && iField < m_dataConfig.getNumberOfField() - 1; iRecordChar++) {
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
			break;
		case '\"':
			if (!stkBracket.empty() && stkBracket.top() == '\"') { stkBracket.pop(); }
			else { stkBracket.push('\"'); }
			break;
		default:
			;
		}
	}
	m_arrField[iField] = m_strRecord.substr(iFieldStart, nRecordLength - iFieldStart);
}

string DataLog::getInFilePath(const int &iFile) {
	char strFilePath[512];

	sprintf(strFilePath, "%s\\%04d%02d%02d\\ap%d.%s_%04d-%02d-%02d.txt", m_dataConfig.getPathLogFileDir().c_str(), m_dataInput.getYear(), m_dataInput.getMonth(), m_dataInput.getDay(), iFile, "daouoffice.com_access", m_dataInput.getYear(), m_dataInput.getMonth(), m_dataInput.getDay()); // 입력파일 이름 지정
	return string(strFilePath);
}