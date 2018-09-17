#include "OutputFile.h"
#include "ArgumentData.h"

OutputFile *OutputFile::pInstance = nullptr;

OutputFile *OutputFile::getInstance(void) {
	if (pInstance == nullptr) {
		pInstance = new OutputFile();
	}
	return pInstance;
}

void OutputFile::print(const string &strBuffer) {
	m_of << strBuffer << endl;
}

OutputFile::OutputFile() : m_of(ArgumentData::getInstance().getResultFilePath()) {
}