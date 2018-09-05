#ifndef __DATAINPUT_H__
#define __DATAINPUT_H__

#include <string>
using namespace std;

class DataInput {
private:
	int m_nYear, m_nMonth, m_nDay;
	int m_nHourStart, m_nMinuteStart, m_nSecondStart;
	int m_nHourEnd, m_nMinuteEnd, m_nSecondEnd;
	int m_nDelayLimit;

public:
	DataInput();
	~DataInput();
	void setDate(const string &strDate);
	void setTimeStart(const string &strTime);
	void setTimeEnd(const string &strTime);
	void setDelayLimit(const int &nDelayLimit);
	const int getYear(void) const;
	const int getMonth(void) const;
	const int getDay(void) const;
	const int getHourStart(void) const;
	const int getMinuteStart(void) const;
	const int getSecondStart(void) const;
	const int getHourEnd(void) const;
	const int getMinuteEnd(void) const;
	const int getSecondEnd(void) const;
	const int getDelayLimit(void) const;
};

#endif