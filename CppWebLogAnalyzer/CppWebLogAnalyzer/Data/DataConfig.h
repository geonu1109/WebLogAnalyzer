#ifndef __DATACONFIG_H__
#define __DATACONFIG_H__

#include <string>
using namespace std;

class DataConfig // Singleton
{
private:
	const string ConfigFilePath;
	string PathLogFileDir;
	int NumberOfLogFile;
	int NumberOfField;
	int IndexResponseTime;
	int IndexDateTime;
	int IndexHttpStatusCode;
	int IndexApi;
	int IndexHttpRequestMethod;
	int IndexClientAgent;
	static DataConfig instance;

public:
	~DataConfig(void);
	void load(void);
	const string getPathLogFileDir(void);
	const int getNumberOfLogFile(void);
	const int getNumberOfField(void);
	const int getIndexResponseTime(void);
	const int getIndexDateTime(void);
	const int getIndexHttpStatusCode(void);
	const int getIndexApi(void);
	const int getIndexHttpRequestMethod(void);
	const int getIndexClientAgent(void);
	static DataConfig &getInstance(void);

private:
	DataConfig(void);
};

#endif