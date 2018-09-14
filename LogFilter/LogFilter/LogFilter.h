#ifndef __LogFilter_h__
#define __LogFilter_h__

#include <mutex>
using namespace std;

class LogFilter {
public:
	static int arrcTotalLog[24];
	static int arrcValidLog[24];
	static mutex mtxTotalLog;
	static mutex mtxValidLog;

public:
	static void run(void);

private:
	static void subprocess(const int &iFile);
	static const string getLogFilePath(const int &iLogFile);
};

#endif