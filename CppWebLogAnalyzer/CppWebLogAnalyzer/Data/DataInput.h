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
	int m_nHttpStatusCode;
	string m_strHttpRequestMethod;

public:
	DataInput();
	~DataInput();
	void setDate(const string &strDate);
	void setTimeStart(const string &strTime);
	void setTimeEnd(const string &strTime);
	void setDelayLimit(const int &nDelayLimit);
	void setHttpStatusCode(const int &nHttpStatusCode);
	void setHttpRequestMethod(const string &strHttpRequestMethod);
	const tm getDate(void) const;
	const tm getTimeStart(void) const;
	const tm getTimeEnd(void) const;
	const int getDelayLimit(void) const;
	const int getHttpStatusCode(void) const;
	const string getHttpRequestMethod(void) const;
};

#endif