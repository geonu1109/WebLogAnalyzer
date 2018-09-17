#ifndef __LogFilter_h__
#define __LogFilter_h__

#include <mutex>
using namespace std;

class LogFilter {
public:
	static int s_arrcTotalLog[24];
	static int s_arrcValidLog[24];
	static mutex s_mtxTotalLog;
	static mutex s_mtxValidLog;

public:
	static void run(void);

private:
	static void subprocess(const int &iFile);
};

#endif