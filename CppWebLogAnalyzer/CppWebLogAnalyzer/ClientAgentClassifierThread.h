#ifndef __CLIENTAGENTCLASSIFIERTHREAD_H__
#define __CLIENTAGENTCLASSIFIERTHREAD_H__

#include <list>
#include <utility>
#include <mutex>
using namespace std;

class ClientAgentClassifierThread
{
private:
	static mutex mtxList;

public:
	ClientAgentClassifierThread();
	~ClientAgentClassifierThread();
	void process(void);

private:
	static void subprocess(const int &iFile, list<pair<pair<string, string>, int>> arrlistClientAgent[]);
};

#endif