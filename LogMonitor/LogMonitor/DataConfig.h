#ifndef __DATACONFIG_H__
#define __DATACONFIG_H__

#include <string>
using namespace std;

class DataConfig {
private:
	static DataConfig *pInstance;
	int m_nLogField;
	int m_iFieldResponseTime;
	string m_strLogDirPath;

public:
	static DataConfig &getInstance(void);
	static void load(const string &strConfigFilePath);
	const int &getLogField(void) const;

private:
	DataConfig(void);
};

#endif