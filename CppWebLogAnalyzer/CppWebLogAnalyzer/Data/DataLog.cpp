#include "DataLog.h"
#include <iostream>
#include <stack>

DataLog::DataLog(const DataConfig &dataConfig, const string &strFilePath) : m_dataConfig(dataConfig), m_ifLog(strFilePath), m_nLine(1) {
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
		m_nLine++;
		getline(m_ifLog, m_strRecord);
		setField();

		return m_strRecord;
	}
	else {
		return string();
	}
}

const int DataLog::getLine(void) const {
	return m_nLine;
}

const string DataLog::getRecord(void) const {
	return m_strRecord;
}

const float DataLog::getResponseTime(void) const {
	return stof(m_arrField[m_dataConfig.getIndexResponseTime() - 1]);
}

const bool DataLog::isValidTime(const tm &tmTimeEnd) const {
	tm tmTimeCur;
	tmTimeCur.tm_hour = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(13, 2));
	tmTimeCur.tm_min = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(16, 2));
	tmTimeCur.tm_sec = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(19, 2));

	if (calTotalTime(tmTimeCur) <= calTotalTime(tmTimeEnd) + 600)
		return true;
	else
		return false;
}

const bool DataLog::isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const {
	tm tmTimeCur;
	tmTimeCur.tm_hour = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(13, 2));
	tmTimeCur.tm_min = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(16, 2));
	tmTimeCur.tm_sec = stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(19, 2));

	if (calTotalTime(tmTimeStart) > calTotalTime(tmTimeEnd)) {
		cout << endl;
		cout << "[method] const bool DataLog::isValidTime(const tm &tmTimeStart, const tm &tmTimeEnd) const" << endl;
		cout << "[fatal error] invalid time" << endl;
		cout << endl;
		system("pause");
		exit(0);
	}

	if (calTotalTime(tmTimeStart) <= calTotalTime(tmTimeCur) && calTotalTime(tmTimeCur) <= calTotalTime(tmTimeEnd))
		return true;
	else
		return false;
}

const bool DataLog::isApi(void) const {
	if (m_arrField[m_dataConfig.getIndexApi() - 1].substr(0, 4) == "/api") {
		return true;
	}
	else {
		return false;
	}
}

const bool DataLog::isStaticResource(void) const {
	// if (m_arrField[m_dataConfig.getIndexApi() - 1].find("/rs") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find("/resources") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".css") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".js") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find("/favicon.ico") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".png") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".txt") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find("/thumb") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find("/img") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".gif") != string::npos || m_arrField[m_dataConfig.getIndexApi() - 1].find(".php") != string::npos) return true;
	if (m_arrField[m_dataConfig.getIndexApi() - 1].find('.') != string::npos) return true;
	else return false;
}

const int DataLog::getHour(void) const {
	return stoi(m_arrField[m_dataConfig.getIndexDateTime() - 1].substr(13, 2));
}

const int DataLog::getHttpStatusCode(void) const {
	return stoi(m_arrField[m_dataConfig.getIndexHttpStatusCode() - 1]);
}

const string DataLog::getHttpRequestMethod(void) const {
	return m_arrField[m_dataConfig.getIndexHttpRequestMethod() - 1];
}

const string DataLog::getApiField(void) const {
	return m_arrField[m_dataConfig.getIndexApi() - 1];
}

const string DataLog::getApiGroup(void) const {
	int iApiChar = m_arrField[m_dataConfig.getIndexApi() - 1].find('?');
	string strApi;
	
	if (iApiChar != string::npos) {
		strApi = m_arrField[m_dataConfig.getIndexApi() - 1].substr(0, iApiChar);
	}
	else {
		strApi = m_arrField[m_dataConfig.getIndexApi() - 1];
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

const string DataLog::getClientAgentField(void) const {
	return m_arrField[m_dataConfig.getIndexClientAgent() - 1];
}

const string DataLog::getBrowser(void) const {
	const string &strAgent = m_arrField[m_dataConfig.getIndexClientAgent() - 1];

	if (strAgent.find("compatible") != string::npos || strAgent.find("compatible") != string::npos) return string("Internet Explorer");
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

const string DataLog::getOS(void) const {
	const string &strAgent = m_arrField[m_dataConfig.getIndexClientAgent() - 1];

	if (strAgent.find("Windows") != string::npos) return string("Windows");
	else if (strAgent.find("Linux") != string::npos) {
		if (strAgent.find("Android") != string::npos) return string("Android");
		else return string("Linux");
	}
	else if (strAgent.find("iPhone") != string::npos || strAgent.find("iPad") != string::npos) return string("iOS");
	else if (strAgent.find("Macintosh") != string::npos) return string("macOS");
	else return string("?");
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
			//else {
			//	cout << endl;
			//	cout << "[method] void DataLog::setField(void)" << endl;
			//	cout << "[minor error] [ ] is not matched." << endl;
			//	cout << "[record] " << m_strRecord << endl;
			//	cout << endl;
			//}
			break;
		case '\"':
			if (m_strRecord.at(iRecordChar - 1) == ' ') {
				stkBracket.push('\"');
			}
			else if (m_strRecord.at(iRecordChar + 1) == ' ' || iRecordChar == nRecordLength - 1) {
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

int DataLog::calTotalTime(const tm &tmTime) const {
	return ((tmTime.tm_hour * 3600) + (tmTime.tm_min * 60) + tmTime.tm_sec);
}
