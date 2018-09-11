#include "Processor.h"



Processor::Processor()
{
}


Processor::~Processor()
{
}

void Processor::process(void)
{
	ofstreamsync ofResult;

	thread(&subprocess, ofResult);
}

void Processor::subprocess(pair<ofstream, mutex> &ofResult) {

}