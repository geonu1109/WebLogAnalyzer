#ifndef __DYNAMICAPICOUNTERTHREAD_H__
#define __DYNAMICAPICOUNTERTHREAD_H__

#include <mutex>
using namespace std;

class DynamicApiCounterThread
{
private:
	mutex mtx;

public:
	DynamicApiCounterThread();
	~DynamicApiCounterThread();
	void process(void);

private:
	void subprocess(void);
};

#endif