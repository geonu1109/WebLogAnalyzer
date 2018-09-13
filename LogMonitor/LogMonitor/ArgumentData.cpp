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
		if (strBuffer == "--delay" || strBuffer == "-d") {
			ArgumentData::getInstance().DelayTimeLimit = stof(argv[++i]);
		}
		else if (strBuffer == "--status" || strBuffer == "-s") {
			ArgumentData::getInstance().HttpStatusCode.push_back(stoi(argv[++i]));
		}
		else if (strBuffer == "--output" || strBuffer == "-o") {
			ArgumentData::getInstance().ResultFilePath = argv[++i];
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

ArgumentData::ArgumentData() : DelayTimeLimit(0.0) {
}
