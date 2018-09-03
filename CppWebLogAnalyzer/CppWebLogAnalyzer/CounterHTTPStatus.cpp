#include "CounterHTTPStatus.h"



CounterHTTPStatus::CounterHTTPStatus(const int hour, const int code, const int counter = 1) : hour(hour), code(code), counter(counter)
{
}


CounterHTTPStatus::~CounterHTTPStatus()
{
}

int CounterHTTPStatus::getHour(void) {
	return hour;
}

int CounterHTTPStatus::getCode(void) {
	return code;
}

int CounterHTTPStatus::getCounter(void) {
	return counter;
}

void CounterHTTPStatus::incrCounter(int num = 1) {
	counter += num;
}