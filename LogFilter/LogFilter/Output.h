#ifndef __Output_h__
#define __Output_h__

#include <string>
using namespace std;

class Output {
public:
	static Output *getInstance(void);
	virtual void print(const string &strBuffer) = 0;
};

#endif