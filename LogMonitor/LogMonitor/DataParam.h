#ifndef __DATAPARAM_H__
#define __DATAPARAM_H__

#include <string>
using namespace std;

class DataParam {
private:
	static DataParam *pInstance;
	int nDelayedTimeLimit;

public:
	DataParam &getInstance(void);
	void init(const int &argc, const char * const argv[]);
	
private:
	DataParam(void);
};

#endif