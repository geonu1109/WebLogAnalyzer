#include "ArgumentData.h"
#include <sstream>

ArgumentData *ArgumentData::pInstance = nullptr;

ArgumentData &ArgumentData::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use parameter data without initialization");
	}
}

void ArgumentData::init(const int &argc, const char * const argv[]) {
	if (pInstance == nullptr) {
		pInstance = new ArgumentData();
	}
	else {
		throw string("unable to initialize parameter data twice or more");
	}

	string strBuffer;

	for (int i = 1; i < argc; i++) {
		strBuffer = string(argv[i]);
		if (strBuffer == "--limit" || strBuffer == "-l") {
			ArgumentData::getInstance().DelayTimeLimit = stof(argv[++i]);
		}
		else if (strBuffer == "--status" || strBuffer == "-s") {
			ArgumentData::getInstance().HttpStatusCode.push_back(stoi(argv[++i]));
		}
		else if (strBuffer == "--output" || strBuffer == "-o") {
			ArgumentData::getInstance().ResultFilePath = argv[++i];
		}
		else if (strBuffer == "--easy" || strBuffer == "-e") {
			ArgumentData::getInstance().bEasy = true;
		}
		else if (strBuffer == "--date" || strBuffer == "-d") {
			strBuffer = argv[++i];
			ArgumentData::getInstance().tmDate.tm_year = stoi(strBuffer.substr(0, 4));
			ArgumentData::getInstance().tmDate.tm_mon = stoi(strBuffer.substr(4, 2));
			ArgumentData::getInstance().tmDate.tm_mday = stoi(strBuffer.substr(6, 2));
		}
		else if (strBuffer == "--time" || strBuffer == "-t") {
			strBuffer = argv[++i];
			ArgumentData::getInstance().tmStart.tm_hour = stoi(strBuffer.substr(0, 2));
			ArgumentData::getInstance().tmStart.tm_min = stoi(strBuffer.substr(2, 2));
			ArgumentData::getInstance().tmStart.tm_sec = stoi(strBuffer.substr(4, 2));
			ArgumentData::getInstance().tmEnd.tm_hour = stoi(strBuffer.substr(7, 2));
			ArgumentData::getInstance().tmEnd.tm_min = stoi(strBuffer.substr(9, 2));
			ArgumentData::getInstance().tmEnd.tm_sec = stoi(strBuffer.substr(11, 2));
		}
	}
}

const float &ArgumentData::getDelayTimeLimit(void) const {
	return DelayTimeLimit;
}

const list<int> &ArgumentData::getHttpStatusCode(void) const {
	return HttpStatusCode;
}

const string &ArgumentData::getResultFilePath(void) const {
	return ResultFilePath;
}

const bool &ArgumentData::isEasyMode(void) const {
	return bEasy;
}

const tm &ArgumentData::getDate(void) const {
	return tmDate;
}

ArgumentData::ArgumentData() : DelayTimeLimit(0.0), bEasy(false) {
}
