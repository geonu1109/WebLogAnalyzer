#ifndef __DATACONFIG_H__
#define __DATACONFIG_H__

#include <string>
using namespace std;

class DataConfig {
private:
	string PathLogFileDir;
	int NumberOfLogFile;
	int NumberOfField;
	int IndexResponseTime;
	int IndexDateTime;
	int IndexHttpStatus;

public:
	DataConfig(void);
	~DataConfig(void);
	const string getPathLogFileDir(void) const;
	const int getNumberOfLogFile(void) const;
	const int getNumberOfField(void) const;
	const int getIndexResponseTime(void) const;
	const int getIndexDateTime(void) const;
	const int getIndexHttpStatus(void) const;

private:
	void load(const string &strFilePath);
};

#endif