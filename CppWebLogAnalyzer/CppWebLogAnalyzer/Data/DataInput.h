#ifndef __DATAINPUT_H__
#define __DATAINPUT_H__

#include <string>
#include <ctime>
using namespace std;

class DataInput // Singleton
{
private:
	int m_nSelect;
	tm m_tmDate;
	tm m_tmTimeStart;
	tm m_tmTimeEnd;
	int m_nDelayLimit;
	int m_nHttpStatusCode;
	string m_strHttpRequestMethod;
	static DataInput instance;

public:
	~DataInput();
	void setSelect(const int &nSelect);
	void setDate(const string &strDate);
	void setTimeStart(const string &strTime);
	void setTimeEnd(const string &strTime);
	void setDelayLimit(const int &nDelayLimit);
	void setHttpStatusCode(const int &nHttpStatusCode);
	void setHttpRequestMethod(const string &strHttpRequestMethod);
	const int getSelect(void);
	const tm getDate(void);
	const tm getTimeStart(void);
	const tm getTimeEnd(void);
	const int getDelayLimit(void);
	const int getHttpStatusCode(void);
	const string getHttpRequestMethod(void);
	static DataInput getInstance(void);

private:
	DataInput();
};

#endif