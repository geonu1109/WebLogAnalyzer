#ifndef __LogMonitor_h__
#define __LogMonitor_h__

#include "ConfigData.h"
#include <fstream>
#include <string>
using namespace std;

class LogMonitor {
private:

public:
	LogMonitor(void);
	~LogMonitor(void);
	void run(void);

private:
	static void subprocess(const string &strLogFilePath);
	static string getLogFilePath(const int &iLogFile);
};

#endif