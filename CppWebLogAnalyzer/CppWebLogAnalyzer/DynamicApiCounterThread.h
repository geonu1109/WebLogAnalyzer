#ifndef __DYNAMICAPICOUNTERTHREAD_H__
#define __DYNAMICAPICOUNTERTHREAD_H__

#include <list>
#include <utility>
#include <mutex>
using namespace std;

class DynamicApiCounterThread
{
private:
	static mutex m_mtxList;

public:
	DynamicApiCounterThread();
	~DynamicApiCounterThread();
	void process(void);

private:
	static void subprocess(const int &iFile, list<pair<string, int>> *listApiCounter);
	static const bool desc(pair<string, int> &first, pair<string, int> &second);
};

#endif