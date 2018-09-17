#include "ConfigData.h"
#include <fstream>
#include <sstream>

ConfigData *ConfigData::pInstance = nullptr;

ConfigData &ConfigData::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use configuration data without load");
	}
}

void ConfigData::load(const string &strConfigFilePath) {
	if (pInstance == nullptr) {
		pInstance = new ConfigData();
	}
	else {
		throw string("unable to load configuration file twice or more");
	}

	ifstream ifConfig(strConfigFilePath);
	string strBuffer;
	stringstream ssBuffer;
	int iFieldCharStart = 0;

	if (ifConfig.fail()) {
		throw string("failed to open configuration file");
	}

	while (!ifConfig.eof()) {
		ssBuffer.clear();
		getline(ifConfig, strBuffer);
		ssBuffer.str(strBuffer);

		ssBuffer >> strBuffer;
		if (strBuffer.at(0) == '#') {
			continue;
		}
		else if (strBuffer == "NumberOfLogField") {
			ssBuffer >> ConfigData::getInstance().m_nLogField;
		}
		else if (strBuffer == "IndexOfResponseTimeField") {
			ssBuffer >> ConfigData::getInstance().m_iResponseTimeField;
		}
		else if (strBuffer == "IndexOfDateTimeField") {
			ssBuffer >> ConfigData::getInstance().m_iDateTimeField;
		}
		else if (strBuffer == "IndexOfHttpStatusCodeField") {
			ssBuffer >> ConfigData::getInstance().m_iHttpStatusCodeField;
		}
		else if (strBuffer == "IndexOfHttpRequestMethodField") {
			ssBuffer >> ConfigData::getInstance().m_iHttpRequestMethodField;
		}
		else if (strBuffer == "LogDirPath") {
			ssBuffer >> ConfigData::getInstance().m_strLogDirPath;
		}
		else if (strBuffer == "NumberOfFile") {
			ssBuffer >> ConfigData::getInstance().m_nFile;
		}
		else if (strBuffer == "IndexOfApiField") {
			ssBuffer >> ConfigData::getInstance().m_iApiField;
		}
		else if (strBuffer == "IndexOfClientAgent") {
			ssBuffer >> ConfigData::getInstance().m_iClientAgentField;
		}
	}
}

const int &ConfigData::getNumberOfLogField(void) const {
	return m_nLogField;
}

const int &ConfigData::getIndexOfResponseTimeField(void) const {
	return m_iResponseTimeField;
}

const int &ConfigData::getIndexOfDateTimeField(void) const {
	return m_iDateTimeField;
}

const int &ConfigData::getIndexOfHttpStatusCodeField(void) const {
	return m_iHttpStatusCodeField;
}

const int &ConfigData::getIndexOfHttpRequestMethodField(void) const {
	return m_iHttpRequestMethodField;
}

const int &ConfigData::getNumberOfFile(void) const {
	return m_nFile;
}

const string &ConfigData::getLogDirPath(void) const {
	return m_strLogDirPath;
}

const int &ConfigData::getIndexOfApiField(void) const {
	return m_iApiField;
}

const int &ConfigData::getIndexOfClientAgentField(void) const {
	return m_iClientAgentField;
}

ConfigData::ConfigData() {
}