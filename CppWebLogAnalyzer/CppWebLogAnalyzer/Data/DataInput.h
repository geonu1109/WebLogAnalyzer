#ifndef __DATAINPUT_H__
#define __DATAINPUT_H__

#include <string>
#include <ctime>
using namespace std;

class DataInput {
private:
	tm m_tmDate;
	tm m_tmTimeStart;
	tm m_tmTimeEnd;
	int m_nDelayLimit;

public:
	DataInput();
	~DataInput();
	void setDate(const string &strDate);
	void setTimeStart(const string &strTime);
	void setTimeEnd(const string &strTime);
	void setDelayLimit(const int &nDelayLimit);
	const tm getDate(void) const;
	const tm getTimeStart(void) const;
	const tm getTimeEnd(void) const;
	const int getDelayLimit(void) const;
};

#endif