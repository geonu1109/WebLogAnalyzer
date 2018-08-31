#ifndef __CONFIG_H__
#define __CONFIG_H__

class Config {
public:
	char *LOG_FILE_DIR;
	int LOG_FILE_COUNT;
	int FIELD_COUNT;
	int INDEX_RESPONSE_TIME;

public:
	Config(void);
	~Config(void);
	void load(char *path);
};

#endif