#ifndef __HTTPSTATUSCOUNTER_H__
#define __HTTPSTATUSCOUNTER_H__

#include <list>
#include <utility>
#include <mutex>
using namespace std;

class HttpStatusCounterThread
{
private:
	static mutex m_mtxList;

public:
	HttpStatusCounterThread();
	~HttpStatusCounterThread();
	void process(void);

private:
	static void subprocess(const int &iFile, list<pair<int, int>> *arrlistHourlyStatus);
};

#endif