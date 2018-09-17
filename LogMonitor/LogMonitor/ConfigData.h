#ifndef __ConfigData_h__
#define __ConfigData_h__

#include <string>
using namespace std;

class ConfigData {
private:
	static ConfigData *pInstance;
	int m_nLogField;
	int m_iResponseTimeField;
	int m_iDateTimeField;
	int m_iHttpRequestMethodField;
	int m_iHttpStatusCodeField;
	int m_iApiField;
	int m_iClientAgentField;
	string m_strLogDirPath;
	int m_nFile;

public:
	static ConfigData &getInstance(void);
	static void load(const string &strConfigFilePath);
	const int &getNumberOfLogField(void) const;
	const int &getIndexOfResponseTimeField(void) const;
	const int &getIndexOfDateTimeField(void) const;
	const int &getIndexOfHttpStatusCodeField(void) const;
	const int &getIndexOfHttpRequestMethodField(void) const;
	const int &getNumberOfFile(void) const;
	const string &getLogDirPath(void) const;
	const int &getIndexOfApiField(void) const;
	const int &getIndexOfClientAgentField(void) const;

private:
	ConfigData(void);
};

#endif