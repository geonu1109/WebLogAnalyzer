#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include <fstream>
#include <thread>
#include <mutex>
using namespace std;

class Processor
{
	typedef pair<ofstream, mutex> ofstreamsync;

public:
	Processor();
	~Processor();
	void process(void);

private:
	static void subprocess(ofstreamsync &ofResult);
};

#endif