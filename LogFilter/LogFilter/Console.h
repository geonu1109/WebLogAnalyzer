#ifndef __Console_h__
#define __Console_h__

#include <string>
using namespace std;

class Console {
private:
	static Console instance;

public:
	static Console &getInstance(void);
	void print(const string &strMsg) const;
	void printErr(const string &strErrMsg) const;
	void printChart(int arrValid[], int arrTotal[]) const;
	void showProgress(const unsigned short int &ratio) const;

private:
	Console();
};

#endif