#ifndef __LogFilter_h__
#define __LogFilter_h__

class LogFilter {
public:
	static void run(void);

private:
	static void subprocess(const int &iFile);
	static const string getLogFilePath(const int &iLogFile);
};

#endif