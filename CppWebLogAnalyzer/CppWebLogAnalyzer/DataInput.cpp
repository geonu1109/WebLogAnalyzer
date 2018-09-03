#include "DataInput.h"
#include <cstdlib>
#include <cstring>

DataInput::DataInput()
{
}


DataInput::~DataInput()
{
}

void DataInput::getDate(const char *strDate) {
	char tmp[5];
	strncpy_s(tmp, 5, &strDate[0], 4);
	year = atoi(tmp);
	strncpy_s(tmp, 5, &strDate[4], 2);
	month = atoi(tmp);
	strncpy_s(tmp, 5, &strDate[6], 2);
	day = atoi(tmp);
}

void DataInput::getTimeStart(const char *strTime) {
	char tmp[3];
	strncpy_s(tmp, 3, &strTime[0], 2);
	hour_start = atoi(tmp);
	strncpy_s(tmp, 3, &strTime[2], 2);
	minute_start = atoi(tmp);
	strncpy_s(tmp, 3, &strTime[4], 2);
	second_start = atoi(tmp);
}
void DataInput::getTimeEnd(const char *strTime) {
	char tmp[3];
	strncpy_s(tmp, 3, &strTime[0], 2);
	hour_end = atoi(tmp);
	strncpy_s(tmp, 3, &strTime[2], 2);
	minute_end = atoi(tmp);
	strncpy_s(tmp, 3, &strTime[4], 2);
	second_end = atoi(tmp);
}

void DataInput::getDelay(const int delay) {
	this->delay = delay;
}