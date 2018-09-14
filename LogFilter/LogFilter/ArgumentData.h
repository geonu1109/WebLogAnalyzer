#ifndef __ArgumentData_h__
#define __ArgumentData_h__

#include <string>
#include <list>
#include <ctime>
using namespace std;

class ArgumentData {
private:
	static ArgumentData *pInstance;
	float DelayTimeLimit;
	list<int> HttpStatusCode;
	string ResultFilePath;
	tm tmDate;

public:
	static ArgumentData &getInstance(void);
	static void init(const int &argc, const char * const argv[]);
	const float &getDelayTimeLimit(void) const;
	const list<int> &getHttpStatusCode(void) const;
	const string &getResultFilePath(void) const;
	const tm &getDate(void) const;

private:
	ArgumentData(void);
};

#endif