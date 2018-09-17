#ifndef __OutputFile_h__
#define __OutputFile_h__

#include "Output.h"
#include <string>
#include <fstream>
using namespace std;

class OutputFile : public Output {
private:
	static OutputFile *pInstance;
	ofstream m_of;

public:
	static OutputFile *getInstance(void);
	virtual void print(const string &strBuffer);

private:
	OutputFile();
};

#endif