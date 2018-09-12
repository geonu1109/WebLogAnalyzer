#include "ResultWriter.h"
#include "ConfigData.h"

ResultWriter *ResultWriter::pInstance = nullptr;

ResultWriter &ResultWriter::getInstance(void) {
	if (pInstance) {
		return *pInstance;
	}
	else {
		throw string("unable to use result writer without initialization");
	}
}

void ResultWriter::init(const string &strResultFilePath) {
	pInstance = new ResultWriter(strResultFilePath);
}

void ResultWriter::write(const string &str) {
	//
}

ResultWriter::ResultWriter(const string &strResultFilePath) : ResultFilePath(strResultFilePath) {
}
