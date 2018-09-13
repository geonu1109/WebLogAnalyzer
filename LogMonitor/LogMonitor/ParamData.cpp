#include "ParamData.h"
#include <sstream>

ParamData *ParamData::pInstance = nullptr;

ParamData &ParamData::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use parameter data without initialization");
	}
}

void ParamData::init(const int &argc, const char * const argv[]) {
	if (pInstance == nullptr) {
		pInstance = new ParamData();
	}
	else {
		throw string("unable to initialize parameter data twice or more");
	}

	string strBuffer;

	for (int i = 1; i < argc; i++) {
		strBuffer = string(argv[i]);
		if (strBuffer == "--delay" || strBuffer == "-d") {
			ParamData::getInstance().DelayTimeLimit = stof(argv[++i]);
		}
		else if (strBuffer == "--status" || strBuffer == "-s") {
			ParamData::getInstance().HttpStatusCode.push_back(stoi(argv[++i]));
		}
	}
}

const float &ParamData::getDelayTimeLimit(void) const {
	return DelayTimeLimit;
}

const list<int> &ParamData::getHttpStatusCode(void) const {
	return HttpStatusCode;
}

ParamData::ParamData() : DelayTimeLimit(0.0) {
}
