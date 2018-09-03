#ifndef __DATACONFIG_H__
#define __DATACONFIG_H__

class DataConfig {
public:
	char *LOG_FILE_DIR;
	int LOG_FILE_COUNT;
	int FIELD_COUNT;
	int INDEX_RESPONSE_TIME;
	int INDEX_DATETIME;

public:
	DataConfig(void);
	~DataConfig(void);
	void load(char *path);
};

#endif