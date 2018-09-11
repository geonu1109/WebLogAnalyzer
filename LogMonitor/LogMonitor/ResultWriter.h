#ifndef __RESULTWRITER_H__
#define __RESULTWRITER_H__

#include <fstream>
#include <string>
using namespace std;

class ResultWriter
{
private:
	static ResultWriter *pInstance;
	ofstream m_ofResult;
	const string ResultFilePath;

public:
	static ResultWriter &getInstance(void);
	static void init(const string &strResultFilePath);
	void write(const string &str);

private:
	ResultWriter(const string &strResultFilePath);
};

#endif