#include "DataParam.h"
#include <sstream>

DataParam *DataParam::pInstance = nullptr;

DataParam &DataParam::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use parameter data without initialization");
	}
}

void DataParam::init(const int &argc, const char * const argv[]) {
	string strBuffer;

	for (int i = 1; i < argc; i++) {
		strBuffer = string(argv[i]);
		if (strBuffer == "--delayed" || strBuffer == "-d") {
			DataParam::getInstance().nDelayedTimeLimit = stoi(argv[++i]);
		}
	}
}

DataParam::DataParam() {
}
