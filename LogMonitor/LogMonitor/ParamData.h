#ifndef __ParamData_h__
#define __ParamData_h__

#include <string>
#include <list>
using namespace std;

class ParamData {
private:
	static ParamData *pInstance;
	float DelayTimeLimit;
	list<int> HttpStatusCode;

public:
	static ParamData &getInstance(void);
	static void init(const int &argc, const char * const argv[]);
	const float &getDelayTimeLimit(void) const;
	const list<int> &getHttpStatusCode(void) const;
	
private:
	ParamData(void);
};

#endif