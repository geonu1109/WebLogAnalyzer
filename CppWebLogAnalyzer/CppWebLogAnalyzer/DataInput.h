#ifndef __DATAINPUT_H__
#define __DATAINPUT_H__

class DataInput {
public:
	int year, month, day;
	int hour_start, minute_start, second_start;
	int hour_end, minute_end, second_end;
	int delay;

public:
	DataInput();
	~DataInput();
	void getDate(const char *strDate);
	void getTimeStart(const char *strTime);
	void getTimeEnd(const char *strTime);
	void getDelay(const int delay);
};

#endif