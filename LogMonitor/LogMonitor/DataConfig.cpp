#include "DataConfig.h"
#include <fstream>
#include <sstream>

DataConfig *DataConfig::pInstance = nullptr;

DataConfig &DataConfig::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use configuration data without load");
	}
}

void DataConfig::load(const string &strConfigFilePath) {
	if (pInstance == nullptr) {
		pInstance = new DataConfig();
	}
	else {
		throw string("unable to reload configuration file");
	}

	ifstream ifConfig(strConfigFilePath);
	string strBuffer;
	stringstream ssBuffer;
	int iFieldCharStart = 0;

	if (ifConfig.fail()) {
		throw string("failed to open configuration file");
	}

	while (!ifConfig.eof()) {
		getline(ifConfig, strBuffer);
		ssBuffer.str(strBuffer);

		ssBuffer >> strBuffer;
		if (strBuffer.at(0) == '#') {
			continue;
		}
		else if (strBuffer == "NumberOfLogField") {
			ssBuffer >> DataConfig::getInstance().m_nLogField;
		}
		else if (strBuffer == "IndexOfResponseTimeField") {
			ssBuffer >> DataConfig::getInstance().m_iFieldResponseTime;
		}
		else if (strBuffer == "LogDirPath") {
			ssBuffer >> DataConfig::getInstance().m_strLogDirPath;
		}
	}
}

const int &DataConfig::getLogField(void) const {
	return m_nLogField;
}

DataConfig::DataConfig() {
}