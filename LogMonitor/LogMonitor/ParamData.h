#ifndef __ParamData_h__
#define __ParamData_h__

#include <string>
using namespace std;

class ParamData {
private:
	static ParamData *pInstance;
	int nDelayedTimeLimit;

public:
	static ParamData &getInstance(void);
	static void init(const int &argc, const char * const argv[]);
	
private:
	ParamData(void);
};

#endif