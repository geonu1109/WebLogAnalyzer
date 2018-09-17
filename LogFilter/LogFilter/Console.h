#ifndef __Console_h__
#define __Console_h__

#include "Output.h"
#include <string>
using namespace std;

class Console : public Output {
private:
	static Console *pInstance;

public:
	static Console *getInstance(void);
	virtual void print(const string &strMsg);
	void printErr(const string &strErrMsg) const;
	void printChart(int arrValid[], int arrTotal[]) const;
	void showProgress(const unsigned short int &ratio) const;

private:
	Console();
};

#endif