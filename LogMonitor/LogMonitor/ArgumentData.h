#ifndef __ArgumentData_h__
#define __ArgumentData_h__

#include <string>
#include <list>
using namespace std;

class ArgumentData {
private:
	static ArgumentData *pInstance;
	float DelayTimeLimit;
	list<int> HttpStatusCode;
	string ResultFilePath;

public:
	static ArgumentData &getInstance(void);
	static void init(const int &argc, const char * const argv[]);
	const float &getDelayTimeLimit(void) const;
	const list<int> &getHttpStatusCode(void) const;
	const string &getResultFilePath(void) const;

private:
	ArgumentData(void);
};

#endif