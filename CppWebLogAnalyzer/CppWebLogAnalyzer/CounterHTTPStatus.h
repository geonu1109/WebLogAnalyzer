#ifndef __COUNTERHTTPSTATUS_H__
#define __COUNTERHTTPSTATUS_H__

class CounterHTTPStatus
{
private:
	int hour;
	int code;
	int counter;

public:
	CounterHTTPStatus(const int hour, const int code, const int counter = 1);
	~CounterHTTPStatus();
	int getHour(void);
	int getCode(void);
	int getCounter(void);
	void incrCounter(int num = 1);
};

#endif