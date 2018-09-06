#ifndef __LOGFILTERTHREAD_H__
#define __LOGFILTERTHREAD_H__

class LogFilterThread
{
public:
	LogFilterThread();
	~LogFilterThread();
	void process(void);

private:
	static void subprocess(const int &iFile);
};

#endif